#pragma once

#include <cstdint>
#include <type_traits>

#include <mtl/common/parameters.hpp>

namespace mtl::traits {
    namespace typesp {
        template <bool v_is_signed, uint8_t v_width> struct min_integral {
            constexpr static bool is_signed = v_is_signed;
            constexpr static uint8_t width = v_width;
        };

        template <uint64_t v_value> struct min_integral_for_value { constexpr static uint64_t value = v_value; };

        template <uint8_t v_width> struct min_floating { constexpr static uint8_t width = v_width; };
    } // namespace typesp

    namespace detail {
        template <bool v_is_signed, uint8_t v_width> struct use_min_integral_type;

        template <uint8_t v_width> struct use_min_integral_type<false, v_width> {
            using type = typename std::conditional<
                v_width <= 8, uint8_t,
                typename std::conditional<v_width <= 16, uint16_t,
                                          typename std::conditional<v_width <= 32, uint32_t, uint64_t>::type>::type>::
                type;
        };

        template <uint8_t v_width> struct use_min_integral_type<true, v_width> {
            using type = typename std::make_signed<typename use_min_integral_type<false, v_width>::type>::type;
        };

        template <uint8_t v_width> struct use_min_floating_type {
            using type = typename std::conditional<(v_width <= 23), float, double>::type;
        };

        template <uint64_t v_value> struct use_min_integral_type_for_value {
            using type = typename std::conditional<
                v_value <= 0xff, uint8_t,
                typename std::conditional<
                    v_value <= 0xffff, uint16_t,
                    typename std::conditional<v_value <= 0xffffffff, uint32_t, uint64_t>::type>::type>::type;
        };
    } // namespace detail

    struct types {
        template <class...> struct pick;

        template <bool v_is_signed, uint8_t v_width> struct pick<typesp::min_integral<v_is_signed, v_width>> {
            using type = typename detail::use_min_integral_type<v_is_signed, v_width>::type;
        };

        template <uint8_t v_width> struct pick<typesp::min_floating<v_width>> {
            using type = typename detail::use_min_floating_type<v_width>::type;
        };

        template <uint64_t v_value> struct pick<typesp::min_integral_for_value<v_value>> {
            using type = typename detail::use_min_integral_type_for_value<v_value>::type;
        };
    };
} // namespace mtl::traits
