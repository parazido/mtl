#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace mtl::devices {
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
} // namespace mtl::devices
