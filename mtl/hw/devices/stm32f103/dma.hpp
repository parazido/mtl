#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace devices {
    namespace descriptor {
        template <uint32_t v_base_address> struct dma {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct isr : register_<0x00, uint32_t> {
                template <uint8_t v_index> struct gif : mtl::hw::field<isr, v_index * 4, 1> {
                    using option = mtl::hw::option<gif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                template <uint8_t v_index> struct tcif : mtl::hw::field<isr, v_index * 4 + 1, 1> {
                    using option = mtl::hw::option<tcif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                template <uint8_t v_index> struct htif : mtl::hw::field<isr, v_index * 4 + 2, 1> {
                    using option = mtl::hw::option<htif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                template <uint8_t v_index> struct teif : mtl::hw::field<isr, v_index * 4 + 3, 1> {
                    using option = mtl::hw::option<teif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };

            struct ifcr : register_<0x04, uint32_t> {
                template <uint8_t v_index> struct cgif : mtl::hw::field<ifcr, v_index * 4, 1> {
                    using option = mtl::hw::option<cgif>;
                    constexpr static option clear = 1;
                };

                template <uint8_t v_index> struct ctcif : mtl::hw::field<ifcr, v_index * 4 + 1, 1> {
                    using option = mtl::hw::option<ctcif>;
                    constexpr static option clear = 1;
                };

                template <uint8_t v_index> struct chtif : mtl::hw::field<ifcr, v_index * 4 + 2, 1> {
                    using option = mtl::hw::option<chtif>;
                    constexpr static option clear = 1;
                };

                template <uint8_t v_index> struct cteif : mtl::hw::field<ifcr, v_index * 4 + 3, 1> {
                    using option = mtl::hw::option<cteif>;
                    constexpr static option clear = 1;
                };
            };

            template <uint8_t v_reg_index> struct ccr : register_<0x08 + v_reg_index * 20, uint32_t> {
                struct en : mtl::hw::field<ccr, 0, 1> {
                    using option = mtl::hw::option<en>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct tcie : mtl::hw::field<ccr, 1, 1> {
                    using option = mtl::hw::option<tcie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct htie : mtl::hw::field<ccr, 2, 1> {
                    using option = mtl::hw::option<htie>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct teie : mtl::hw::field<ccr, 3, 1> {
                    using option = mtl::hw::option<teie>;
                    constexpr static option enabled = 0;
                    constexpr static option disabled = 1;
                };

                struct dir : mtl::hw::field<ccr, 4, 1> {
                    using option = mtl::hw::option<dir>;
                    constexpr static option from_peripheral = 0;
                    constexpr static option from_memory = 1;
                };

                struct circ : mtl::hw::field<ccr, 5, 1> {
                    using option = mtl::hw::option<circ>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct pinc : mtl::hw::field<ccr, 6, 1> {
                    using option = mtl::hw::option<pinc>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct mirc : mtl::hw::field<ccr, 7, 1> {
                    using option = mtl::hw::option<minc>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct psize : mtl::hw::field<ccr, 8, 2> {
                    using option = mtl::hw::option<psize>;
                    constexpr static option bits8 = 0;
                    constexpr static option bits16 = 1;
                    constexpr static option bits32 = 2;
                };

                struct msize : mtl::hw::field<ccr, 10, 2> {
                    using option = mtl::hw::option<msize>;
                    constexpr static option bits8 = 0;
                    constexpr static option bits16 = 1;
                    constexpr static option bits32 = 2;
                };

                struct pl : mtl::hw::field<ccr, 12, 2> {
                    using option = mtl::hw::option<pl>;
                    constexpr static option low = 0;
                    constexpr static option medium = 1;
                    constexpr static option high = 2;
                    constexpr static option bits32 = 3;
                };

                struct mem2mem : mtl::hw::field<ccr, 14, 1> {
                    using option = mtl::hw::option<mem2mem>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            template <uint8_t v_reg_index> struct cndtr : register_<0x0c + v_reg_index * 20, uint32_t> {
                struct ndt : mtl::hw::field<cndtr, 0, 16> {};
            };

            template <uint8_t v_reg_index> struct cpar : register_<0x10 + v_reg_index * 20, uint32_t> {};

            template <uint8_t v_reg_index> struct cmar : register_<0x14 + v_reg_index * 20, uint32_t> {};
        };
    } // namespace descriptor

    using dma1 = descriptor::dma<0x40020000>;
    using dma2 = descriptor::dma<0x40020400>;
} // namespace devices
