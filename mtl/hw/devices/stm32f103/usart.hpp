

#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace mtl::hw {
    namespace descriptor {
        template <uint32_t v_base_address> struct usart {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct sr : register_<0x00, uint32_t> {
                struct pe : mtl::hw::field<sr, 0, 1> {
                    using option = mtl::hw::option<pe>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct fe : mtl::hw::field<sr, 1, 1> {
                    using option = mtl::hw::option<fe>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct ne : mtl::hw::field<sr, 2, 1> {
                    using option = mtl::hw::option<ne>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct ore : mtl::hw::field<sr, 3, 1> {
                    using option = mtl::hw::option<ore>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct idle : mtl::hw::field<sr, 4, 1> {
                    using option = mtl::hw::option<idle>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct rxne : mtl::hw::field<sr, 5, 1> {
                    using option = mtl::hw::option<rxne>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct tc : mtl::hw::field<sr, 6, 1> {
                    using option = mtl::hw::option<tc>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct txe : mtl::hw::field<sr, 7, 1> {
                    using option = mtl::hw::option<txe>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct lbd : mtl::hw::field<sr, 8, 1> {
                    using option = mtl::hw::option<lbd>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct cts : mtl::hw::field<cts, 9, 1> {
                    using option = mtl::hw::option<cts>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };

            struct dr : register_<0x04, uint32_t> {
                struct d : mtl::hw::field<dr, 0, 9> {};
            };

            struct brr : register_<0x08, uint32_t> {
                struct div : mtl::hw::field<brr, 0, 16> {};
            };

            struct cr1 : register_<0x0c, uint32_t> {
                struct sbk : mtl::hw::field<cr1, 0, 1> {
                    using option = mtl::hw::option<sbk>;
                    constexpr static option send = 1;
                };

                struct rwu : mtl::hw::field<cr1, 1, 1> {
                    using option = mtl::hw::option<rwu>;
                    constexpr static option active = 0;
                    constexpr static option mute = 1;
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

                struct m : mtl::hw::field<cr1, 12, 1> {
                    using option = mtl::hw::option<m>;
                    constexpr static option bits8 = 0;
                    constexpr static option bits9 = 1;
                };

                struct ue : mtl::hw::field<cr1, 13, 1> {
                    using option = mtl::hw::option<ue>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct cr2 : register_<0x10, uint32_t> {
                struct add : mtl::hw::field<cr2, 0, 3> {};

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
            };

            struct cr3 : register_<0x14, uint32_t> {
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
            };

            struct gtpr : register_<0x18, uint32_t> {
                struct psc : mtl::hw::field<gtpr, 0, 8> {};
                struct gt : mtl::hw::field<gtpr, 8, 8> {};
            };
        };
    } // namespace descriptor

    using usart1 = descriptor::usart<0x40013800>;
    using usart2 = descriptor::usart<0x40004400>;
    using usart3 = descriptor::usart<0x40004800>;
    using uart4 = descriptor::usart<0x40004c00>;
    using uart5 = descriptor::usart<0x40005000>;

    template <class> struct usart;
    template <> struct timer<mtl::hw::ids::usart1> : usart1 {};
    template <> struct timer<mtl::hw::ids::usart2> : usart2 {};
    template <> struct timer<mtl::hw::ids::usart3> : usart3 {};
    template <> struct timer<mtl::hw::ids::usart4> : uart4 {};
    template <> struct timer<mtl::hw::ids::usart5> : uart5 {};
} // namespace mtl::hw
