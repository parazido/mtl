

#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace mtl::hw {
    namespace descriptor {
        template <uint32_t v_base_address> struct usart {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct cr1 : register_<0x00, uint32_t> {
                struct ue : mtl::hw::field<cr1, 0, 1> {
                    using option = mtl::hw::option<ue>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct uesm : mtl::hw::field<cr1, 1, 1> {
                    using option = mtl::hw::option<ue>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct re : mtl::hw::field<cr1, 2, 1> {
                    using option = mtl::hw::option<re>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct te : mtl::hw::field<cr1, 3, 1> {
                    using option = mtl::hw::option<te>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct idleie : mtl::hw::field<cr1, 4, 1> {
                    using option = mtl::hw::option<idleie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct rxneie : mtl::hw::field<cr1, 5, 1> {
                    using option = mtl::hw::option<rxneie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct tcie : mtl::hw::field<cr1, 6, 1> {
                    using option = mtl::hw::option<tcie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct txeie : mtl::hw::field<cr1, 7, 1> {
                    using option = mtl::hw::option<txeie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct peie : mtl::hw::field<cr1, 8, 1> {
                    using option = mtl::hw::option<peie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ps : mtl::hw::field<cr1, 9, 1> {
                    using option = mtl::hw::option<ps>;
                    constexpr static option even = 0;
                    constexpr static option odd = 1;
                };

                struct pce : mtl::hw::field<cr1, 10, 1> {
                    using option = mtl::hw::option<pce>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct wake : mtl::hw::field<cr1, 11, 1> {
                    using option = mtl::hw::option<wake>;
                    constexpr static option idle = 0;
                    constexpr static option address = 1;
                };

                struct m0 : mtl::hw::field<cr1, 12, 1> {};

                struct over8 : mtl::hw::field<cr1, 15, 1> {
                    using option = mtl::hw::option<over8>;
                    constexpr static option by16 = 0;
                    constexpr static option by8 = 1;
                };

                struct dedt : mtl::hw::field<cr1, 16, 5> {};

                struct deat : mtl::hw::field<cr1, 21, 5> {};

                struct rtoie : mtl::hw::field<cr1, 26, 1> {
                    using option = mtl::hw::option<rtoie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct eobie : mtl::hw::field<cr1, 27, 1> {
                    using option = mtl::hw::option<eobie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct m1 : mtl::hw::field<cr1, 28, 1> {};
            };

            struct cr2 : register_<0x04, uint32_t> {
                struct addm7 : mtl::hw::field<cr2, 4, 1> {
                    using option = mtl::hw::option<addm7>;
                    constexpr static option bit4 = 0;
                    constexpr static option bit7 = 1;
                };

                struct lbdl : mtl::hw::field<cr2, 5, 1> {
                    using option = mtl::hw::option<lbdl>;
                    constexpr static option bit10 = 0;
                    constexpr static option bit11 = 1;
                };

                struct lbdie : mtl::hw::field<cr2, 6, 1> {
                    using option = mtl::hw::option<lbdie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct lbcl : mtl::hw::field<cr2, 8, 1> {
                    using option = mtl::hw::option<lbcl>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct cpha : mtl::hw::field<cr2, 9, 1> {
                    using option = mtl::hw::option<cpha>;
                    constexpr static option first = 0;
                    constexpr static option second = 1;
                };

                struct cpol : mtl::hw::field<cr2, 10, 1> {
                    using option = mtl::hw::option<cpol>;
                    constexpr static option low = 0;
                    constexpr static option high = 1;
                };

                struct clken : mtl::hw::field<cr2, 11, 1> {
                    using option = mtl::hw::option<clken>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct stop : mtl::hw::field<cr2, 12, 2> {
                    using option = mtl::hw::option<stop>;
                    constexpr static option bits1 = 0;
                    constexpr static option bits0_5 = 1;
                    constexpr static option bits2 = 2;
                    constexpr static option bits1_5 = 3;
                };

                struct linen : mtl::hw::field<cr2, 14, 1> {
                    using option = mtl::hw::option<linen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct swap : mtl::hw::field<cr2, 15, 1> {
                    using option = mtl::hw::option<swap>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct rxinv : mtl::hw::field<cr2, 16, 1> {
                    using option = mtl::hw::option<rxinv>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct txinv : mtl::hw::field<cr2, 17, 1> {
                    using option = mtl::hw::option<txinv>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct datainv : mtl::hw::field<cr2, 18, 1> {
                    using option = mtl::hw::option<datainv>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct msbfirst : mtl::hw::field<cr2, 19, 1> {
                    using option = mtl::hw::option<msbfirst>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct arben : mtl::hw::field<cr2, 20, 1> {
                    using option = mtl::hw::option<arben>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct arbmod : mtl::hw::field<cr2, 21, 2> {
                    using option = mtl::hw::option<arbmod>;
                    constexpr static option start_bit_length = 0;
                    constexpr static option falling_edge_period = 1;
                    constexpr static option frame0x7f = 2;
                    constexpr static option frame0x55 = 3;
                };

                struct rtoen : mtl::hw::field<cr2, 23, 1> {
                    using option = mtl::hw::option<rtoen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct add : mtl::hw::field<cr2, 24, 7> {};
            };

            struct cr3 : register_<0x08, uint32_t> {
                struct eie : mtl::hw::field<cr3, 0, 1> {
                    using option = mtl::hw::option<eie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct iren : mtl::hw::field<cr3, 1, 1> {
                    using option = mtl::hw::option<iren>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct irlp : mtl::hw::field<cr3, 2, 1> {
                    using option = mtl::hw::option<irlp>;
                    constexpr static option normal = 0;
                    constexpr static option low_power = 1;
                };

                struct hdsel : mtl::hw::field<cr3, 3, 1> {
                    using option = mtl::hw::option<hdsel>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct nack : mtl::hw::field<cr3, 4, 1> {
                    using option = mtl::hw::option<nack>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct scen : mtl::hw::field<cr3, 5, 1> {
                    using option = mtl::hw::option<scen>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct dmar : mtl::hw::field<cr3, 6, 1> {
                    using option = mtl::hw::option<dmar>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct dmat : mtl::hw::field<cr3, 7, 1> {
                    using option = mtl::hw::option<dmat>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct rtse : mtl::hw::field<cr3, 8, 1> {
                    using option = mtl::hw::option<rtse>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ctse : mtl::hw::field<cr3, 9, 1> {
                    using option = mtl::hw::option<ctse>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ctsie : mtl::hw::field<cr3, 10, 1> {
                    using option = mtl::hw::option<ctsie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct onebit : mtl::hw::field<cr3, 11, 1> {
                    using option = mtl::hw::option<onebit>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct ovrdis : mtl::hw::field<cr3, 12, 1> {
                    using option = mtl::hw::option<ovrdis>;
                    constexpr static option enabled = 0;
                    constexpr static option disabled = 1;
                };

                struct ddre : mtl::hw::field<cr3, 13, 1> {
                    using option = mtl::hw::option<ddre>;
                    constexpr static option enabled = 0;
                    constexpr static option disabled = 1;
                };

                struct dem : mtl::hw::field<cr3, 14, 1> {
                    using option = mtl::hw::option<dem>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct dep : mtl::hw::field<cr3, 15, 1> {
                    using option = mtl::hw::option<dep>;
                    constexpr static option high = 0;
                    constexpr static option low = 1;
                };

                struct scarcnt : mtl::hw::field<cr3, 17, 3> {};

                struct wus : mtl::hw::field<cr3, 20, 2> {
                    using option = mtl::hw::option<dep>;
                    constexpr static option address = 0;
                    constexpr static option start = 1;
                    constexpr static option rxne = 3;
                };

                struct wufie : mtl::hw::field<cr3, 22, 1> {
                    using option = mtl::hw::option<wufie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct brr : register_<0x0c, uint32_t> {
                struct div : mtl::hw::field<brr, 0, 16> {};
            };

            struct gtpr : register_<0x10, uint32_t> {
                struct psc : mtl::hw::field<gtpr, 0, 8> {};
                struct gt : mtl::hw::field<gtpr, 8, 8> {};
            };

            struct rtor : register_<0x14, uint32_t> {
                struct rto : mtl::hw::field<rtor, 0, 24> {};
                struct blen : mtl::hw::field<rtor, 24, 8> {};
            };

            struct rqr : register_<0x18, uint32_t> {
                struct abrrq : mtl::hw::field<rqr, 0, 1> {
                    using option = mtl::hw::option<abrrq>;
                    constexpr static option request = 1;
                };

                struct sbkrq : mtl::hw::field<rqr, 1, 1> {
                    using option = mtl::hw::option<sbkrq>;
                    constexpr static option request = 1;
                };

                struct mmrq : mtl::hw::field<rqr, 2, 1> {
                    using option = mtl::hw::option<mmrq>;
                    constexpr static option request = 1;
                };

                struct rxfrq : mtl::hw::field<rqr, 3, 1> {
                    using option = mtl::hw::option<rxfrq>;
                    constexpr static option request = 1;
                };

                struct txfrq : mtl::hw::field<rqr, 4, 1> {
                    using option = mtl::hw::option<txfrq>;
                    constexpr static option request = 1;
                };
            };

            struct isr : register_<0x1c, uint32_t> {
                struct pe : mtl::hw::field<isr, 0, 1> {
                    using option = mtl::hw::option<pe>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct fe : mtl::hw::field<isr, 1, 1> {
                    using option = mtl::hw::option<fe>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct ne : mtl::hw::field<isr, 2, 1> {
                    using option = mtl::hw::option<ne>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct ore : mtl::hw::field<isr, 3, 1> {
                    using option = mtl::hw::option<ore>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct idle : mtl::hw::field<isr, 4, 1> {
                    using option = mtl::hw::option<idle>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct rxne : mtl::hw::field<isr, 5, 1> {
                    using option = mtl::hw::option<rxne>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct tc : mtl::hw::field<isr, 6, 1> {
                    using option = mtl::hw::option<tc>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct txe : mtl::hw::field<isr, 7, 1> {
                    using option = mtl::hw::option<txe>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct lbdf : mtl::hw::field<isr, 8, 1> {
                    using option = mtl::hw::option<lbdf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct ctsif : mtl::hw::field<isr, 9, 1> {
                    using option = mtl::hw::option<ctsif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cts : mtl::hw::field<isr, 10, 1> {
                    using option = mtl::hw::option<cts>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct rtof : mtl::hw::field<isr, 11, 1> {
                    using option = mtl::hw::option<rtof>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct eobf : mtl::hw::field<isr, 12, 1> {
                    using option = mtl::hw::option<eobf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct abre : mtl::hw::field<isr, 14, 1> {
                    using option = mtl::hw::option<abre>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct abrf : mtl::hw::field<isr, 15, 1> {
                    using option = mtl::hw::option<abrf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct busy : mtl::hw::field<isr, 16, 1> {
                    using option = mtl::hw::option<busy>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cmf : mtl::hw::field<isr, 17, 1> {
                    using option = mtl::hw::option<cmf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct sbkf : mtl::hw::field<isr, 18, 1> {
                    using option = mtl::hw::option<sbkf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct rwu : mtl::hw::field<isr, 19, 1> {
                    using option = mtl::hw::option<rwu>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct wuf : mtl::hw::field<isr, 20, 1> {
                    using option = mtl::hw::option<wuf>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct teack : mtl::hw::field<isr, 21, 1> {
                    using option = mtl::hw::option<teack>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct reack : mtl::hw::field<isr, 22, 1> {
                    using option = mtl::hw::option<reack>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };

            struct icr : register_<0x20, uint32_t> {
                struct pecf : mtl::hw::field<isr, 0, 1> {
                    using option = mtl::hw::option<pecf>;
                    constexpr static option clear = 1;
                };

                struct fecf : mtl::hw::field<isr, 1, 1> {
                    using option = mtl::hw::option<fecf>;
                    constexpr static option clear = 1;
                };

                struct ncf : mtl::hw::field<isr, 2, 1> {
                    using option = mtl::hw::option<ncf>;
                    constexpr static option clear = 1;
                };

                struct orecf : mtl::hw::field<isr, 3, 1> {
                    using option = mtl::hw::option<orecf>;
                    constexpr static option clear = 1;
                };

                struct idlecf : mtl::hw::field<isr, 4, 1> {
                    using option = mtl::hw::option<idlecf>;
                    constexpr static option clear = 1;
                };

                struct ttcf : mtl::hw::field<isr, 6, 1> {
                    using option = mtl::hw::option<ttcf>;
                    constexpr static option clear = 1;
                };

                struct lbdcf : mtl::hw::field<isr, 8, 1> {
                    using option = mtl::hw::option<lbdcf>;
                    constexpr static option clear = 1;
                };

                struct ctscf : mtl::hw::field<isr, 9, 1> {
                    using option = mtl::hw::option<ctscf>;
                    constexpr static option clear = 1;
                };

                struct rtocf : mtl::hw::field<isr, 11, 1> {
                    using option = mtl::hw::option<rtocf>;
                    constexpr static option clear = 1;
                };

                struct eobcf : mtl::hw::field<isr, 12, 1> {
                    using option = mtl::hw::option<eobcf>;
                    constexpr static option clear = 1;
                };

                struct cmcf : mtl::hw::field<isr, 17, 1> {
                    using option = mtl::hw::option<cmcf>;
                    constexpr static option clear = 1;
                };

                struct wucf : mtl::hw::field<isr, 20, 1> {
                    using option = mtl::hw::option<wucf>;
                    constexpr static option clear = 1;
                };
            };

            struct rdr : register_<0x24, uint32_t> {
                struct dr : mtl::hw::field<dr, 0, 9> {};
            };

            struct tdr : register_<0x28, uint32_t> {
                struct dr : mtl::hw::field<dr, 0, 9> {};
            };
        };
    } // namespace descriptor

    using usart1 = descriptor::usart<0x40013800>;
    using usart2 = descriptor::usart<0x40004400>;
    using usart3 = descriptor::usart<0x40004800>;
    using usart4 = descriptor::usart<0x40004C00>;
    using usart5 = descriptor::usart<0x40005000>;
    using usart6 = descriptor::usart<0x40011400>;
    using usart7 = descriptor::usart<0x40011800>;
    using usart8 = descriptor::usart<0x40011C00>;

    template <class> struct usart;
    template <> struct usart<mtl::hw::ids::usart1> : usart1 {};
    template <> struct usart<mtl::hw::ids::usart2> : usart2 {};
    template <> struct usart<mtl::hw::ids::usart3> : usart3 {};
    template <> struct usart<mtl::hw::ids::usart4> : usart4 {};
    template <> struct usart<mtl::hw::ids::usart5> : usart5 {};
    template <> struct usart<mtl::hw::ids::usart6> : usart6 {};
    template <> struct usart<mtl::hw::ids::usart7> : usart7 {};
    template <> struct usart<mtl::hw::ids::usart8> : usart8 {};
} // namespace mtl::hw
