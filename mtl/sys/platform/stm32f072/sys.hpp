#pragma once

#include <cstdint>
#include <type_traits>

#include <mtl/common/parameters.hpp>
#include <mtl/hw/descriptor.hpp>
#include <mtl/hw/flash.hpp>
#include <mtl/hw/nvic.hpp>
#include <mtl/hw/rcc.hpp>
#include <mtl/sys/pwr.hpp>

extern "C" volatile uint32_t isr_table_address;

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

            static void remap() noexcept {
                // Temporary replaced with the copying of initial values (for debugging purposes).
                // for (auto &entry : ram_interrupt_table) {
                //	entry = reinterpret_cast<uint32_t>(&default_handler);
                // }
                auto source_table = reinterpret_cast<uint32_t *>(0);
                for (int i = 0; i < sizeof(ram_interrupt_table) / sizeof(ram_interrupt_table[0]); ++i) {
                    ram_interrupt_table[i] = source_table[i];
                }

                // Set new table pointer.
                isr_table_address = reinterpret_cast<uint32_t>(&ram_interrupt_table);
            }

        private:
            alignas(128 * sizeof(uint32_t)) // Number of interrupts rounded to the upper power of 2 value.
                inline static uint32_t ram_interrupt_table[73];

            // Default interrupt handler.
            __attribute__((naked)) inline static void default_handler() { __asm volatile("b	."); }
        };

        class services {
        public:
            static void initialize() noexcept {
                // Setup handler, clear and activate SVC interrupt.
                interrupts::set_handler<mtl::hw::interrupts::svc>(handler);
                // interrupts::clear<mtl::hw::interrupts::svc>();
                // interrupts::enable<mtl::hw::interrupts::svc>();
            }

            inline static void start_os() noexcept __attribute__((naked)) { asm volatile("svc	0\n"); }

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
                    : "r1", "r2", "r3", "r4", "r5", "r6", /*"r7", */"r8", "r9", "r10", "r11", "memory", "cc");
            }

            inline static void set_start_os_handler(void (*handler)()) noexcept {
                m_entries[0] = reinterpret_cast<uint32_t>(handler);
            }

            inline static void set_os_service_handler(void (*handler)()) noexcept {
                m_entries[1] = reinterpret_cast<uint32_t>(handler);
            }

        private:
            [[gnu::naked]] static void handler() noexcept {
                asm volatile("mov		r0, lr\n"
                             "movs		r2, #4\n"
                             "tst		r0, r2\n"
                             "bne		l1\n"
                             "mrs		r3, msp\n"
                             "b			l2\n"
                             "l1:\n"
                             "mrs		r3, psp\n"
                             "l2:\n"
                             "ldr		r0, [r3, #24]\n"
                             "sub		r0, r0, #2\n"
                             "ldr		r0, [r0]\n"
                             "movs		r2, #0xff\n"
                             "and		r0, r0, r2\n"
                             "lsl		r0, r0, #2\n"
                             "mov		r1, %[entries]\n"
                             "ldr		r1, [r1, r0]\n"
                             "bx		r1\n"
                             :
                             : [ entries ] "r"(reinterpret_cast<uint32_t>(&m_entries))
                             : "r0", "r2", "r3", "r4", "r5", "r6", /*"r7", */"r8", "r9", "r10", "r11", "memory", "cc");
            }

            static void os_service_default_handler() noexcept {}

            inline static uint32_t m_entries[2];
        };
    } // namespace detail

    template <class... t_parameters> class sys {
    public:
        using interrupts = detail::interrupts;
        using services = detail::services;

        // This method should be called before main() method.
        inline static void startup() noexcept {
            // Configure flash memory for high speed operation.
            mtl::hw::flash::acr::prftbe::set(mtl::hw::flash::acr::prftbe::enabled);
            mtl::hw::flash::acr::latency::set(mtl::hw::flash::acr::latency::one);
            while (!mtl::hw::flash::acr::latency::test(mtl::hw::flash::acr::latency::one))
                ;

            // Setup clocks for appropriate frequency.
            // Turn HSI on.
            mtl::hw::rcc::cr::hsion::set(mtl::hw::rcc::cr::hsion::on);
            while (!(mtl::hw::rcc::cr::hsirdy::test(mtl::hw::rcc::cr::hsirdy::ready)))
                ;

            // Configure PLL.
            mtl::hw::rcc::cfgr::pllmul::set(mtl::hw::rcc::cfgr::pllmul::mul8);
            // Turn PLL on.
            mtl::hw::rcc::cr::pllon::set(mtl::hw::rcc::cr::pllon::on);
            while (!(mtl::hw::rcc::cr::pllrdy::test(mtl::hw::rcc::cr::pllrdy::ready)))
                ;

            // Use PLL as a source for clocking.
            mtl::hw::rcc::cfgr::sw::set(mtl::hw::rcc::cfgr::sw::pll);

            // // Divide APB1 by 16.
            // devices::rcc::cfgr::ppre1::set(devices::rcc::cfgr::ppre1::by16);
        }

        inline static void initialize() noexcept {
            // Remap interrupt table.
            detail::interrupts::remap();
            // Initialize system services.
            detail::services::initialize();
            // Allow interrupts.
            detail::interrupts::enable();
        }

        inline static uint32_t initial_stack_pointer() noexcept {
            // Temporary replaced.
            // __asm volatile ("ldr	r0, =__initial_sp");
            // __asm volatile ("bx		lr");
            return reinterpret_cast<uint32_t *>(0)[0];
        }
    };
} // namespace mtl
