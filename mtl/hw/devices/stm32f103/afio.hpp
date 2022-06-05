#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace devices {
    namespace descriptor {
        template <uint32_t v_base_address> struct afio {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct evcr : register_<0x00, uint32_t> {
                struct pin : mtl::hw::field<evcr, 0, 4> {};

                struct port : mtl::hw::field<evcr, 4, 3> {
                    using option = mtl::hw::option<port>;
                    constexpr static option pa = 0;
                    constexpr static option pb = 1;
                    constexpr static option pc = 2;
                    constexpr static option pd = 3;
                    constexpr static option pe = 4;
                };

                struct evoe : mtl::hw::field<evcr, 7, 1> {
                    using option = mtl::hw::option<evoe>;
                    constexpr static option disable = 0;
                    constexpr static option enable = 1;
                };
            };

            struct mapr : register_<0x04, uint32_t> {
                struct spi1_remap : mtl::hw::field<mapr, 0, 1> {
                    using option = mtl::hw::option<spi1_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct 12c1_remap : mtl::hw::field<mapr, 1, 1> {
                    using option = mtl::hw::option<12c1_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct usart1_remap : mtl::hw::field<mapr, 2, 1> {
                    using option = mtl::hw::option<usart1_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct usart2_remap : mtl::hw::field<mapr, 3, 1> {
                    using option = mtl::hw::option<usart2_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct usart3_remap : mtl::hw::field<mapr, 4, 2> {
                    using option = mtl::hw::option<usart3_remap>;
                    constexpr static option no = 0;
                    constexpr static option partial = 1;
                    constexpr static option full = 3;
                };

                struct tim1_remap : mtl::hw::field<mapr, 6, 2> {
                    using option = mtl::hw::option<tim1_remap>;
                    constexpr static option no = 0;
                    constexpr static option partial = 1;
                    constexpr static option full = 3;
                };

                struct tim2_remap : mtl::hw::field<mapr, 8, 2> {
                    using option = mtl::hw::option<tim2_remap>;
                    constexpr static option no = 0;
                    constexpr static option partial1 = 1;
                    constexpr static option partial2 = 2;
                    constexpr static option full = 3;
                };

                struct tim3_remap : mtl::hw::field<mapr, 10, 2> {
                    using option = mtl::hw::option<tim3_remap>;
                    constexpr static option no = 0;
                    constexpr static option partial = 2;
                    constexpr static option full = 3;
                };

                struct tim4_remap : mtl::hw::field<mapr, 12, 1> {
                    using option = mtl::hw::option<tim4_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct can_remap : mtl::hw::field<mapr, 13, 2> {
                    using option = mtl::hw::option<can_remap>;
                    constexpr static option remap1 = 0;
                    constexpr static option remap2 = 2;
                    constexpr static option remap3 = 3;
                };

                struct pd0_remap : mtl::hw::field<mapr, 15, 1> {
                    using option = mtl::hw::option<pd0_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct tim5ch4_remap : mtl::hw::field<mapr, 16, 1> {
                    using option = mtl::hw::option<tim5ch4_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct adc1_etrginj_remap : mtl::hw::field<mapr, 17, 1> {
                    using option = mtl::hw::option<adc1_etrginj_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct adc1_etrgreg_remap : mtl::hw::field<mapr, 18, 1> {
                    using option = mtl::hw::option<adc1_etrgreg_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct adc2_etrginj_remap : mtl::hw::field<mapr, 19, 1> {
                    using option = mtl::hw::option<adc2_etrginj_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct adc2_etrgreg_remap : mtl::hw::field<mapr, 20, 1> {
                    using option = mtl::hw::option<adc2_etrgreg_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct swj_cfg : mtl::hw::field<mapr, 21, 1> {
                    using option = mtl::hw::option<swj_cfg>;
                    constexpr static option full = 0;
                    constexpr static option full_wo_njtrst = 1;
                    constexpr static option disable_jtag = 2;
                    constexpr static option disable_jtag_sw = 4;
                };
            };

            struct exticr1 : register_<0x08, uint32_t> {};
            struct exticr2 : register_<0x0c, uint32_t> {};
            struct exticr3 : register_<0x10, uint32_t> {};
            struct exticr4 : register_<0x14, uint32_t> {};

            struct mapr2 : register_<0x1c, uint32_t> {
                struct tim9_remap : mtl::hw::field<mapr2, 5, 1> {
                    using option = mtl::hw::option<tim9_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct tim10_remap : mtl::hw::field<mapr2, 6, 1> {
                    using option = mtl::hw::option<tim10_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct tim11_remap : mtl::hw::field<mapr2, 7, 1> {
                    using option = mtl::hw::option<tim11_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct tim13_remap : mtl::hw::field<mapr2, 8, 1> {
                    using option = mtl::hw::option<tim13_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct tim14_remap : mtl::hw::field<mapr2, 9, 1> {
                    using option = mtl::hw::option<tim14_remap>;
                    constexpr static option no = 0;
                    constexpr static option remap = 1;
                };

                struct fsmc_nadv : mtl::hw::field<mapr2, 10, 1> {
                    using option = mtl::hw::option<fsmc_nadv>;
                    constexpr static option connect = 0;
                    constexpr static option disconnect = 1;
                };
            };
        };
    } // namespace descriptor

    using afio = descriptor::afio<0x40010000>;
} // namespace devices
