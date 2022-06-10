#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace devices {
    namespace descriptor {
        template <uint32_t v_base_address> struct rcc {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct cr : register_<0x00, uint32_t> {
                struct hsion : mtl::hw::field<cr, 0, 1> {
                    using option = mtl::hw::option<hsion>;
                    constexpr static option off = 0;
                    constexpr static option on = 1;
                }

                struct hsirdy : mtl::hw::field<cr, 1, 1> {
                    using option = mtl::hw::option<hsirdy>;
                    constexpr static option not_ready = 0;
                    constexpr static option ready = 1;
                }

                struct hsitrim : mtl::hw::field<cr, 3, 5> {
                }

                struct hsical : mtl::hw::field<cr, 8, 8> {
         struct hsi14cal : mtl::hw::field<cr2, 8, 8> {};       }

                struct hseon : mtl::hw::field<cr, 16, 1> {
                    using option = mtl::hw::option<hseon>;
                    constexpr static option off = 0;
                    constexpr static option on = 1;
                }

                struct hserdy : mtl::hw::field<cr, 17, 1> {
                    using option = mtl::hw::option<hserdy>;
                    constexpr static option not_ready = 0;
                    constexpr static option ready = 1;
                }

                struct hsebyp : mtl::hw::field<cr, 18, 1> {
                    using option = mtl::hw::option<hsebyp>;
                    constexpr static option not_bypassed = 0;
                    constexpr static option bypassed = 1;
                }

                struct csson : mtl::hw::field<cr, 19, 1> {
                    using option = mtl::hw::option<csson>;
                    constexpr static option off = 0;
                    constexpr static option on = 1;
                };

                struct pllon : mtl::hw::field<cr, 24, 1> {
                    using option = mtl::hw::option<pllon>;
                    constexpr static option off = 0;
                    constexpr static option on = 1;
                };

                struct pllrdy : mtl::hw::field<cr, 25, 1> {
                    using option = mtl::hw::option<pllrdy>;
                    constexpr static option not_ready = 0;
                    constexpr static option ready = 1;
                };
            };

            struct cfgr : register_<0x04, uint32_t> {
                struct sw : mtl::hw::field<cfgr, 0, 2> {
                    using option = mtl::hw::option<sw>;
                    constexpr static option hsi = 0;
                    constexpr static option hse = 1;
                    constexpr static option pll = 2;
                    constexpr static option hsi48 = 3;
                };

                struct sws : mtl::hw::field<cfgr, 2, 2> {
                    using option = mtl::hw::option<sws>;
                    constexpr static option hsi = 0;
                    constexpr static option hse = 1;
                    constexpr static option pll = 2;
                    constexpr static option hsi48 = 3;
                };

                struct hpre : mtl::hw::field<cfgr, 4, 4> {
                    using option = mtl::hw::option<hpre>;
                    constexpr static option div2 = 8;
                    constexpr static option div4 = 9;
                    constexpr static option div8 = 10;
                    constexpr static option div16 = 11;
                    constexpr static option div64 = 12;
                    constexpr static option div128 = 13;
                    constexpr static option div256 = 14;
                    constexpr static option div512 = 15;
                };

                struct ppre : mtl::hw::field<cfgr, 8, 3> {
                    using option = mtl::hw::option<ppre1>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 4;
                    constexpr static option div4 = 5;
                    constexpr static option div8 = 6;
                    constexpr static option div16 = 7;
                };

                struct pllsrc : mtl::hw::field<cfgr, 15, 2> {
                    using option = mtl::hw::option<pllsrc>;
                    constexpr static option hsi_div2 = 0;
                    constexpr static option hsi_prediv = 1;
                    constexpr static option hse_prediv = 2;
                    constexpr static option hsi48_prediv = 3;
                };

                struct pllxtpre : mtl::hw::field<cfgr, 17, 1> {
                    using option = mtl::hw::option<pllxtpre>;
                    constexpr static option nodiv = 0;
                    constexpr static option div2 = 1;
                };

                struct pllmul : mtl::hw::field<cfgr, 18, 4> {
                    using option = mtl::hw::option<pllmul>;
                    constexpr static option mul2 = 0;
                    constexpr static option mul3 = 1;
                    constexpr static option mul4 = 2;
                    constexpr static option mul5 = 3;
                    constexpr static option mul6 = 4;
                    constexpr static option mul7 = 5;
                    constexpr static option mul8 = 6;
                    constexpr static option mul9 = 7;
                    constexpr static option mul10 = 8;
                    constexpr static option mul11 = 9;
                    constexpr static option mul12 = 10;
                    constexpr static option mul13 = 11;
                    constexpr static option mul14 = 12;
                    constexpr static option mul15 = 13;
                    constexpr static option mul16 = 14;
                };

                struct mco : mtl::hw::field<cfgr, 24, 4> {
                    using option = mtl::hw::option<mco>;
                    constexpr static option no = 0;
                    constexpr static option hsi14 = 1;
                    constexpr static option lsi = 2;
                    constexpr static option lse = 3;
                    constexpr static option sysclk = 4;
                    constexpr static option hsi = 5;
                    constexpr static option hse = 6;
                    constexpr static option pll_div = 7;
                    constexpr static option hsi48 = 8;
                };

                struct mcopre : mtl::hw::field<cfgr, 28, 3> {
                    using option = mtl::hw::option<mcopre>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 2;
                    constexpr static option div8 = 3;
                    constexpr static option div16 = 4;
                    constexpr static option div32 = 5;
                    constexpr static option div64 = 6;
                    constexpr static option div128 = 7;
                };

                struct pllnodiv : mtl::hw::field<cfgr, 31, 1> {
                    using option = mtl::hw::option<pllnodiv>;
                    constexpr static option div2 = 0;
                    constexpr static option no = 1;
                };
            };

            struct cir : register_<0x08, uint32_t> {};

            struct apb2rstr : register_<0x0c, uint32_t> {};

            struct apb1rstr : register_<0x10, uint32_t> {};

            struct ahbenr : register_<0x14, uint32_t> {};

            struct apb2enr : register_<0x18, uint32_t> {};

            struct apb1enr : register_<0x1c, uint32_t> {};

            struct bdcr : register_<0x20, uint32_t> {};

            struct csr : register_<0x24, uint32_t> {
                struct lsion : mtl::hw::field<csr, 0, 1> {
                    using option = mtl::hw::option<lsion>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct lsirdy : mtl::hw::field<csr, 1, 1> {
                    using option = mtl::hw::option<lsirdy>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct v18pwrrstf : mtl::hw::field<csr, 23, 1> {
                    using option = mtl::hw::option<rmvf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct rmvf : mtl::hw::field<csr, 24, 1> {
                    using option = mtl::hw::option<rmvf>;
                    constexpr static option clear = 1;
                };

                struct oblrstf : mtl::hw::field<csr, 25, 1> {
                    using option = mtl::hw::option<rmvf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct pinrstf : mtl::hw::field<csr, 26, 1> {
                    using option = mtl::hw::option<pinrstf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct porrstf : mtl::hw::field<csr, 27, 1> {
                    using option = mtl::hw::option<porrstf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct sftrstf : mtl::hw::field<csr, 28, 1> {
                    using option = mtl::hw::option<sftrstf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct iwdgrstf : mtl::hw::field<csr, 29, 1> {
                    using option = mtl::hw::option<iwdgrstf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct wwdgrstf : mtl::hw::field<csr, 30, 1> {
                    using option = mtl::hw::option<wwdgrstf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct lpwrrstf : mtl::hw::field<csr, 31, 1> {
                    using option = mtl::hw::option<lpwrrstf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };

            struct ahbrstr : register_<0x28, uint32_t> {};

            struct cfgr2 : register_<0x2c, uint32_t> {
                struct prediv : mtl::hw::field<cfgr2, 0, 4> {
                    using option = mtl::hw::option<prediv>;
                    constexpr static option nodiv = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div3 = 2;
                    constexpr static option div4 = 3;
                    constexpr static option div5 = 4;
                    constexpr static option div6 = 5;
                    constexpr static option div7 = 6;
                    constexpr static option div8 = 7;
                    constexpr static option div9 = 8;
                    constexpr static option div10 = 9;
                    constexpr static option div11 = 10;
                    constexpr static option lse = 2;
                    constexpr static option hsi = 3;
                    constexpr static option div12 = 11;
                    constexpr static option div13 = 12;
                    constexpr static option div14 = 13;
                    constexpr static option div15 = 14;
                    constexpr static option div16 = 15;
                };
            };

            struct cfgr3 : register_<0x30, uint32_t> {
                struct usart1sw : mtl::hw::field<cfgr3, 0, 2> {
                    using option = mtl::hw::option<usart1sw>;
                    constexpr static option pclk = 0;
                    constexpr static option syslk = 1;
                    constexpr static option lse = 2;
                    constexpr static option hsi = 3;
                };

                struct i2c1sw : mtl::hw::field<cfgr3, 4, 1> {
                    using option = mtl::hw::option<i2c1sw>;
                    constexpr static option hsi = 0;
                    constexpr static option syslk = 1;
                };

                struct cecsw : mtl::hw::field<cfgr3, 6, 1> {
                    using option = mtl::hw::option<cecsw>;
                    constexpr static option hsi_div244 = 0;
                    constexpr static option lse = 1;
                };

                struct usbsw : mtl::hw::field<cfgr3, 7, 1> {
                    using option = mtl::hw::option<usbsw>;
                    constexpr static option hsi48 = 0;
                    constexpr static option pll = 1;
                };

                struct usbsw : mtl::hw::field<cfgr3, 7, 1> {
                    using option = mtl::hw::option<usbsw>;
                    constexpr static option hsi48 = 0;
                    constexpr static option pll = 1;
                };

                struct usart2sw : mtl::hw::field<cfgr3, 16, 2> {
                    using option = mtl::hw::option<usart2sw>;
                    constexpr static option pclk = 0;
                    constexpr static option syslk = 1;
                    constexpr static option lse = 2;
                    constexpr static option hsi = 3;
                };

                struct usart3sw : mtl::hw::field<cfgr3, 18, 2> {
                    using option = mtl::hw::option<usart3sw>;
                    constexpr static option pclk = 0;
                    constexpr static option syslk = 1;
                    constexpr static option lse = 2;
                    constexpr static option hsi = 3;
                };
            };

            struct cr2 : register_<0x34, uint32_t> {
                struct hsi14on : mtl::hw::field<cr2, 0, 1> {
                    using option = mtl::hw::option<hsi14on>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct hsi14rdy : mtl::hw::field<cr2, 1, 1> {
                    using option = mtl::hw::option<hsi14rdy>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct hsi14dis : mtl::hw::field<cr2, 2, 1> {
                    using option = mtl::hw::option<hsi14rdy>;
                    constexpr static option allow = 0;
                    constexpr static option prevent = 1;
                };

                struct hsi14trim : mtl::hw::field<cr2, 3, 4> {};

                struct hsi14cal : mtl::hw::field<cr2, 8, 8> {};

                struct hsi48on : mtl::hw::field<cr2, 16, 1> {
                    using option = mtl::hw::option<hsi48on>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct hsi48rdy : mtl::hw::field<cr2, 17, 1> {
                    using option = mtl::hw::option<hsi48rdy>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct hsi48cal : mtl::hw::field<cr2, 24, 8> {};
            };
        };
    } // namespace descriptor

    using rcc = descriptor::rcc<0x40021000>;
} // namespace devices
