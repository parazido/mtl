#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace mtl::hw {
    namespace descriptor {
        template <uint32_t v_base_address> struct gpio {
            constexpr static unsigned int base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct moder : register_<0x00, uint32_t> {
                template <uint8_t v_index> struct mode : mtl::hw::field<moder, v_index * 2, 2> {
                    using option = mtl::hw::option<mode>;
                    constexpr static option input = 0;
                    constexpr static option output = 1;
                    constexpr static option alternate = 2;
                    constexpr static option analog = 3;
                };
            };

            struct otyper : register_<0x04, uint32_t> {
                template <uint8_t v_index> struct otype : mtl::hw::field<otyper, v_index, 1> {
                    using option = mtl::hw::option<otype>;
                    constexpr static option push_pull = 0;
                    constexpr static option open_drain = 1;
                };
            };

            struct ospeedr : register_<0x08, uint32_t> {
                template <uint8_t v_index> struct ospeed : mtl::hw::field<ospeedr, v_index * 2, 2> {
                    using option = mtl::hw::option<ospeed>;
                    constexpr static option low = 0;
                    constexpr static option medium = 2;
                    constexpr static option high = 3;
                };
            };

            struct pupdr : register_<0x0c, uint32_t> {
                template <uint8_t v_index> struct pupd : mtl::hw::field<pupdr, v_index * 2, 2> {
                    using option = mtl::hw::option<pupd>;
                    constexpr static option no = 0;
                    constexpr static option pull_up = 1;
                    constexpr static option pull_down = 2;
                };
            };

            struct idr : register_<0x10, uint16_t> {};
            struct ord : register_<0x14, uint16_t> {};

            struct bsrr : register_<0x18, uint32_t> {
                template <uint8_t v_index> struct bs : mtl::hw::field<bsrr, v_index, 1> {
                    using option = mtl::hw::option<bs>;
                    constexpr static option set = 1;
                };

                template <uint8_t v_index> struct br : mtl::hw::field<bsrr, v_index + 16, 1> {
                    using option = mtl::hw::option<br>;
                    constexpr static option set = 1;
                };
            };

            struct lckr : register_<0x1c, uint32_t> {
                struct lck : mtl::hw::field<lckr, 0, 16> {};
                struct lckk : mtl::hw::field<lckr, 16, 1> {};
            };

            struct afrl : register_<0x20, uint32_t> {
                template <uint8_t v_index> struct af : mtl::hw::field<afrl, v_index * 4, 4> {
                    using option = mtl::hw::option<af>;
                    constexpr static option af0 = 0;
                    constexpr static option af1 = 1;
                    constexpr static option af2 = 2;
                    constexpr static option af3 = 3;
                    constexpr static option af4 = 4;
                    constexpr static option af5 = 5;
                    constexpr static option af6 = 6;
                    constexpr static option af7 = 7;
                    constexpr static option af8 = 8;
                    constexpr static option af9 = 9;
                    constexpr static option af10 = 10;
                    constexpr static option af11 = 11;
                    constexpr static option af12 = 12;
                    constexpr static option af13 = 13;
                    constexpr static option af14 = 14;
                    constexpr static option af15 = 15;
                };
            };

            struct afrh : register_<0x24, uint32_t> {
                template <uint8_t v_index> struct af : mtl::hw::field<afrh, v_index * 4, 4> {
                    using option = mtl::hw::option<af>;
                    constexpr static option af0 = 0;
                    constexpr static option af1 = 1;
                    constexpr static option af2 = 2;
                    constexpr static option af3 = 3;
                    constexpr static option af4 = 4;
                    constexpr static option af5 = 5;
                    constexpr static option af6 = 6;
                    constexpr static option af7 = 7;
                    constexpr static option af8 = 8;
                    constexpr static option af9 = 9;
                    constexpr static option af10 = 10;
                    constexpr static option af11 = 11;
                    constexpr static option af12 = 12;
                    constexpr static option af13 = 13;
                    constexpr static option af14 = 14;
                    constexpr static option af15 = 15;
                };
            };

            struct brr : register_<0x28, uint32_t> {
                template <uint8_t v_index> struct br : mtl::hw::field<brr, v_index, 1> {
                    using option = mtl::hw::option<br>;
                    constexpr static option reset = 1;
                };
            };
        };
    } // namespace descriptor

    using gpioa = descriptor::gpio<0x48000000>;
    using gpiob = descriptor::gpio<0x48000400>;
    using gpioc = descriptor::gpio<0x48000800>;
    using gpiod = descriptor::gpio<0x48000C00>;
    using gpioe = descriptor::gpio<0x48001000>;
    using gpiof = descriptor::gpio<0x48001400>;

    template <class t_device_id> struct gpio;
    template <> struct gpio<mtl::hw::ids::gpioa> : gpioa {};
    template <> struct gpio<mtl::hw::ids::gpiob> : gpiob {};
    template <> struct gpio<mtl::hw::ids::gpioc> : gpioc {};
    template <> struct gpio<mtl::hw::ids::gpiod> : gpiod {};
    template <> struct gpio<mtl::hw::ids::gpioe> : gpioe {};
    template <> struct gpio<mtl::hw::ids::gpiof> : gpiof {};
} // namespace mtl::hw
