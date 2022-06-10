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
                }

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

                struct pll2on : mtl::hw::field<cr, 26, 1> {
                    using option = mtl::hw::option<pll2on>;
                    constexpr static option off = 0;
                    constexpr static option on = 1;
                };

                struct pll2rdy : mtl::hw::field<cr, 27, 1> {
                    using option = mtl::hw::option<pll2rdy>;
                    constexpr static option not_ready = 0;
                    constexpr static option ready = 1;
                };

                struct pll3on : mtl::hw::field<cr, 28, 1> {
                    using option = mtl::hw::option<pll3on>;
                    constexpr static option off = 0;
                    constexpr static option on = 1;
                };

                struct pll3rdy : mtl::hw::field<cr, 29, 1> {
                    using option = mtl::hw::option<pll3rdy>;
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
                };

                struct sws : mtl::hw::field<cfgr, 2, 2> {
                    using option = mtl::hw::option<sws>;
                    constexpr static option hsi = 0;
                    constexpr static option hse = 1;
                    constexpr static option pll = 2;
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

                struct ppre1 : mtl::hw::field<cfgr, 8, 3> {
                    using option = mtl::hw::option<ppre1>;
                    constexpr static option div2 = 4;
                    constexpr static option div4 = 5;
                    constexpr static option div8 = 6;
                    constexpr static option div16 = 7;
                };

                struct ppre2 : mtl::hw::field<cfgr, 11, 3> {
                    using option = mtl::hw::option<ppre2>;
                    constexpr static option div2 = 4;
                    constexpr static option div4 = 5;
                    constexpr static option div8 = 6;
                    constexpr static option div16 = 7;
                };

                struct adcpre : mtl::hw::field<cfgr, 14, 2> {
                    using option = mtl::hw::option<adcpre>;
                    constexpr static option div2 = 0;
                    constexpr static option div4 = 1;
                    constexpr static option div6 = 2;
                    constexpr static option div8 = 3;
                };

                struct pllsrc : mtl::hw::field<cfgr, 16, 1> {
                    using option = mtl::hw::option<pllsrc>;
                    constexpr static option hsi_div2 = 0;
                    constexpr static option prediv1 = 1;
                };

                struct pllxtpre : mtl::hw::field<cfgr, 17, 1> {
                    using option = mtl::hw::option<pllxtpre>;
                    constexpr static option nodiv = 0;
                    constexpr static option div2 = 1;
                };

                struct pllmul : mtl::hw::field<cfgr, 18, 4> {
                    using option = mtl::hw::option<pllmul>;
                    constexpr static option mul4 = 2;
                    constexpr static option mul5 = 3;
                    constexpr static option mul6 = 4;
                    constexpr static option mul7 = 5;
                    constexpr static option mul8 = 6;
                    constexpr static option mul9 = 7;
                    constexpr static option mul6_5 = 13;
                };

                struct otgfspre : mtl::hw::field<cfgr, 22, 1> {
                    using option = mtl::hw::option<otgfspre>;
                    constexpr static option div3 = 0;
                    constexpr static option div2 = 1;
                };

                struct mco : mtl::hw::field<cfgr, 23, 4> {
                    using option = mtl::hw::option<mco>;
                    constexpr static option sysclk = 4;
                    constexpr static option hsi = 5;
                    constexpr static option hse = 6;
                    constexpr static option pll_div2 = 7;
                    constexpr static option pll2 = 8;
                    constexpr static option pll3_div2 = 9;
                    constexpr static option pll3_xt1 = 10;
                    constexpr static option pll3 = 11;
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
                        constexpr static option off = 0;
                        constexpr static option on = 1;
                    };

                    struct lsirdy : mtl::hw::field<csr, 1, 1> {
                        using option = mtl::hw::option<lsirdy>;
                        constexpr static option not_ready = 0;
                        constexpr static option ready = 1;
                    };

                    struct rmvf : mtl::hw::field<csr, 24, 1> {
                        using option = mtl::hw::option<rmvf>;
                        constexpr static option clear = 1;
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
                    struct prediv1 : mtl::hw::field<cfgr2, 0, 4> {
                        using option = mtl::hw::option<prediv1>;
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
                        constexpr static option div12 = 11;
                        constexpr static option div13 = 12;
                        constexpr static option div14 = 13;
                        constexpr static option div15 = 14;
                        constexpr static option div16 = 15;
                    };

                    struct prediv2 : mtl::hw::field<cfgr2, 4, 4> {
                        using option = mtl::hw::option<prediv2>;
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
                        constexpr static option div12 = 11;
                        constexpr static option div13 = 12;
                        constexpr static option div14 = 13;
                        constexpr static option div15 = 14;
                        constexpr static option div16 = 15;
                    };

                    struct pll2mul : mtl::hw::field<cfgr2, 8, 4> {
                        using option = mtl::hw::option<pll2mul>;
                        constexpr static option mul8 = 6;
                        constexpr static option mul9 = 7;
                        constexpr static option mul10 = 8;
                        constexpr static option mul11 = 9;
                        constexpr static option mul12 = 10;
                        constexpr static option mul13 = 11;
                        constexpr static option mul14 = 12;
                        constexpr static option mul16 = 14;
                        constexpr static option mul20 = 15;
                    };

                    struct pll3mul : mtl::hw::field<cfgr2, 12, 4> {
                        using option = mtl::hw::option<pll3mul>;
                        constexpr static option mul8 = 6;
                        constexpr static option mul9 = 7;
                        constexpr static option mul10 = 8;
                        constexpr static option mul11 = 9;
                        constexpr static option mul12 = 10;
                        constexpr static option mul13 = 11;
                        constexpr static option mul14 = 12;
                        constexpr static option mul16 = 14;
                        constexpr static option mul20 = 15;
                    };

                    struct prediv1src : mtl::hw::field<cfgr2, 16, 1> {
                        using option = mtl::hw::option<prediv1src>;
                        constexpr static option hse = 0;
                        constexpr static option pll2 = 1;
                    };

                    struct i2s2src : mtl::hw::field<cfgr2, 17, 1> {
                        using option = mtl::hw::option<i2s2src>;
                        constexpr static option sysclk = 0;
                        constexpr static option pll3 = 1;
                    };

                    struct i2s3src : mtl::hw::field<cfgr2, 18, 1> {
                        using option = mtl::hw::option<i2s3src>;
                        constexpr static option sysclk = 0;
                        constexpr static option pll3 = 1;
                    };
                };
            };
        };
    } // namespace descriptor

    using flash = descriptor::rcc<0x40021000>;
} // namespace devices
