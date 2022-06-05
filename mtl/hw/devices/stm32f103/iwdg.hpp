#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace devices {
    namespace descriptor {
        template <uint32_t v_base_address> struct iwdg {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct kr : register_<0x00, uint32_t> {
                struct key : mtl::hw::field<key, 0, 16> {};
            };

            struct pr : register_<0x04, uint32_t> {
                struct pr : mtl::hw::field<pr, 0, 3> {
                    using option = mtl::hw::option<pr>;
                    constexpr static option div4 = 0;
                    constexpr static option div8 = 1;
                    constexpr static option div16 = 2;
                    constexpr static option div32 = 3;
                    constexpr static option div64 = 4;
                    constexpr static option div128 = 5;
                    constexpr static option div256 = 6;
                };
            };

            struct rlr : register_<0x08, uint32_t> {
                struct rl : mtl::hw::field<rl, 0, 12> {};
            };

            struct sr : register_<0x0c, uint32_t> {
                struct pvu : mtl::hw::field<pvu, 0, 1> {
                    using option = mtl::hw::option<sr>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };

                struct rvu : mtl::hw::field<rvu, 1, 1> {
                    using option = mtl::hw::option<sr>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };
        };
    } // namespace descriptor

    using iwdg = descriptor::iwdg<0x40003000>;
} // namespace devices
