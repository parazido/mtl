#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace devices {
    namespace descriptor {
        template <uint32_t v_base_address> struct adc {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct isr : register_<0x00, uint32_t> {
                struct adrdy : mtl::hw::field<isr, 0, 1> {
                    using option = mtl::hw::option<adrdy>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
                
                struct eosmp : mtl::hw::field<isr, 1, 1> {
                    using option = mtl::hw::option<eosmp>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct eoc : mtl::hw::field<isr, 2, 1> {
                    using option = mtl::hw::option<eoc>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct eos : mtl::hw::field<isr, 3, 1> {
                    using option = mtl::hw::option<eos>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct ovr : mtl::hw::field<isr, 4, 1> {
                    using option = mtl::hw::option<ovr>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct awd : mtl::hw::field<isr, 7, 1> {
                    using option = mtl::hw::option<awd>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };

            struct ier : register_<0x04, uint32_t> {
                struct adrdyie : mtl::hw::field<ier, 0, 1> {
                    using option = mtl::hw::option<adrdyie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
                
                struct eosmpie : mtl::hw::field<ier, 1, 1> {
                    using option = mtl::hw::option<eosmpie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct eocie : mtl::hw::field<ier, 2, 1> {
                    using option = mtl::hw::option<eocie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct eosie : mtl::hw::field<ier, 3, 1> {
                    using option = mtl::hw::option<eosie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ovrie : mtl::hw::field<ier, 4, 1> {
                    using option = mtl::hw::option<ovrie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct awdie : mtl::hw::field<ier, 7, 1> {
                    using option = mtl::hw::option<awdie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct cr : register_<0x08, uint32_t> {
                struct aden : mtl::hw::field<cr, 0, 1> {
                    using option = mtl::hw::option<aden>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct addis : mtl::hw::field<cr, 1, 1> {
                    using option = mtl::hw::option<addis>;
                    constexpr static option disable = 1;
                    constexpr static option in_progress = 1;
                };

                struct adstart : mtl::hw::field<cr, 2, 1> {
                    using option = mtl::hw::option<adstart>;
                    constexpr static option start = 1;
                };

                struct adstp : mtl::hw::field<cr, 4, 1> {
                    using option = mtl::hw::option<adstp>;
                    constexpr static option stop = 1;
                    constexpr static option in_progress = 1;
                };

                struct adcal : mtl::hw::field<cr, 31, 1> {
                    using option = mtl::hw::option<adcal>;
                    constexpr static option calibrate = 1;
                    constexpr static option in_progress = 1;
                };
            };


            struct cfgr1 : register_<0x0c, uint32_t> {
                struct dmaen : mtl::hw::field<cfgr1, 0, 1> {
                    using option = mtl::hw::option<dmaen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct dmacfg : mtl::hw::field<cfgr1, 1, 1> {
                    using option = mtl::hw::option<dmacfg>;
                    constexpr static option one_shot = 0;
                    constexpr static option circular = 1;
                };

                struct scandir : mtl::hw::field<cfgr1, 2, 1> {
                    using option = mtl::hw::option<scandir>;
                    constexpr static option upward = 0;
                    constexpr static option backward = 1;
                };

                struct res : mtl::hw::field<cfgr1, 3, 2> {
                    using option = mtl::hw::option<res>;
                    constexpr static option bits12 = 0;
                    constexpr static option bits10 = 1;
                    constexpr static option bits8 = 2;
                    constexpr static option bits6 = 3;
                };

                struct align : mtl::hw::field<cfgr1, 5, 1> {
                    using option = mtl::hw::option<align>;
                    constexpr static option right = 0;
                    constexpr static option left = 1;
                };

                struct extsel : mtl::hw::field<cfgr1, 6, 3> {
                    using option = mtl::hw::option<extsel>;
                    constexpr static option trg0 = 0;
                    constexpr static option trg1 = 1;
                    constexpr static option trg2 = 2;
                    constexpr static option trg3 = 3;
                    constexpr static option trg4 = 4;
                    constexpr static option trg5 = 5;
                    constexpr static option trg6 = 6;
                    constexpr static option trg7 = 7;
                };

                struct exten : mtl::hw::field<cfgr1, 10, 2> {
                    using option = mtl::hw::option<exten>;
                    constexpr static option disabled = 0;
                    constexpr static option rising = 1;
                    constexpr static option falling = 2;
                    constexpr static option both = 3;
                };

                struct ovrmod : mtl::hw::field<cfgr1, 12, 1> {
                    using option = mtl::hw::option<ovrmod>;
                    constexpr static option old = 0;
                    constexpr static option last = 1;
                };

                struct cont : mtl::hw::field<cfgr1, 13, 1> {
                    using option = mtl::hw::option<cont>;
                    constexpr static option single = 0;
                    constexpr static option continuous = 1;
                };

                struct wait : mtl::hw::field<cfgr1, 14, 1> {
                    using option = mtl::hw::option<wait>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct autoff : mtl::hw::field<cfgr1, 15, 1> {
                    using option = mtl::hw::option<autoff>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct discen : mtl::hw::field<cfgr1, 16, 1> {
                    using option = mtl::hw::option<discen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct awdsgl : mtl::hw::field<cfgr1, 22, 1> {
                    using option = mtl::hw::option<wait>;
                    constexpr static option all = 0;
                    constexpr static option single = 1;
                };

                struct awden : mtl::hw::field<cfgr1, 23, 1> {
                    using option = mtl::hw::option<awden>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct awdch : mtl::hw::field<cfgr1, 26, 5> {};
            };

            struct cfgr2 : register_<0x10, uint32_t> {
                struct ckmode : mtl::hw::field<cfgr2, 30, 2> {
                    using option = mtl::hw::option<ckmode>;
                    constexpr static option adcclk = 0;
                    constexpr static option pclk_div2 = 1;
                    constexpr static option pclk_div4 = 1;
                };
            };

            struct smpr : register_<0x14, uint32_t> {
                struct smp : mtl::hw::field<smp, 0, 3> {
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

            struct tr : register_<0x20, uint32_t> {
                struct lt : mtl::hw::field<tr, 16, 12> {};
                struct ht : mtl::hw::field<tr, 0, 12> {};
            };

            struct chselr : register_<0x28, uint32_t> {
                template <uint8_t v_index> struct chsel : mtl::hw::field<chselr, v_index, 1> {
                    using option = mtl::hw::option<chsel>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct dr : register_<0x40, uint32_t> {};

            struct ccr : register_<0x308, uint32_t> {
                struct vrefen : mtl::hw::field<ccr, 22, 1> {
                    using option = mtl::hw::option<vrefen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct tsen : mtl::hw::field<ccr, 23, 1> {
                    using option = mtl::hw::option<tsen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct vbaten : mtl::hw::field<ccr, 24, 1> {
                    using option = mtl::hw::option<vbaten>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };
        };
    } // namespace descriptor

    using adc = descriptor::adc<0x40012400>;
} // namespace devices
