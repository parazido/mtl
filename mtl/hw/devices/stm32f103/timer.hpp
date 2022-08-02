#pragma once

#include <cstdint>

#include <mtl/hw/descriptor.hpp>
#include <mtl/hw/device.hpp>

namespace mtl::hw {
    namespace descriptor {
        template <uint32_t v_base_address> struct timer_1_8 {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct cr1 : register_<0x00, uint32_t> {
                struct cen : mtl::hw::field<cr1, 0, 1> {
                    using option = mtl::hw::option<cen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct udis : mtl::hw::field<cr1, 1, 1> {
                    using option = mtl::hw::option<udis>;
                    constexpr static option uev_enabled = 0;
                    constexpr static option uev_disabled = 1;
                };

                struct urs : mtl::hw::field<cr1, 2, 1> {
                    using option = mtl::hw::option<urs>;
                    constexpr static option any = 0;
                    constexpr static option counter_uo = 1;
                };

                struct opm : mtl::hw::field<cr1, 3, 1> {
                    using option = mtl::hw::option<opm>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct dir : mtl::hw::field<cr1, 4, 1> {
                    using option = mtl::hw::option<dir>;
                    constexpr static option upcount = 0;
                    constexpr static option downcount = 1;
                };

                struct cms : mtl::hw::field<cr1, 5, 2> {
                    using option = mtl::hw::option<cms>;
                    constexpr static option edge = 0;
                    constexpr static option center1 = 1;
                    constexpr static option center2 = 2;
                    constexpr static option center3 = 3;
                };

                struct arpe : mtl::hw::field<cr1, 7, 1> {
                    using option = mtl::hw::option<arpe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ckd : mtl::hw::field<cr1, 8, 2> {
                    using option = mtl::hw::option<ckd>;
                    constexpr static option nomul = 0;
                    constexpr static option mul2 = 1;
                    constexpr static option mul4 = 2;
                };
            };

            struct cr2 : register_<0x04, uint32_t> {
                struct ccpc : mtl::hw::field<cr2, 0, 1> {
                    using option = mtl::hw::option<ccpc>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ccus : mtl::hw::field<cr2, 2, 1> {
                    using option = mtl::hw::option<ccus>;
                    constexpr static option comg_only = 0;
                    constexpr static option comg_trgi = 1;
                };

                struct ccds : mtl::hw::field<cr2, 3, 1> {
                    using option = mtl::hw::option<ccds>;
                    constexpr static option cc_event = 0;
                    constexpr static option update_event = 1;
                };

                struct mms : mtl::hw::field<cr2, 4, 3> {
                    using option = mtl::hw::option<mms>;
                    constexpr static option reset = 0;
                    constexpr static option enable = 1;
                    constexpr static option update = 2;
                    constexpr static option compare_pulse = 3;
                    constexpr static option compare1 = 4;
                    constexpr static option compare2 = 5;
                    constexpr static option compare3 = 6;
                    constexpr static option compare4 = 7;
                };

                struct ti1s : mtl::hw::field<cr2, 7, 1> {
                    using option = mtl::hw::option<ti1s>;
                    constexpr static option ch1 = 0;
                    constexpr static option ch1_2_3 = 1;
                };

                struct ois1 : mtl::hw::field<cr2, 8, 1> {
                    using option = mtl::hw::option<ois1>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };

                struct ois1n : mtl::hw::field<cr2, 9, 1> {
                    using option = mtl::hw::option<ois1n>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };

                struct ois2 : mtl::hw::field<cr2, 10, 1> {
                    using option = mtl::hw::option<ois2>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };

                struct ois2n : mtl::hw::field<cr2, 11, 1> {
                    using option = mtl::hw::option<ois2n>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };

                struct ois3 : mtl::hw::field<cr2, 12, 1> {
                    using option = mtl::hw::option<ois3>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };

                struct ois3n : mtl::hw::field<cr2, 13, 1> {
                    using option = mtl::hw::option<ois3n>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };

                struct ois4 : mtl::hw::field<cr2, 14, 1> {
                    using option = mtl::hw::option<ois4>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };
            };

            struct smcr : register_<0x08, uint32_t> {
                struct sms : mtl::hw::field<smcr, 0, 3> {
                    using option = mtl::hw::option<sms>;
                    constexpr static option disabled = 0;
                    constexpr static option encoder1 = 1;
                    constexpr static option encoder2 = 2;
                    constexpr static option encoder3 = 3;
                    constexpr static option reset = 4;
                    constexpr static option gated = 5;
                    constexpr static option trigger = 6;
                    constexpr static option external_clock = 7;
                };

                struct ts : mtl::hw::field<smcr, 4, 3> {
                    using option = mtl::hw::option<ts>;
                    constexpr static option itr0 = 0;
                    constexpr static option itr1 = 1;
                    constexpr static option itr2 = 2;
                    constexpr static option itr3 = 3;
                    constexpr static option ti1f_ed = 4;
                    constexpr static option ti1fp1 = 5;
                    constexpr static option ti1fp2 = 6;
                    constexpr static option etrf = 7;
                };

                struct msm : mtl::hw::field<smcr, 7, 1> {
                    using option = mtl::hw::option<msm>;
                    constexpr static option no = 0;
                    constexpr static option delayed = 1;
                };

                struct etf : mtl::hw::field<smcr, 8, 4> {
                    using option = mtl::hw::option<etf>;
                    constexpr static option no_filter = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                struct etps : mtl::hw::field<smcr, 12, 2> {
                    using option = mtl::hw::option<etps>;
                    constexpr static option nodiv = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ece : mtl::hw::field<smcr, 14, 1> {
                    using option = mtl::hw::option<ece>;
                    constexpr static option disabled = 0;
                    constexpr static option ebabled = 1;
                };

                struct etp : mtl::hw::field<smcr, 15, 1> {
                    using option = mtl::hw::option<etp>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };
            };

            struct dier : register_<0x0c, uint32_t> {
                struct uie : mtl::hw::field<dier, 0, 1> {
                    using option = mtl::hw::option<uie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc1ie : mtl::hw::field<dier, 1, 1> {
                    using option = mtl::hw::option<cc1ie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc2ie : mtl::hw::field<dier, 2, 1> {
                    using option = mtl::hw::option<cc2ie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc3ie : mtl::hw::field<dier, 3, 1> {
                    using option = mtl::hw::option<cc3ie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc4ie : mtl::hw::field<dier, 4, 1> {
                    using option = mtl::hw::option<cc4ie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct comie : mtl::hw::field<dier, 5, 1> {
                    using option = mtl::hw::option<comie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct tie : mtl::hw::field<dier, 6, 1> {
                    using option = mtl::hw::option<tie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct bie : mtl::hw::field<dier, 7, 1> {
                    using option = mtl::hw::option<bie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ude : mtl::hw::field<dier, 8, 1> {
                    using option = mtl::hw::option<ude>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc1de : mtl::hw::field<dier, 9, 1> {
                    using option = mtl::hw::option<cc1de>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc2de : mtl::hw::field<dier, 10, 1> {
                    using option = mtl::hw::option<cc2de>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc3de : mtl::hw::field<cc3de, 11, 1> {
                    using option = mtl::hw::option<ude>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc4de : mtl::hw::field<dier, 12, 1> {
                    using option = mtl::hw::option<cc4de>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct comde : mtl::hw::field<dier, 13, 1> {
                    using option = mtl::hw::option<comde>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct tde : mtl::hw::field<dier, 14, 1> {
                    using option = mtl::hw::option<tde>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct sr : register_<0x10, uint32_t> {
                struct uif : mtl::hw::field<sr, 0, 1> {
                    using option = mtl::hw::option<uif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc1if : mtl::hw::field<sr, 1, 1> {
                    using option = mtl::hw::option<cc1if>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc2if : mtl::hw::field<sr, 2, 1> {
                    using option = mtl::hw::option<cc2if>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc3if : mtl::hw::field<sr, 3, 1> {
                    using option = mtl::hw::option<cc3if>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc4if : mtl::hw::field<sr, 4, 1> {
                    using option = mtl::hw::option<cc4if>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct comif : mtl::hw::field<sr, 5, 1> {
                    using option = mtl::hw::option<comif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct tif : mtl::hw::field<sr, 6, 1> {
                    using option = mtl::hw::option<tif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct bif : mtl::hw::field<sr, 7, 1> {
                    using option = mtl::hw::option<bif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc1of : mtl::hw::field<sr, 9, 1> {
                    using option = mtl::hw::option<cc1of>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc2of : mtl::hw::field<sr, 10, 1> {
                    using option = mtl::hw::option<cc2of>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc3of : mtl::hw::field<sr, 11, 1> {
                    using option = mtl::hw::option<cc3of>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc4of : mtl::hw::field<sr, 12, 1> {
                    using option = mtl::hw::option<cc4of>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };

            struct egr : register_<0x14, uint32_t> {
                struct ug : mtl::hw::field<egr, 0, 1> {
                    using option = mtl::hw::option<ug>;
                    constexpr static option set = 1;
                };

                struct cc1g : mtl::hw::field<egr, 1, 1> {
                    using option = mtl::hw::option<cc1g>;
                    constexpr static option set = 1;
                };

                struct cc2g : mtl::hw::field<egr, 2, 1> {
                    using option = mtl::hw::option<cc2g>;
                    constexpr static option set = 1;
                };

                struct cc3g : mtl::hw::field<egr, 3, 1> {
                    using option = mtl::hw::option<cc3g>;
                    constexpr static option set = 1;
                };

                struct cc4g : mtl::hw::field<egr, 4, 1> {
                    using option = mtl::hw::option<cc4g>;
                    constexpr static option set = 1;
                };

                struct comg : mtl::hw::field<egr, 5, 1> {
                    using option = mtl::hw::option<comg>;
                    constexpr static option set = 1;
                };

                struct tg : mtl::hw::field<egr, 6, 1> {
                    using option = mtl::hw::option<tg>;
                    constexpr static option set = 1;
                };

                struct bg : mtl::hw::field<egr, 7, 1> {
                    using option = mtl::hw::option<bg>;
                    constexpr static option set = 1;
                };
            };

            struct ccmr1 : register_<0x18, uint32_t> {
                // Common fields.
                struct cc1s : mtl::hw::field<ccmr1, 0, 2> {
                    using option = mtl::hw::option<cc1s>;
                    constexpr static option output = 0;
                    constexpr static option input_ti1 = 1;
                    constexpr static option input_ti2 = 2;
                    constexpr static option input_trc = 3;
                };

                // Input capture mode fields.
                struct ic1psc : mtl::hw::field<ccmr1, 2, 2> {
                    using option = mtl::hw::option<ic1psc>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ic1f : mtl::hw::field<ccmr1, 4, 4> {
                    using option = mtl::hw::option<ic1f>;
                    constexpr static option no = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                // Common fields.
                struct cc2s : mtl::hw::field<ccmr1, 8, 2> {
                    using option = mtl::hw::option<cc2s>;
                    constexpr static option output = 0;
                    constexpr static option input_ti2 = 1;
                    constexpr static option input_ti1 = 2;
                    constexpr static option input_trc = 3;
                };

                // Input capture mode fields.
                struct ic2psc : mtl::hw::field<ccmr1, 10, 2> {
                    using option = mtl::hw::option<ic2psc>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ic2f : mtl::hw::field<ccmr1, 12, 4> {
                    using option = mtl::hw::option<ic2f>;
                    constexpr static option no = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                // Output compare mode fields.
                struct oc1fe : mtl::hw::field<ccmr1, 2, 1> {
                    using option = mtl::hw::option<oc1fe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc1pe : mtl::hw::field<ccmr1, 3, 1> {
                    using option = mtl::hw::option<oc1pe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc1m : mtl::hw::field<ccmr1, 4, 3> {
                    using option = mtl::hw::option<oc1m>;
                    constexpr static option frozen = 0;
                    constexpr static option active = 1;
                    constexpr static option inactive = 2;
                    constexpr static option toggle = 3;
                    constexpr static option force_inactive = 4;
                    constexpr static option force_active = 5;
                    constexpr static option pwm1 = 6;
                    constexpr static option pwm2 = 7;
                };

                struct oc1ce : mtl::hw::field<ccmr1, 7, 1> {
                    using option = mtl::hw::option<oc1ce>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc2fe : mtl::hw::field<ccmr1, 10, 1> {
                    using option = mtl::hw::option<oc2fe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc2pe : mtl::hw::field<ccmr1, 11, 1> {
                    using option = mtl::hw::option<oc2pe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc2m : mtl::hw::field<ccmr1, 12, 3> {
                    using option = mtl::hw::option<oc2m>;
                    constexpr static option frozen = 0;
                    constexpr static option active = 1;
                    constexpr static option inactive = 2;
                    constexpr static option toggle = 3;
                    constexpr static option force_inactive = 4;
                    constexpr static option force_active = 5;
                    constexpr static option pwm1 = 6;
                    constexpr static option pwm2 = 7;
                };

                struct oc2ce : mtl::hw::field<ccmr1, 15, 1> {
                    using option = mtl::hw::option<oc2ce>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct ccmr2 : register_<0x1c, uint32_t> {
                // Common fields.
                struct cc3s : mtl::hw::field<ccmr2, 0, 2> {
                    using option = mtl::hw::option<cc3s>;
                    constexpr static option output = 0;
                    constexpr static option input_ti3 = 1;
                    constexpr static option input_ti4 = 2;
                    constexpr static option input_trc = 3;
                };

                // Input capture mode fields.
                struct ic3psc : mtl::hw::field<ccmr2, 2, 2> {
                    using option = mtl::hw::option<ic3psc>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ic3f : mtl::hw::field<ccmr2, 4, 4> {
                    using option = mtl::hw::option<ic3f>;
                    constexpr static option no = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                // Common fields.
                struct cc4s : mtl::hw::field<ccmr2, 8, 2> {
                    using option = mtl::hw::option<cc4s>;
                    constexpr static option output = 0;
                    constexpr static option input_ti4 = 1;
                    constexpr static option input_ti3 = 2;
                    constexpr static option input_trc = 3;
                };

                // Input capture mode fields.
                struct ic4psc : mtl::hw::field<ccmr2, 10, 2> {
                    using option = mtl::hw::option<ic4psc>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ic4f : mtl::hw::field<ccmr2, 12, 4> {
                    using option = mtl::hw::option<ic4f>;
                    constexpr static option no = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                // Output compare mode fields.
                struct oc3fe : mtl::hw::field<ccmr2, 2, 1> {
                    using option = mtl::hw::option<oc3fe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc3pe : mtl::hw::field<ccmr2, 3, 1> {
                    using option = mtl::hw::option<oc3pe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc3m : mtl::hw::field<ccmr2, 4, 3> {
                    using option = mtl::hw::option<oc3m>;
                    constexpr static option frozen = 0;
                    constexpr static option active = 1;
                    constexpr static option inactive = 2;
                    constexpr static option toggle = 3;
                    constexpr static option force_inactive = 4;
                    constexpr static option force_active = 5;
                    constexpr static option pwm1 = 6;
                    constexpr static option pwm2 = 7;
                };

                struct oc3ce : mtl::hw::field<ccmr2, 7, 1> {
                    using option = mtl::hw::option<oc3ce>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc4fe : mtl::hw::field<ccmr2, 10, 1> {
                    using option = mtl::hw::option<oc4fe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc4pe : mtl::hw::field<ccmr2, 11, 1> {
                    using option = mtl::hw::option<oc4pe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc4m : mtl::hw::field<ccmr2, 12, 3> {
                    using option = mtl::hw::option<oc4m>;
                    constexpr static option frozen = 0;
                    constexpr static option active = 1;
                    constexpr static option inactive = 2;
                    constexpr static option toggle = 3;
                    constexpr static option force_inactive = 4;
                    constexpr static option force_active = 5;
                    constexpr static option pwm1 = 6;
                    constexpr static option pwm2 = 7;
                };

                struct oc4ce : mtl::hw::field<ccmr2, 15, 1> {
                    using option = mtl::hw::option<oc4ce>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct ccer : register_<0x20, uint32_t> {
                struct cc1e : mtl::hw::field<ccer, 0, 1> {
                    using option = mtl::hw::option<cc1e>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc1p : mtl::hw::field<ccer, 1, 1> {
                    using option = mtl::hw::option<cc1p>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };

                struct cc1ne : mtl::hw::field<ccer, 2, 1> {
                    using option = mtl::hw::option<cc1ne>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc1np : mtl::hw::field<ccer, 3, 1> {
                    using option = mtl::hw::option<cc1np>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };

                struct cc2e : mtl::hw::field<ccer, 4, 1> {
                    using option = mtl::hw::option<cc2e>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc2p : mtl::hw::field<ccer, 5, 1> {
                    using option = mtl::hw::option<cc2p>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };

                struct cc2ne : mtl::hw::field<ccer, 6, 1> {
                    using option = mtl::hw::option<cc2ne>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc2np : mtl::hw::field<ccer, 7, 1> {
                    using option = mtl::hw::option<cc2np>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };

                struct cc3e : mtl::hw::field<ccer, 8, 1> {
                    using option = mtl::hw::option<cc3e>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc3p : mtl::hw::field<ccer, 9, 1> {
                    using option = mtl::hw::option<cc3p>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };

                struct cc3ne : mtl::hw::field<ccer, 10, 1> {
                    using option = mtl::hw::option<cc3ne>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc3np : mtl::hw::field<ccer, 11, 1> {
                    using option = mtl::hw::option<cc3np>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };

                struct cc4e : mtl::hw::field<ccer, 12, 1> {
                    using option = mtl::hw::option<cc4e>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc4p : mtl::hw::field<ccer, 13, 1> {
                    using option = mtl::hw::option<cc4p>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };

                struct cc4ne : mtl::hw::field<ccer, 14, 1> {
                    using option = mtl::hw::option<cc4ne>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc4np : mtl::hw::field<ccer, 15, 1> {
                    using option = mtl::hw::option<cc4np>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };
            };

            struct cnt : register_<0x24, uint16_t> {};
            struct psc : register_<0x28, uint16_t> {};
            struct arr : register_<0x2c, uint16_t> {};
            struct rcr : register_<0x30, uint16_t> {
                struct rep : mtl::hw::field<rcr, 0, 8> {};
            };
            struct ccr1 : register_<0x34, uint16_t> {};
            struct ccr2 : register_<0x38, uint16_t> {};
            struct ccr3 : register_<0x3c, uint16_t> {};
            struct ccr4 : register_<0x40, uint16_t> {};

            struct bdtr : register_<0x44, uint16_t> {
                struct dtg : mtl::hw::field<bdtr, 0, 8> {};
                struct lock : mtl::hw::field<bdtr, 8, 2> {
                    using option = mtl::hw::option<lock>;
                    constexpr static option off = 0;
                    constexpr static option level1 = 1;
                    constexpr static option level2 = 2;
                    constexpr static option level3 = 3;
                };

                struct ossi : mtl::hw::field<bdtr, 10, 1> {
                    using option = mtl::hw::option<ossi>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ossr : mtl::hw::field<bdtr, 11, 1> {
                    using option = mtl::hw::option<ossr>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct bke : mtl::hw::field<bdtr, 12, 1> {
                    using option = mtl::hw::option<bke>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct bkp : mtl::hw::field<bdtr, 13, 1> {
                    using option = mtl::hw::option<bkp>;
                    constexpr static option low = 0;
                    constexpr static option high = 1;
                };

                struct aoe : mtl::hw::field<bdtr, 14, 1> {
                    using option = mtl::hw::option<aoe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct moe : mtl::hw::field<bdtr, 15, 1> {
                    using option = mtl::hw::option<moe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct dcr : register_<0x48, uint16_t> {
                struct dba : mtl::hw::field<dcr, 0, 5> {};
                struct dbl : mtl::hw::field<dcr, 8, 5> {};
            };

            struct dmar : register_<0x4c, uint32_t> {};
        };

        template <uint32_t v_base_address> struct timer_2_5 {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct cr1 : register_<0x00, uint32_t> {
                struct cen : mtl::hw::field<cr1, 0, 1> {
                    using option = mtl::hw::option<cen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct udis : mtl::hw::field<cr1, 1, 1> {
                    using option = mtl::hw::option<udis>;
                    constexpr static option uev_enabled = 0;
                    constexpr static option uev_disabled = 1;
                };

                struct urs : mtl::hw::field<cr1, 2, 1> {
                    using option = mtl::hw::option<urs>;
                    constexpr static option any = 0;
                    constexpr static option counter_uo = 1;
                };

                struct opm : mtl::hw::field<cr1, 3, 1> {
                    using option = mtl::hw::option<opm>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct dir : mtl::hw::field<cr1, 4, 1> {
                    using option = mtl::hw::option<dir>;
                    constexpr static option upcount = 0;
                    constexpr static option downcount = 1;
                };

                struct cms : mtl::hw::field<cr1, 5, 2> {
                    using option = mtl::hw::option<cms>;
                    constexpr static option edge = 0;
                    constexpr static option center1 = 1;
                    constexpr static option center2 = 2;
                    constexpr static option center3 = 3;
                };

                struct arpe : mtl::hw::field<cr1, 7, 1> {
                    using option = mtl::hw::option<arpe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ckd : mtl::hw::field<cr1, 8, 2> {
                    using option = mtl::hw::option<ckd>;
                    constexpr static option nomul = 0;
                    constexpr static option mul2 = 1;
                    constexpr static option mul4 = 2;
                };
            };

            struct cr2 : register_<0x04, uint32_t> {
                struct ccds : mtl::hw::field<cr2, 3, 1> {
                    using option = mtl::hw::option<ccds>;
                    constexpr static option cc_event = 0;
                    constexpr static option update_event = 1;
                };

                struct mms : mtl::hw::field<cr2, 4, 3> {
                    using option = mtl::hw::option<mms>;
                    constexpr static option reset = 0;
                    constexpr static option enable = 1;
                    constexpr static option update = 2;
                    constexpr static option compare_pulse = 3;
                    constexpr static option compare1 = 4;
                    constexpr static option compare2 = 5;
                    constexpr static option compare3 = 6;
                    constexpr static option compare4 = 7;
                };

                struct ti1s : mtl::hw::field<cr2, 7, 1> {
                    using option = mtl::hw::option<ti1s>;
                    constexpr static option ch1 = 0;
                    constexpr static option ch1_2_3 = 1;
                };
            };

            struct smcr : register_<0x08, uint32_t> {
                struct sms : mtl::hw::field<smcr, 0, 3> {
                    using option = mtl::hw::option<sms>;
                    constexpr static option disabled = 0;
                    constexpr static option encoder1 = 1;
                    constexpr static option encoder2 = 2;
                    constexpr static option encoder3 = 3;
                    constexpr static option reset = 4;
                    constexpr static option gated = 5;
                    constexpr static option trigger = 6;
                    constexpr static option external_clock = 7;
                };

                struct ts : mtl::hw::field<smcr, 4, 3> {
                    using option = mtl::hw::option<ts>;
                    constexpr static option itr0 = 0;
                    constexpr static option itr1 = 1;
                    constexpr static option itr2 = 2;
                    constexpr static option itr3 = 3;
                    constexpr static option ti1f_ed = 4;
                    constexpr static option ti1fp1 = 5;
                    constexpr static option ti1fp2 = 6;
                    constexpr static option etrf = 7;
                };

                struct msm : mtl::hw::field<smcr, 7, 1> {
                    using option = mtl::hw::option<msm>;
                    constexpr static option no = 0;
                    constexpr static option delayed = 1;
                };

                struct etf : mtl::hw::field<smcr, 8, 4> {
                    using option = mtl::hw::option<etf>;
                    constexpr static option no_filter = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                struct etps : mtl::hw::field<smcr, 12, 2> {
                    using option = mtl::hw::option<etps>;
                    constexpr static option nodiv = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ece : mtl::hw::field<smcr, 14, 1> {
                    using option = mtl::hw::option<ece>;
                    constexpr static option disabled = 0;
                    constexpr static option ebabled = 1;
                };

                struct etp : mtl::hw::field<smcr, 15, 1> {
                    using option = mtl::hw::option<etp>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };
            };

            struct dier : register_<0x0c, uint32_t> {
                struct uie : mtl::hw::field<dier, 0, 1> {
                    using option = mtl::hw::option<uie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc1ie : mtl::hw::field<dier, 1, 1> {
                    using option = mtl::hw::option<cc1ie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc2ie : mtl::hw::field<dier, 2, 1> {
                    using option = mtl::hw::option<cc2ie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc3ie : mtl::hw::field<dier, 3, 1> {
                    using option = mtl::hw::option<cc3ie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc4ie : mtl::hw::field<dier, 4, 1> {
                    using option = mtl::hw::option<cc4ie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct tie : mtl::hw::field<dier, 6, 1> {
                    using option = mtl::hw::option<tie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ude : mtl::hw::field<dier, 8, 1> {
                    using option = mtl::hw::option<ude>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc1de : mtl::hw::field<dier, 9, 1> {
                    using option = mtl::hw::option<cc1de>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc2de : mtl::hw::field<dier, 10, 1> {
                    using option = mtl::hw::option<cc2de>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc3de : mtl::hw::field<cc3de, 11, 1> {
                    using option = mtl::hw::option<ude>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc4de : mtl::hw::field<dier, 12, 1> {
                    using option = mtl::hw::option<cc4de>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct tde : mtl::hw::field<dier, 14, 1> {
                    using option = mtl::hw::option<tde>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct sr : register_<0x10, uint32_t> {
                struct uif : mtl::hw::field<sr, 0, 1> {
                    using option = mtl::hw::option<uif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc1if : mtl::hw::field<sr, 1, 1> {
                    using option = mtl::hw::option<cc1if>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc2if : mtl::hw::field<sr, 2, 1> {
                    using option = mtl::hw::option<cc2if>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc3if : mtl::hw::field<sr, 3, 1> {
                    using option = mtl::hw::option<cc3if>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc4if : mtl::hw::field<sr, 4, 1> {
                    using option = mtl::hw::option<cc4if>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct tif : mtl::hw::field<sr, 6, 1> {
                    using option = mtl::hw::option<tif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc1of : mtl::hw::field<sr, 9, 1> {
                    using option = mtl::hw::option<cc1of>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc2of : mtl::hw::field<sr, 10, 1> {
                    using option = mtl::hw::option<cc2of>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc3of : mtl::hw::field<sr, 11, 1> {
                    using option = mtl::hw::option<cc3of>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc4of : mtl::hw::field<sr, 12, 1> {
                    using option = mtl::hw::option<cc4of>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };

            struct egr : register_<0x14, uint32_t> {
                struct ug : mtl::hw::field<egr, 0, 1> {
                    using option = mtl::hw::option<ug>;
                    constexpr static option set = 1;
                };

                struct cc1g : mtl::hw::field<egr, 1, 1> {
                    using option = mtl::hw::option<cc1g>;
                    constexpr static option set = 1;
                };

                struct cc2g : mtl::hw::field<egr, 2, 1> {
                    using option = mtl::hw::option<cc2g>;
                    constexpr static option set = 1;
                };

                struct cc3g : mtl::hw::field<egr, 3, 1> {
                    using option = mtl::hw::option<cc3g>;
                    constexpr static option set = 1;
                };

                struct cc4g : mtl::hw::field<egr, 4, 1> {
                    using option = mtl::hw::option<cc4g>;
                    constexpr static option set = 1;
                };

                struct tg : mtl::hw::field<egr, 6, 1> {
                    using option = mtl::hw::option<tg>;
                    constexpr static option set = 1;
                };
            };

            struct ccmr1 : register_<0x18, uint32_t> {
                // Common fields.
                struct cc1s : mtl::hw::field<ccmr1, 0, 2> {
                    using option = mtl::hw::option<cc1s>;
                    constexpr static option output = 0;
                    constexpr static option input_ti1 = 1;
                    constexpr static option input_ti2 = 2;
                    constexpr static option input_trc = 3;
                };

                // Input capture mode fields.
                struct ic1psc : mtl::hw::field<ccmr1, 2, 2> {
                    using option = mtl::hw::option<ic1psc>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ic1f : mtl::hw::field<ccmr1, 4, 4> {
                    using option = mtl::hw::option<ic1f>;
                    constexpr static option no = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                // Common fields.
                struct cc2s : mtl::hw::field<ccmr1, 8, 2> {
                    using option = mtl::hw::option<cc2s>;
                    constexpr static option output = 0;
                    constexpr static option input_ti2 = 1;
                    constexpr static option input_ti1 = 2;
                    constexpr static option input_trc = 3;
                };

                // Input capture mode fields.
                struct ic2psc : mtl::hw::field<ccmr1, 10, 2> {
                    using option = mtl::hw::option<ic2psc>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ic2f : mtl::hw::field<ccmr1, 12, 4> {
                    using option = mtl::hw::option<ic2f>;
                    constexpr static option no = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                // Output compare mode fields.
                struct oc1fe : mtl::hw::field<ccmr1, 2, 1> {
                    using option = mtl::hw::option<oc1fe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc1pe : mtl::hw::field<ccmr1, 3, 1> {
                    using option = mtl::hw::option<oc1pe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc1m : mtl::hw::field<ccmr1, 4, 3> {
                    using option = mtl::hw::option<oc1m>;
                    constexpr static option frozen = 0;
                    constexpr static option active = 1;
                    constexpr static option inactive = 2;
                    constexpr static option toggle = 3;
                    constexpr static option force_inactive = 4;
                    constexpr static option force_active = 5;
                    constexpr static option pwm1 = 6;
                    constexpr static option pwm2 = 7;
                };

                struct oc1ce : mtl::hw::field<ccmr1, 7, 1> {
                    using option = mtl::hw::option<oc1ce>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc2fe : mtl::hw::field<ccmr1, 10, 1> {
                    using option = mtl::hw::option<oc2fe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc2pe : mtl::hw::field<ccmr1, 11, 1> {
                    using option = mtl::hw::option<oc2pe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc2m : mtl::hw::field<ccmr1, 12, 3> {
                    using option = mtl::hw::option<oc2m>;
                    constexpr static option frozen = 0;
                    constexpr static option active = 1;
                    constexpr static option inactive = 2;
                    constexpr static option toggle = 3;
                    constexpr static option force_inactive = 4;
                    constexpr static option force_active = 5;
                    constexpr static option pwm1 = 6;
                    constexpr static option pwm2 = 7;
                };

                struct oc2ce : mtl::hw::field<ccmr1, 15, 1> {
                    using option = mtl::hw::option<oc2ce>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct ccmr2 : register_<0x1c, uint32_t> {
                // Common fields.
                struct cc3s : mtl::hw::field<ccmr2, 0, 2> {
                    using option = mtl::hw::option<cc3s>;
                    constexpr static option output = 0;
                    constexpr static option input_ti3 = 1;
                    constexpr static option input_ti4 = 2;
                    constexpr static option input_trc = 3;
                };

                // Input capture mode fields.
                struct ic3psc : mtl::hw::field<ccmr2, 2, 2> {
                    using option = mtl::hw::option<ic3psc>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ic3f : mtl::hw::field<ccmr2, 4, 4> {
                    using option = mtl::hw::option<ic3f>;
                    constexpr static option no = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                // Common fields.
                struct cc4s : mtl::hw::field<ccmr2, 8, 2> {
                    using option = mtl::hw::option<cc4s>;
                    constexpr static option output = 0;
                    constexpr static option input_ti4 = 1;
                    constexpr static option input_ti3 = 2;
                    constexpr static option input_trc = 3;
                };

                // Input capture mode fields.
                struct ic4psc : mtl::hw::field<ccmr2, 10, 2> {
                    using option = mtl::hw::option<ic4psc>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ic4f : mtl::hw::field<ccmr2, 12, 4> {
                    using option = mtl::hw::option<ic4f>;
                    constexpr static option no = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                // Output compare mode fields.
                struct oc3fe : mtl::hw::field<ccmr2, 2, 1> {
                    using option = mtl::hw::option<oc3fe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc3pe : mtl::hw::field<ccmr2, 3, 1> {
                    using option = mtl::hw::option<oc3pe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc3m : mtl::hw::field<ccmr2, 4, 3> {
                    using option = mtl::hw::option<oc3m>;
                    constexpr static option frozen = 0;
                    constexpr static option active = 1;
                    constexpr static option inactive = 2;
                    constexpr static option toggle = 3;
                    constexpr static option force_inactive = 4;
                    constexpr static option force_active = 5;
                    constexpr static option pwm1 = 6;
                    constexpr static option pwm2 = 7;
                };

                struct oc3ce : mtl::hw::field<ccmr2, 7, 1> {
                    using option = mtl::hw::option<oc3ce>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc4fe : mtl::hw::field<ccmr2, 10, 1> {
                    using option = mtl::hw::option<oc4fe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc4pe : mtl::hw::field<ccmr2, 11, 1> {
                    using option = mtl::hw::option<oc4pe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc4m : mtl::hw::field<ccmr2, 12, 3> {
                    using option = mtl::hw::option<oc4m>;
                    constexpr static option frozen = 0;
                    constexpr static option active = 1;
                    constexpr static option inactive = 2;
                    constexpr static option toggle = 3;
                    constexpr static option force_inactive = 4;
                    constexpr static option force_active = 5;
                    constexpr static option pwm1 = 6;
                    constexpr static option pwm2 = 7;
                };

                struct oc4ce : mtl::hw::field<ccmr2, 15, 1> {
                    using option = mtl::hw::option<oc4ce>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct ccer : register_<0x20, uint32_t> {
                struct cc1e : mtl::hw::field<ccer, 0, 1> {
                    using option = mtl::hw::option<cc1e>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc1p : mtl::hw::field<ccer, 1, 1> {
                    using option = mtl::hw::option<cc1p>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };

                struct cc2e : mtl::hw::field<ccer, 4, 1> {
                    using option = mtl::hw::option<cc2e>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc2p : mtl::hw::field<ccer, 5, 1> {
                    using option = mtl::hw::option<cc2p>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };

                struct cc3e : mtl::hw::field<ccer, 8, 1> {
                    using option = mtl::hw::option<cc3e>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc3p : mtl::hw::field<ccer, 9, 1> {
                    using option = mtl::hw::option<cc3p>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };

                struct cc4e : mtl::hw::field<ccer, 12, 1> {
                    using option = mtl::hw::option<cc4e>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc4p : mtl::hw::field<ccer, 13, 1> {
                    using option = mtl::hw::option<cc4p>;
                    constexpr static option non_inverted = 0;
                    constexpr static option inverted = 1;
                };
            };

            struct cnt : register_<0x24, uint16_t> {};
            struct psc : register_<0x28, uint16_t> {};
            struct arr : register_<0x2c, uint16_t> {};
            struct ccr1 : register_<0x34, uint16_t> {};
            struct ccr2 : register_<0x38, uint16_t> {};
            struct ccr3 : register_<0x3c, uint16_t> {};
            struct ccr4 : register_<0x40, uint16_t> {};

            struct dcr : register_<0x48, uint16_t> {
                struct dba : mtl::hw::field<dcr, 0, 5> {};
                struct dbl : mtl::hw::field<dcr, 8, 5> {};
            };

            struct dmar : register_<0x4c, uint32_t> {};
        };

        template <uint32_t v_base_address> struct timer_9_12 {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct cr1 : register_<0x00, uint32_t> {
                struct cen : mtl::hw::field<cr1, 0, 1> {
                    using option = mtl::hw::option<cen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct udis : mtl::hw::field<cr1, 1, 1> {
                    using option = mtl::hw::option<udis>;
                    constexpr static option uev_enabled = 0;
                    constexpr static option uev_disabled = 1;
                };

                struct urs : mtl::hw::field<cr1, 2, 1> {
                    using option = mtl::hw::option<urs>;
                    constexpr static option any = 0;
                    constexpr static option counter_uo = 1;
                };

                struct opm : mtl::hw::field<cr1, 3, 1> {
                    using option = mtl::hw::option<opm>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct arpe : mtl::hw::field<cr1, 7, 1> {
                    using option = mtl::hw::option<arpe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ckd : mtl::hw::field<cr1, 8, 2> {
                    using option = mtl::hw::option<ckd>;
                    constexpr static option nomul = 0;
                    constexpr static option mul2 = 1;
                    constexpr static option mul4 = 2;
                };
            };

            struct smcr : register_<0x08, uint32_t> {
                struct sms : mtl::hw::field<smcr, 0, 3> {
                    using option = mtl::hw::option<sms>;
                    constexpr static option disabled = 0;
                    constexpr static option reset = 4;
                    constexpr static option gated = 5;
                    constexpr static option trigger = 6;
                    constexpr static option external_clock = 7;
                };

                struct ts : mtl::hw::field<smcr, 4, 3> {
                    using option = mtl::hw::option<ts>;
                    constexpr static option itr0 = 0;
                    constexpr static option itr1 = 1;
                    constexpr static option itr2 = 2;
                    constexpr static option itr3 = 3;
                    constexpr static option ti1f_ed = 4;
                    constexpr static option ti1fp1 = 5;
                    constexpr static option ti1fp2 = 6;
                };
            };

            struct dier : register_<0x0c, uint32_t> {
                struct uie : mtl::hw::field<dier, 0, 1> {
                    using option = mtl::hw::option<uie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc1ie : mtl::hw::field<dier, 1, 1> {
                    using option = mtl::hw::option<cc1ie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc2ie : mtl::hw::field<dier, 2, 1> {
                    using option = mtl::hw::option<cc2ie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct tie : mtl::hw::field<dier, 6, 1> {
                    using option = mtl::hw::option<tie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct sr : register_<0x10, uint32_t> {
                struct uif : mtl::hw::field<sr, 0, 1> {
                    using option = mtl::hw::option<uif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc1if : mtl::hw::field<sr, 1, 1> {
                    using option = mtl::hw::option<cc1if>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc2if : mtl::hw::field<sr, 2, 1> {
                    using option = mtl::hw::option<cc2if>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct tif : mtl::hw::field<sr, 6, 1> {
                    using option = mtl::hw::option<tif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
                struct cc1of : mtl::hw::field<sr, 9, 1> {
                    using option = mtl::hw::option<cc1of>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc2of : mtl::hw::field<sr, 10, 1> {
                    using option = mtl::hw::option<cc2of>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };

            struct egr : register_<0x14, uint32_t> {
                struct ug : mtl::hw::field<egr, 0, 1> {
                    using option = mtl::hw::option<ug>;
                    constexpr static option set = 1;
                };

                struct cc1g : mtl::hw::field<egr, 1, 1> {
                    using option = mtl::hw::option<cc1g>;
                    constexpr static option set = 1;
                };

                struct cc2g : mtl::hw::field<egr, 2, 1> {
                    using option = mtl::hw::option<cc2g>;
                    constexpr static option set = 1;
                };

                struct tg : mtl::hw::field<egr, 6, 1> {
                    using option = mtl::hw::option<tg>;
                    constexpr static option set = 1;
                };
            };

            struct ccmr1 : register_<0x18, uint32_t> {
                // Common fields.
                struct cc1s : mtl::hw::field<ccmr1, 0, 2> {
                    using option = mtl::hw::option<cc1s>;
                    constexpr static option output = 0;
                    constexpr static option input_ti1 = 1;
                    constexpr static option input_ti2 = 2;
                    constexpr static option input_trc = 3;
                };

                // Input capture mode fields.
                struct ic1psc : mtl::hw::field<ccmr1, 2, 2> {
                    using option = mtl::hw::option<ic1psc>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ic1f : mtl::hw::field<ccmr1, 4, 4> {
                    using option = mtl::hw::option<ic1f>;
                    constexpr static option no = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                // Common fields.
                struct cc2s : mtl::hw::field<ccmr1, 8, 2> {
                    using option = mtl::hw::option<cc2s>;
                    constexpr static option output = 0;
                    constexpr static option input_ti2 = 1;
                    constexpr static option input_ti1 = 2;
                    constexpr static option input_trc = 3;
                };

                // Input capture mode fields.
                struct ic2psc : mtl::hw::field<ccmr1, 10, 2> {
                    using option = mtl::hw::option<ic2psc>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ic2f : mtl::hw::field<ccmr1, 12, 4> {
                    using option = mtl::hw::option<ic2f>;
                    constexpr static option no = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                // Output compare mode fields.
                struct oc1fe : mtl::hw::field<ccmr1, 2, 1> {
                    using option = mtl::hw::option<oc1fe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc1pe : mtl::hw::field<ccmr1, 3, 1> {
                    using option = mtl::hw::option<oc1pe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc1m : mtl::hw::field<ccmr1, 4, 3> {
                    using option = mtl::hw::option<oc1m>;
                    constexpr static option frozen = 0;
                    constexpr static option active = 1;
                    constexpr static option inactive = 2;
                    constexpr static option toggle = 3;
                    constexpr static option force_inactive = 4;
                    constexpr static option force_active = 5;
                    constexpr static option pwm1 = 6;
                    constexpr static option pwm2 = 7;
                };

                struct oc1ce : mtl::hw::field<ccmr1, 7, 1> {
                    using option = mtl::hw::option<oc1ce>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc2fe : mtl::hw::field<ccmr1, 10, 1> {
                    using option = mtl::hw::option<oc2fe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc2pe : mtl::hw::field<ccmr1, 11, 1> {
                    using option = mtl::hw::option<oc2pe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc2m : mtl::hw::field<ccmr1, 12, 3> {
                    using option = mtl::hw::option<oc2m>;
                    constexpr static option frozen = 0;
                    constexpr static option active = 1;
                    constexpr static option inactive = 2;
                    constexpr static option toggle = 3;
                    constexpr static option force_inactive = 4;
                    constexpr static option force_active = 5;
                    constexpr static option pwm1 = 6;
                    constexpr static option pwm2 = 7;
                };

                struct oc2ce : mtl::hw::field<ccmr1, 15, 1> {
                    using option = mtl::hw::option<oc2ce>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct ccer : register_<0x20, uint32_t> {
                struct cc1e : mtl::hw::field<ccer, 0, 1> {
                    using option = mtl::hw::option<cc1e>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc1p : mtl::hw::field<ccer, 1, 1> {
                    using option = mtl::hw::option<cc1p>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };

                struct cc1np : mtl::hw::field<ccer, 3, 1> {
                    using option = mtl::hw::option<cc1np>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };

                struct cc2e : mtl::hw::field<ccer, 4, 1> {
                    using option = mtl::hw::option<cc2e>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc2p : mtl::hw::field<ccer, 5, 1> {
                    using option = mtl::hw::option<cc2p>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };

                struct cc2np : mtl::hw::field<ccer, 7, 1> {
                    using option = mtl::hw::option<cc2np>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };
            };

            struct cnt : register_<0x24, uint16_t> {};
            struct psc : register_<0x28, uint16_t> {};
            struct arr : register_<0x2c, uint16_t> {};
            struct ccr1 : register_<0x34, uint16_t> {};
            struct ccr2 : register_<0x38, uint16_t> {};
        };

        template <uint32_t v_base_address> struct timer_10_14 {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct cr1 : register_<0x00, uint32_t> {
                struct cen : mtl::hw::field<cr1, 0, 1> {
                    using option = mtl::hw::option<cen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct udis : mtl::hw::field<cr1, 1, 1> {
                    using option = mtl::hw::option<udis>;
                    constexpr static option uev_enabled = 0;
                    constexpr static option uev_disabled = 1;
                };

                struct urs : mtl::hw::field<cr1, 2, 1> {
                    using option = mtl::hw::option<urs>;
                    constexpr static option any = 0;
                    constexpr static option counter_uo = 1;
                };

                struct opm : mtl::hw::field<cr1, 3, 1> {
                    using option = mtl::hw::option<opm>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct arpe : mtl::hw::field<cr1, 7, 1> {
                    using option = mtl::hw::option<arpe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ckd : mtl::hw::field<cr1, 8, 2> {
                    using option = mtl::hw::option<ckd>;
                    constexpr static option nomul = 0;
                    constexpr static option mul2 = 1;
                    constexpr static option mul4 = 2;
                };
            };

            struct dier : register_<0x0c, uint32_t> {
                struct uie : mtl::hw::field<dier, 0, 1> {
                    using option = mtl::hw::option<uie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc1ie : mtl::hw::field<dier, 1, 1> {
                    using option = mtl::hw::option<cc1ie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct sr : register_<0x10, uint32_t> {
                struct uif : mtl::hw::field<sr, 0, 1> {
                    using option = mtl::hw::option<uif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc1if : mtl::hw::field<sr, 1, 1> {
                    using option = mtl::hw::option<cc1if>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cc1of : mtl::hw::field<sr, 9, 1> {
                    using option = mtl::hw::option<cc1of>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };

            struct egr : register_<0x14, uint32_t> {
                struct ug : mtl::hw::field<egr, 0, 1> {
                    using option = mtl::hw::option<ug>;
                    constexpr static option set = 1;
                };

                struct cc1g : mtl::hw::field<egr, 1, 1> {
                    using option = mtl::hw::option<cc1g>;
                    constexpr static option set = 1;
                };
            };

            struct ccmr1 : register_<0x18, uint32_t> {
                // Common fields.
                struct cc1s : mtl::hw::field<ccmr1, 0, 2> {
                    using option = mtl::hw::option<cc1s>;
                    constexpr static option output = 0;
                    constexpr static option input_ti1 = 1;
                    constexpr static option input_ti2 = 2;
                    constexpr static option input_trc = 3;
                };

                // Input capture mode fields.
                struct ic1psc : mtl::hw::field<ccmr1, 2, 2> {
                    using option = mtl::hw::option<ic1psc>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                };

                struct ic1f : mtl::hw::field<ccmr1, 4, 4> {
                    using option = mtl::hw::option<ic1f>;
                    constexpr static option no = 0;
                    constexpr static option nodiv_n2 = 1;
                    constexpr static option nodiv_n4 = 2;
                    constexpr static option nodiv_n8 = 3;
                    constexpr static option div2_n6 = 4;
                    constexpr static option div2_n8 = 5;
                    constexpr static option div4_n6 = 6;
                    constexpr static option div4_n8 = 7;
                    constexpr static option div8_n6 = 8;
                    constexpr static option div8_n8 = 9;
                    constexpr static option div16_n5 = 10;
                    constexpr static option div16_n6 = 11;
                    constexpr static option div16_n8 = 12;
                    constexpr static option div32_n5 = 13;
                    constexpr static option div32_n6 = 14;
                    constexpr static option div32_n8 = 15;
                };

                // Output compare mode fields.
                struct oc1fe : mtl::hw::field<ccmr1, 2, 1> {
                    using option = mtl::hw::option<oc1fe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc1pe : mtl::hw::field<ccmr1, 3, 1> {
                    using option = mtl::hw::option<oc1pe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct oc1m : mtl::hw::field<ccmr1, 4, 3> {
                    using option = mtl::hw::option<oc1m>;
                    constexpr static option frozen = 0;
                    constexpr static option active = 1;
                    constexpr static option inactive = 2;
                    constexpr static option toggle = 3;
                    constexpr static option force_inactive = 4;
                    constexpr static option force_active = 5;
                    constexpr static option pwm1 = 6;
                    constexpr static option pwm2 = 7;
                };

                struct oc1ce : mtl::hw::field<ccmr1, 7, 1> {
                    using option = mtl::hw::option<oc1ce>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct ccer : register_<0x20, uint32_t> {
                struct cc1e : mtl::hw::field<ccer, 0, 1> {
                    using option = mtl::hw::option<cc1e>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cc1p : mtl::hw::field<ccer, 1, 1> {
                    using option = mtl::hw::option<cc1p>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };

                struct cc1np : mtl::hw::field<ccer, 3, 1> {
                    using option = mtl::hw::option<cc1np>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                };
            };

            struct cnt : register_<0x24, uint16_t> {};
            struct psc : register_<0x28, uint16_t> {};
            struct arr : register_<0x2c, uint16_t> {};
            struct ccr1 : register_<0x34, uint16_t> {};
        };
        template <uint32_t v_base_address> struct timer_6_7 {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct cr1 : register_<0x00, uint32_t> {
                struct cen : mtl::hw::field<cr1, 0, 1> {
                    using option = mtl::hw::option<cen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct udis : mtl::hw::field<cr1, 1, 1> {
                    using option = mtl::hw::option<udis>;
                    constexpr static option uev_enabled = 0;
                    constexpr static option uev_disabled = 1;
                };

                struct urs : mtl::hw::field<cr1, 2, 1> {
                    using option = mtl::hw::option<urs>;
                    constexpr static option any = 0;
                    constexpr static option counter_uo = 1;
                };

                struct opm : mtl::hw::field<cr1, 3, 1> {
                    using option = mtl::hw::option<opm>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct arpe : mtl::hw::field<cr1, 7, 1> {
                    using option = mtl::hw::option<arpe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct cr2 : register_<0x04, uint32_t> {
                struct mms : mtl::hw::field<cr2, 4, 3> {
                    using option = mtl::hw::option<mms>;
                    constexpr static option reset = 0;
                    constexpr static option enable = 1;
                    constexpr static option update = 2;
                };
            };

            struct dier : register_<0x0c, uint32_t> {
                struct uie : mtl::hw::field<dier, 0, 1> {
                    using option = mtl::hw::option<uie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ude : mtl::hw::field<dier, 8, 1> {
                    using option = mtl::hw::option<ude>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct sr : register_<0x10, uint32_t> {
                struct uif : mtl::hw::field<sr, 0, 1> {
                    using option = mtl::hw::option<uif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };

            struct egr : register_<0x14, uint32_t> {
                struct ug : mtl::hw::field<egr, 0, 1> {
                    using option = mtl::hw::option<ug>;
                    constexpr static option set = 1;
                };
            };

            struct cnt : register_<0x24, uint16_t> {};
            struct psc : register_<0x28, uint16_t> {};
            struct arr : register_<0x2c, uint16_t> {};
        };
    } // namespace descriptor

    using timer1 = descriptor::timer_1_8<0x40012c00>;
    using timer2 = descriptor::timer_2_5<0x40000000>;
    using timer3 = descriptor::timer_2_5<0x40000400>;
    using timer4 = descriptor::timer_2_5<0x40000800>;
    using timer5 = descriptor::timer_2_5<0x40000c00>;
    using timer6 = descriptor::timer_6_7<0x40001000>;
    using timer7 = descriptor::timer_6_7<0x40001400>;
    using timer8 = descriptor::timer_1_8<0x40013400>;
    using timer9 = descriptor::timer_9_12<0x40014c00>;
    using timer10 = descriptor::timer_10_14<0x40015000>;
    using timer11 = descriptor::timer_10_14<0x40015400>;
    using timer12 = descriptor::timer_9_12<0x40001800>;
    using timer13 = descriptor::timer_10_14<0x40001c00>;
    using timer14 = descriptor::timer_10_14<0x40002000>;

    template <class> struct timer;
    template <> struct timer<mtl::hw::ids::timer1> : timer1 {};
    template <> struct timer<mtl::hw::ids::timer2> : timer2 {};
    template <> struct timer<mtl::hw::ids::timer3> : timer3 {};
    template <> struct timer<mtl::hw::ids::timer4> : timer4 {};
    template <> struct timer<mtl::hw::ids::timer5> : timer5 {};
    template <> struct timer<mtl::hw::ids::timer6> : timer6 {};
    template <> struct timer<mtl::hw::ids::timer7> : timer7 {};
    template <> struct timer<mtl::hw::ids::timer8> : timer8 {};
    template <> struct timer<mtl::hw::ids::timer9> : timer9 {};
    template <> struct timer<mtl::hw::ids::timer10> : timer10 {};
    template <> struct timer<mtl::hw::ids::timer11> : timer11 {};
    template <> struct timer<mtl::hw::ids::timer12> : timer12 {};
    template <> struct timer<mtl::hw::ids::timer13> : timer13 {};
    template <> struct timer<mtl::hw::ids::timer14> : timer14 {};
} // namespace mtl::hw
