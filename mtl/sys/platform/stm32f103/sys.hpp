#pragma once

#include <cstdint>
#include <type_traits>

#include <mtl/common/parameters.hpp>
#include <mtl/hw/descriptor.hpp>
#include <mtl/hw/flash.hpp>
#include <mtl/hw/nvic.hpp>
#include <mtl/hw/rcc.hpp>
#include <mtl/sys/pwr.hpp>

namespace mtl {
    namespace detail {
        class interrupts {
        public:
            [[gnu::always_inline]] inline static void enable() { __asm volatile("cpsie	i"); }

            template <class t_interrupt> inline static void enable() {
                t_interrupt::set_enable_register::set(1 << t_interrupt::register_index);
            }

            [[gnu::always_inline]] inline static void disable() { __asm volatile("cpsid	i"); }

            template <class t_interrupt> inline static void disable() {
                t_interrupt::clear_enable_register::set(1 << t_interrupt::register_index);
            }

            template <class t_interrupt>[[gnu::always_inline]] inline static void set() {
                t_interrupt::set_pending_register::set(1 << t_interrupt::register_index);
            }

            template <class t_interrupt>[[gnu::always_inline]] inline static void clear() {
                t_interrupt::clear_pending_register::set(1 << t_interrupt::register_index);
            }

            template <class t_interrupt>[[gnu::always_inline]] inline static bool active() {
                return t_interrupt::active_register::test(1 << t_interrupt::register_index);
            }

            template <class t_interrupt, class t_handler>
            [[gnu::always_inline]] inline static void set_handler(t_handler handler) {
                ram_interrupt_table[t_interrupt::table_offset] = reinterpret_cast<uint32_t>(handler);
            }

            static void remap() {
                // Copy interrupt table.
                auto source_table = reinterpret_cast<uint32_t *>(0);
                for (int i = 0; i < sizeof(ram_interrupt_table) / sizeof(ram_interrupt_table[0]); ++i) {
                    ram_interrupt_table[i] = source_table[i];
                }

                // Set new table pointer.
                disable();
                mtl::hw::nvic::vtor::write(reinterpret_cast<uint32_t>(ram_interrupt_table));
                enable();
            }

        private:
            alignas(128 * sizeof(uint32_t)) // Number of interrupts rounded to the upper power of 2 value.
                inline static uint32_t ram_interrupt_table[76];

            // Default interrupt handler.
            [[gnu::naked]] static void default_handler() { __asm volatile("b	."); }
        };

        class services {
        public:
            static void initialize() noexcept {
                // Setup handler, clear and activate SVC interrupt.
                interrupts::set_handler<mtl::hw::interrupts::svc>(handler);
                // interrupts::clear<mtl::hw::interrupts::svc>();
                // interrupts::enable<mtl::hw::interrupts::svc>();
            }

            [[gnu::always_inline]] static void start_os() noexcept { asm volatile("svc	0\n"); }

            template <class t_service, class... t_parameters>
            [[gnu::naked]] static void call_os_service(t_parameters &&... parameters) noexcept {
                asm volatile("push	{r0}\n");
                asm volatile(
                    //"mov	r0, %[entry]\n"
                    "push	{r0}\n"
                    "ldr	r0, [sp, #4]\n"
                    "svc	1\n"
                    "add	sp, #8\n"
                    "bx		lr\n"
                    :
                    : [ entry ] "r"(reinterpret_cast<uint32_t>(t_service::entry))
                    : "r1", "r2", "r3", "r4", "r5", "r6", /*"r7", */"r8", "r9", "r10", /*"r11", */"memory", "cc");
            }

            [[gnu::always_inline]] static void set_start_os_handler(void (*handler)()) noexcept {
                m_entries[0] = reinterpret_cast<uint32_t>(handler);
            }

            [[gnu::always_inline]] static void set_os_service_handler(void (*handler)()) noexcept {
                m_entries[1] = reinterpret_cast<uint32_t>(handler);
            }

        private:
            [[gnu::naked]] static void handler() noexcept {
                asm volatile("tst		lr, #4\n"
                             "ite		eq\n"
                             "mrseq		r3, msp\n"
                             "mrsne		r3, psp\n"
                             "ldr		r0, [r3, #24]\n"
                             "ldrb		r0, [r0, #-2]\n"
                             "mov		r0, r0, asl #2\n"
                             "mov		r1, %[entries]\n"
                             "ldr		r1, [r1, r0]\n"
                             "bx			r1\n"
                             :
                             : [ entries ] "r"(reinterpret_cast<uint32_t>(&m_entries))
                             : "r0", "r2", "r3", "r4", "r5", "r6", /*"r7", */"r8", "r9", "r10", /*"r11", */"memory", "cc");
            }

            static void os_service_default_handler() noexcept {}

            inline static uint32_t m_entries[2];
        };
    } // namespace detail

    namespace sys_ {
        template <auto v_value> struct strategy {
            enum type { max_frequency, low_power, custom };
            constexpr static type value = v_value;
        };

        template <class t_source> struct clock { using source = t_source; };
    } // namespace sys_

    template <class... t_parameters> class sys {
    public:
        using strategy = typename mtl::parameters<t_parameters...>::template find<sys_::strategy>::type;
        using clock = typename mtl::parameters<t_parameters...>::template find_type<sys_::clock>::type;
        using interrupts = detail::interrupts;
        using services = detail::services;

        constexpr static double hse_frequency = 0.0;
        constexpr static double lse_frequency = 0.0;

        // This method should be called before main() method.
        static void startup() {
            // Configure flash memory for high speed operation.
            using flash = mtl::hw::flash;
            flash::acr::prftbe::set(flash::acr::prftbe::enabled);
            flash::acr::latency::set(flash::acr::latency::two);
            while (!flash::acr::latency::test(flash::acr::latency::two))
                ;

            // Setup clocks for appropriate frequency.
            using rcc = mtl::hw::rcc;
            // Turn HSI on.
            rcc::cr::hsion::set(rcc::cr::hsion::on);
            while (!(rcc::cr::hsirdy::test(rcc::cr::hsirdy::ready)))
                ;

            // Configure PLL.
            rcc::cfgr::pllmul::set(rcc::cfgr::pllmul::mul9);
            // Turn PLL on.
            rcc::cr::pllon::set(rcc::cr::pllon::on);
            while (!(rcc::cr::pllrdy::test(rcc::cr::pllrdy::ready)))
                ;

            // Use PLL as a source for clocking.
            rcc::cfgr::sw::set(rcc::cfgr::sw::pll);

            // Divide APB1 by 2.
            rcc::cfgr::ppre1::set(rcc::cfgr::ppre1::div2);

            // Divide ADCCLK by 6.
            rcc::cfgr::adcpre::set(rcc::cfgr::adcpre::div6);
        }

        inline static void initialize() {
            // Remap interrupt table.
            detail::interrupts::remap();
            // Initialize system services.
            detail::services::initialize();
            // Allow interrupts.
            detail::interrupts::enable();
        }

        [[gnu::always_inline]] static uint32_t initial_stack_pointer() {
            // Temporary replaced.
            // __asm volatile ("ldr	r0, =__initial_sp");
            // __asm volatile ("bx		lr");
            return reinterpret_cast<uint32_t *>(0)[0];
        }

        template <class t_bus_id>[[gnu::always_inline]] inline static double frequency() {
            if constexpr (std::is_same<t_bus_id, mtl::hw::bus::hsi>::value) {
                return frequency_hsi();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::hse>::value) {
                return frequency_hse();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::lsi>::value) {
                return frequency_lsi();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::lse>::value) {
                return frequency_lse();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::pllclk>::value) {
                return frequency_pllclk();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::sysclk>::value) {
                return frequency_sysclk();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::ahb>::value) {
                return frequency_ahb();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::hclk>::value) {
                return frequency_hclk();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::cst>::value) {
                return frequency_cst();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::fclk>::value) {
                return frequency_fclk();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::apb1>::value) {
                return frequency_apb1();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::apb2>::value) {
                return frequency_apb2();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::hclk_div2>::value) {
                return frequency_hclk_div2();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::pclk1>::value) {
                return frequency_pclk1();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::timclk1>::value) {
                return frequency_timclk1();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::pclk2>::value) {
                return frequency_pclk2();
            } else if constexpr (std::is_same<t_bus_id, mtl::hw::bus::timclk2>::value) {
                return frequency_timclk2();
            } else {
                return 0.0;
            }
        }

        template <class t_device_id>[[gnu::always_inline]] static void enable() {
            mtl::pwr::enable<t_device_id>();
        }

    private:
        [[gnu::always_inline]] constexpr static double frequency_hsi() { return mtl::hw::frequency<mtl::hw::bus::hsi>; }

        [[gnu::always_inline]] constexpr static double frequency_hse() { return hse_frequency; }

        [[gnu::always_inline]] constexpr static double frequency_lsi() { return mtl::hw::frequency<mtl::hw::bus::lsi>; }

        [[gnu::always_inline]] constexpr static double frequency_lse() { return lse_frequency; }

        inline static double frequency_pllclk() {
            using rcc = mtl::hw::rcc;
            if (rcc::cr::pllon::test(rcc::cr::pllon::off)) {
                return 0.0;
            }

            double source;
            if (rcc::cfgr::pllsrc::test(rcc::cfgr::pllsrc::hsi_div2)) {
                source = frequency_hsi() * 0.5;
            } else {
                source = frequency_hse();
                if (rcc::cfgr::pllxtpre::test(rcc::cfgr::pllxtpre::div2)) {
                    source *= 0.5;
                }
            }

            auto multiplier = rcc::cfgr::pllmul::get();
            if (multiplier < 14) {
                source *= static_cast<double>(rcc::cfgr::pllmul::get()) + 2.0;
            } else {
                source *= 16.0;
            }

            return source;
        }

        inline static double frequency_sysclk() {
            using rcc = mtl::hw::rcc;
            if (rcc::cfgr::sw::test(rcc::cfgr::sw::hsi)) {
                return frequency_hsi();
            }
            if (rcc::cfgr::sw::test(rcc::cfgr::sw::hse)) {
                return frequency_hse();
            }
            return frequency_pllclk();
        }

        inline static double frequency_ahb() {
            using rcc = mtl::hw::rcc;
            auto value = rcc::cfgr::hpre::get();
            double divider;
            if (value < 8) {
                divider = 1.0;
            } else if (value < 12) {
                divider = static_cast<double>(1 << (value - 7));
            } else {
                divider = static_cast<double>(1 << (value - 6));
            }
            return frequency_sysclk() / divider;
        }

        inline static double frequency_hclk() { return frequency_ahb(); }

        inline static double frequency_cst() { return frequency_ahb() * 0.125; }

        inline static double frequency_fclk() { return frequency_ahb(); }

        inline static double frequency_apb1() {
            using rcc = mtl::hw::rcc;
            auto value = rcc::cfgr::ppre1::get();
            double divider;
            if (value < 4) {
                divider = 1.0;
            } else {
                divider = static_cast<double>(1 << (value - 3));
            }
            return frequency_ahb() / divider;
        }

        inline static double frequency_apb2() {
            using rcc = mtl::hw::rcc;
            auto value = rcc::cfgr::ppre2::get();
            double divider;
            if (value < 4) {
                divider = 1.0;
            } else {
                divider = static_cast<double>(1 << (value - 3));
            }
            return frequency_ahb() / divider;
        }

        inline static double frequency_hclk_div2() { return frequency_ahb() * 0.5; }

        inline static double frequency_pclk1() { return frequency_apb1(); }

        inline static double frequency_timclk1() {
            using rcc = mtl::hw::rcc;
            double multiplier = (rcc::cfgr::ppre1::get() < 4) ? 1.0 : 2.0;
            return frequency_apb1() * multiplier;
        }

        inline static double frequency_pclk2() { return frequency_apb2(); }

        inline static double frequency_timclk2() {
            using rcc = mtl::hw::rcc;
            double multiplier = (rcc::cfgr::ppre2::get() < 4) ? 1.0 : 2.0;
            return frequency_apb2() * multiplier;
        }

        inline double frequency_adcclk() {
            using rcc = mtl::hw::rcc;
            constexpr static double multiplier[4] = {0.5, 0.25, 1.0 / 6.0, 0.125};
            return frequency_apb2() * multiplier[rcc::cfgr::adcpre::get()];
        }

        // struct rtcclk {};
        // struct iwdgclk {};
        // struct flitfclk {};
        // struct usbclk {};
        // struct i2s3clk {};
        // struct i2s3clk {};
        // struct sdioclk {};
        // struct fsmcclk {};
    };
} // namespace mtl
