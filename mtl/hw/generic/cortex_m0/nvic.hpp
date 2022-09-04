#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace mtl::hw {
    namespace descriptor {
        template <unsigned int v_base_address> struct nvic {
            constexpr static unsigned int base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct ictr : register_<0x004, uint32_t> {};

            struct stcsr : register_<0x010, uint32_t> {
                struct enable : mtl::hw::field<stcsr, 0, 1> {
                    using option = mtl::hw::option<enable>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct tickint : mtl::hw::field<stcsr, 1, 1> {
                    using option = mtl::hw::option<tickint>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct clksource : mtl::hw::field<stcsr, 2, 1> {
                    using option = mtl::hw::option<clksource>;
                    constexpr static option external = 0;
                    constexpr static option core = 1;
                };

                struct countflag : mtl::hw::field<stcsr, 16, 1> {
                    using option = mtl::hw::option<countflag>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };

            struct strvr : register_<0x014, uint32_t> {};
            struct stcvr : register_<0x018, uint32_t> {};
            struct stclvr : register_<0x01c, uint32_t> {};
            struct irqser : register_<0x100, uint32_t> {};
            struct irqcer : register_<0x180, uint32_t> {};
            struct irqspr : register_<0x200, uint32_t> {};
            struct irqcpr : register_<0x280, uint32_t> {};
            struct irq_0_3_pr : register_<0x400, uint32_t> {};
            struct irq_4_7_pr : register_<0x404, uint32_t> {};
            struct irq_8_11_pr : register_<0x408, uint32_t> {};
            struct irq_12_15_pr : register_<0x40c, uint32_t> {};
            struct irq_16_19_pr : register_<0x410, uint32_t> {};
            struct irq_20_23_pr : register_<0x414, uint32_t> {};
            struct irq_24_27_pr : register_<0x418, uint32_t> {};
            struct irq_28_31_pr : register_<0x41c, uint32_t> {};
        };
    } // namespace descriptor

    using nvic = descriptor::nvic<0xe000e000>;

    namespace interrupts {
        namespace detail {
            template <int v_register_index, int v_table_offset, class t_set_enable_register = void,
                      class t_clear_enable_register = void, class t_set_pending_register = void,
                      class t_clear_pending_register = void>
            struct interrupt {
                using set_enable_register = t_set_enable_register;
                using clear_enable_register = t_clear_enable_register;
                using set_pending_register = t_set_pending_register;
                using clear_pending_register = t_clear_pending_register;

                constexpr static auto register_index = v_register_index;
                constexpr static auto table_offset = v_table_offset;
            };
        } // namespace detail

        using nmi = detail::interrupt<-1, 2>;
        using hard_fault = detail::interrupt<-1, 3>;
        using svc = detail::interrupt<-1, 11>;
        using pend_sv = detail::interrupt<-1, 14>;
        using sys_tick = detail::interrupt<-1, 15>;

        using wwdg = detail::interrupt<0, 16, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using pvd_vddio2 = detail::interrupt<1, 17, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using rtc = detail::interrupt<2, 18, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using flash = detail::interrupt<3, 19, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using rcc_csr = detail::interrupt<4, 20, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using exti0_1 = detail::interrupt<5, 21, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using exti2_3 = detail::interrupt<6, 22, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using exti4_15 = detail::interrupt<7, 23, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using tsc = detail::interrupt<8, 24, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using dma_ch1 = detail::interrupt<9, 25, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using dma_ch2_3_dma2_ch1_2 = detail::interrupt<10, 26, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using dma_ch4_5_6_7_dma2_ch3_4_5 = detail::interrupt<11, 27, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using adc_comp = detail::interrupt<12, 28, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using tim1_brk_up_trg_com = detail::interrupt<13, 29, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using tim1_cc = detail::interrupt<14, 30, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using tim2 = detail::interrupt<15, 31, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using tim3 = detail::interrupt<16, 32, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using tim6_dac = detail::interrupt<17, 33, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using tim7 = detail::interrupt<18, 34, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using tim14 = detail::interrupt<19, 35, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using tim15 = detail::interrupt<20, 36, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using tim16 = detail::interrupt<21, 37, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using tim17 = detail::interrupt<22, 38, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using i2c1 = detail::interrupt<23, 39, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using i2c2 = detail::interrupt<24, 40, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using spi1 = detail::interrupt<25, 41, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using spi2 = detail::interrupt<26, 42, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using usart1 = detail::interrupt<27, 43, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using usart2 = detail::interrupt<28, 44, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using usart3_4_5_6_7_8 = detail::interrupt<29, 45, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using cec_can = detail::interrupt<30, 46, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
        using usb = detail::interrupt<31, 47, nvic::irqser, nvic::irqcer, nvic::irqspr, nvic::irqcpr>;
    } // namespace interrupts
} // namespace mtl::hw
