#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace mtl::hw {
    namespace descriptor {
        template <uint32_t v_base_address> struct flash {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct acr : register_<0x00, uint32_t> {
                struct latency : mtl::hw::field<acr, 0, 3> {
                    using option = mtl::hw::option<latency>;
                    constexpr static option zero = 0;
                    constexpr static option one = 1;
                    constexpr static option two = 2;
                };

                struct prftbe : mtl::hw::field<acr, 4, 1> {
                    using option = mtl::hw::option<prftbe>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct prftbs : mtl::hw::field<acr, 5, 1> {
                    using option = mtl::hw::option<prftbs>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };
            };
        };
    } // namespace descriptor

    using flash = descriptor::flash<0x40022000>;
} // namespace mtl::hw
