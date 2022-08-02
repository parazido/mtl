#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace mtl::hw {
    namespace descriptor {
        template <uint32_t v_base_address> struct adc {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct sr : register_<0x00, uint32_t> {
                struct awd : mtl::hw::field<sr, 0, 1> {
                    using option = mtl::hw::option<awd>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct eoc : mtl::hw::field<sr, 1, 1> {
                    using option = mtl::hw::option<eoc>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct jeoc : mtl::hw::field<sr, 2, 1> {
                    using option = mtl::hw::option<jeoc>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct jstrt : mtl::hw::field<sr, 3, 1> {
                    using option = mtl::hw::option<jstrt>;
                    constexpr static option start = 1;
                };

                struct strt : mtl::hw::field<sr, 4, 1> {
                    using option = mtl::hw::option<strt>;
                    constexpr static option start = 1;
                };
            };

            struct cr1 : register_<0x04, uint32_t> {
                struct awdch : mtl::hw::field<cr1, 0, 5> {};

                struct eocie : mtl::hw::field<cr1, 6, 1> {
                    using option = mtl::hw::option<eocie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct awdie : mtl::hw::field<cr1, 7, 1> {
                    using option = mtl::hw::option<awdie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct jocie : mtl::hw::field<cr1, 8, 1> {
                    using option = mtl::hw::option<jocie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct adwsgl : mtl::hw::field<cr1, 9, 1> {
                    using option = mtl::hw::option<adwsgl>;
                    constexpr static option all = 0;
                    constexpr static option single = 1;
                };

                struct jauto : mtl::hw::field<cr1, 10, 1> {
                    using option = mtl::hw::option<jauto>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct discen : mtl::hw::field<cr1, 11, 1> {
                    using option = mtl::hw::option<discen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct jdiscen : mtl::hw::field<cr1, 12, 1> {
                    using option = mtl::hw::option<jdiscen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                // struct jdiscen : mtl::hw::field<cr1, 13, 3> {};

                struct dualmod : mtl::hw::field<cr1, 16, 4> {
                    using option = mtl::hw::option<dualmod>;
                    constexpr static option independent = 0;
                    constexpr static option rsis = 1;
                    constexpr static option rsat = 2;
                    constexpr static option isfi = 3;
                    constexpr static option issi = 4;
                    constexpr static option iso = 5;
                    constexpr static option rso = 6;
                    constexpr static option fio = 7;
                    constexpr static option sio = 8;
                    constexpr static option ato = 9;
                };

                struct jawden : mtl::hw::field<cr1, 22, 1> {
                    using option = mtl::hw::option<jawden>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct awden : mtl::hw::field<cr1, 23, 1> {
                    using option = mtl::hw::option<awden>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct cr2 : register_<0x08, uint32_t> {
                struct adon : mtl::hw::field<cr2, 0, 1> {
                    using option = mtl::hw::option<adon>;
                    constexpr static option off = 0;
                    constexpr static option on = 1;
                };

                struct cont : mtl::hw::field<cr2, 1, 1> {
                    using option = mtl::hw::option<cont>;
                    constexpr static option single = 0;
                    constexpr static option continuous = 1;
                };

                struct cal : mtl::hw::field<cr2, 2, 1> {
                    using option = mtl::hw::option<cal>;
                    constexpr static option completed = 0;
                    constexpr static option enabled = 1;
                };

                struct rstcal : mtl::hw::field<cr2, 3, 1> {
                    using option = mtl::hw::option<rstcal>;
                    constexpr static option initialized = 0;
                    constexpr static option initialize = 1;
                };

                struct dma : mtl::hw::field<cr2, 8, 1> {
                    using option = mtl::hw::option<dma>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct align : mtl::hw::field<cr2, 11, 1> {
                    using option = mtl::hw::option<align>;
                    constexpr static option right = 0;
                    constexpr static option left = 1;
                };

                struct jextsel : mtl::hw::field<cr2, 12, 3> {
                    using option = mtl::hw::option<jextsel>;
                    constexpr static option tim1_trgo = 0;
                    constexpr static option tim1_cc4 = 1;
                    constexpr static option tim2_trgo = 2;
                    constexpr static option tim2_cc1 = 3;
                    constexpr static option tim3_cc4 = 4;
                    constexpr static option tim4_trgo = 5;
                    constexpr static option exti_15_tim8_cc4 = 6;
                    constexpr static option jswstart = 7;
                };

                struct jexttrig : mtl::hw::field<cr2, 15, 1> {
                    using option = mtl::hw::option<jexttrig>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct extsel : mtl::hw::field<cr2, 17, 3> {
                    using option = mtl::hw::option<extsel>;
                    constexpr static option tim1_cc1 = 0;
                    constexpr static option tim1_cc2 = 1;
                    constexpr static option tim1_cc3 = 2;
                    constexpr static option tim2_cc2 = 3;
                    constexpr static option tim3_trgo = 4;
                    constexpr static option tim4_cc4 = 5;
                    constexpr static option exti_11_tim8_tgro = 6;
                    constexpr static option swstart = 7;
                };

                struct exttrig : mtl::hw::field<cr2, 20, 1> {
                    using option = mtl::hw::option<exttrig>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct jswstart : mtl::hw::field<cr2, 21, 1> {
                    using option = mtl::hw::option<jswstart>;
                    constexpr static option start = 1;
                };

                struct swstart : mtl::hw::field<cr2, 22, 1> {
                    using option = mtl::hw::option<swstart>;
                    constexpr static option start = 1;
                };

                struct tsvrefe : mtl::hw::field<cr2, 23, 1> {
                    using option = mtl::hw::option<tsvrefe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            template <uint8_t v_reg_index> struct smpr : register_<0x04 * v_reg_index + 0x0c, uint32_t> {
                template <uint8_t v_index> struct smp : mtl::hw::field<smpr, v_index * 3, 3> {
                    using option = mtl::hw::option<smp>;
                    constexpr static option cycles_1_5 = 0;
                    constexpr static option cycles_7_5 = 1;
                    constexpr static option cycles_13_5 = 2;
                    constexpr static option cycles_28_5 = 3;
                    constexpr static option cycles_41_5 = 4;
                    constexpr static option cycles_55_5 = 5;
                    constexpr static option cycles_71_5 = 6;
                    constexpr static option cycles_239_5 = 7;
                };
            };

            template <uint8_t v_reg_index> struct jofr : register_<0x04 * v_reg_index + 0x14, uint32_t> {
                struct joffset : mtl::hw::field<jofr, 0, 12> {};
            };

            struct htr : register_<0x24, uint32_t> {
                struct ht : mtl::hw::field<htr, 0, 12> {};
            };

            struct ltr : register_<0x28, uint32_t> {
                struct lt : mtl::hw::field<ltr, 0, 12> {};
            };

            template <uint8_t v_reg_index> struct sqr : register_<0x04 * v_reg_index + 0x2c, uint32_t> {
                template <uint8_t v_index> struct sq : mtl::hw::field<sqr, v_index * 4, 4> {};
            };

            // template <> struct sqr<0> : register_<0x2c, uint32_t> {
            //     template <uint8_t v_index> struct sq : mtl::hw::field<sqr, v_index * 4, 4> {};
            //     struct l : mtl::hw::field<l, 20, 4> {};
            // };

            struct jsqr : register_<0x38, uint32_t> {
                template <uint8_t v_index> struct jsq : mtl::hw::field<jsqr, v_index * 5, 5> {};
                struct jl : mtl::hw::field<jsqr, 20, 2> {};
            };

            template <uint8_t v_reg_index> struct jdr : register_<0x04 * v_reg_index + 0x3c, uint32_t> {
                struct jdata : mtl::hw::field<jdr, 0, 16> {};
            };

            struct dr : register_<0x4c, uint32_t> {
                struct data : mtl::hw::field<dr, 0, 16> {};
                struct adc2data : mtl::hw::field<dr, 16, 16> {};
            };
        };
    }; // namespace descriptor

    using adc1 = descriptor::adc<0x40012400>;
    using adc2 = descriptor::adc<0x40012800>;
} // namespace mtl::hw
