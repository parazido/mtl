#pragma once

#include <cstdint>

#include <mtl/hw/descriptor.hpp>
#include <mtl/hw/device.hpp>

namespace mtl::hw {
    namespace descriptor {
        template <uint32_t v_base_address> struct gpio {
            constexpr static uint32_t base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct crl : register_<0x00, uint32_t> {
                template <uint8_t v_index> struct mode : mtl::hw::field<crl, v_index * 4, 2> {
                    using option = mtl::hw::option<mode>;
                    constexpr static option input = 0;
                    constexpr static option output_10mhz = 1;
                    constexpr static option output_2mhz = 2;
                    constexpr static option output_50mhz = 3;
                };

                template <uint8_t v_index> struct cnf_in : mtl::hw::field<crl, v_index * 4 + 2, 2> {
                    using option = mtl::hw::option<cnf_in>;
                    constexpr static option analog = 0;
                    constexpr static option floating = 1;
                    constexpr static option pupd = 2;
                };

                template <uint8_t v_index> struct cnf_out : mtl::hw::field<crl, v_index * 4 + 2, 2> {
                    using option = mtl::hw::option<cnf_out>;
                    constexpr static option gp_pp = 0;
                    constexpr static option gp_od = 1;
                    constexpr static option alternate_pp = 2;
                    constexpr static option alternate_od = 3;
                };
            };

            struct crh : register_<0x04, uint32_t> {
                template <uint8_t v_index> struct mode : mtl::hw::field<crh, v_index * 4, 2> {
                    using option = mtl::hw::option<mode>;
                    constexpr static option input = 0;
                    constexpr static option output_10mhz = 1;
                    constexpr static option output_2mhz = 2;
                    constexpr static option output_50mhz = 3;
                };

                template <uint8_t v_index> struct cnf_in : mtl::hw::field<crh, v_index * 4 + 2, 2> {
                    using option = mtl::hw::option<cnf_in>;
                    constexpr static option analog = 0;
                    constexpr static option floating = 1;
                    constexpr static option pupd = 2;
                };

                template <uint8_t v_index> struct cnf_out : mtl::hw::field<crh, v_index * 4 + 2, 2> {
                    using option = mtl::hw::option<cnf_out>;
                    constexpr static option gp_pp = 0;
                    constexpr static option gp_od = 1;
                    constexpr static option alternate_pp = 2;
                    constexpr static option alternate_od = 3;
                };
            };

            struct idr : register_<0x08, uint32_t> {};
            struct odr : register_<0x0c, uint32_t> {};
            struct bsrr : register_<0x10, uint32_t> {
                template <uint8_t v_index> struct bs : mtl::hw::field<bsrr, v_index, 1> {
                    using option = mtl::hw::option<bs>;
                    constexpr static option set = 1;
                };

                template <uint8_t v_index> struct br : mtl::hw::field<bsrr, v_index + 16, 1> {
                    using option = mtl::hw::option<br>;
                    constexpr static option set = 1;
                };
            };
            struct brr : register_<0x14, uint32_t> {};
            struct lckr : register_<0x0c, uint32_t> {
                struct lck : mtl::hw::field<lckr, 0, 16> {};
                struct lckk : mtl::hw::field<lckr, 16, 1> {};
            };
        };
    } // namespace descriptor

    using gpioa = descriptor::gpio<0x40010800>;
    using gpiob = descriptor::gpio<0x40010C00>;
    using gpioc = descriptor::gpio<0x40011000>;
    using gpiod = descriptor::gpio<0x40011400>;
    using gpioe = descriptor::gpio<0x40011800>;
    using gpiof = descriptor::gpio<0x40011c00>;
    using gpiog = descriptor::gpio<0x40012000>;

    template <class t_device_id> struct gpio;
    template <> struct gpio<mtl::hw::ids::gpioa> : gpioa {};
    template <> struct gpio<mtl::hw::ids::gpiob> : gpiob {};
    template <> struct gpio<mtl::hw::ids::gpioc> : gpioc {};
    template <> struct gpio<mtl::hw::ids::gpiod> : gpiod {};
    template <> struct gpio<mtl::hw::ids::gpioe> : gpioe {};
    template <> struct gpio<mtl::hw::ids::gpiof> : gpiof {};
    template <> struct gpio<mtl::hw::ids::gpiog> : gpiog {};

} // namespace mtl::hw
