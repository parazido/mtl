

#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace mtl::hw {
    namespace descriptor {
        template <uint32_t v_base_address> struct wwdg {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct cr : register_<0x00, uint32_t> {
                struct t : mtl::hw::field<cr, 0, 7> {};

                struct wdga : mtl::hw::field<cr, 0, 3> {
                    using option = mtl::hw::option<wdga>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct cfr : register_<0x04, uint32_t> {
                struct w : mtl::hw::field<cfr, 0, 7> {};

                struct wdgtb : mtl::hw::field<cfr, 7, 2> {
                    using option = mtl::hw::option<wdgtb>;
                    constexpr static option no = 0;
                    constexpr static option div2 = 1;
                    constexpr static option div4 = 1;
                    constexpr static option div8 = 1;
                };

                struct ewi : mtl::hw::field<cfr, 9, 1> {
                    using option = mtl::hw::option<ewi>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };

            struct sr : register_<0x08, uint32_t> {
                struct ewif : mtl::hw::field<sr, 0, 1> {
                    using option = mtl::hw::option<ewif>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };
        };
    } // namespace descriptor

    using wwdg = descriptor::wwdg<0x40002c00>;
} // namespace mtl::hw
