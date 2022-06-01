#pragma once

#include <mtl/common/parameters.hpp>
#include <mtl/traits/list.hpp>

namespace mtl {
    namespace bmp {
        template <class t_underlying_type> struct underlying_type { using type = t_underlying_type; };

        template <auto v_value> struct raw { constexpr static decltype(v_value) value = v_value; };

        struct operators {
            struct set {};
            template <uint8_t> struct set_from {};
            template <uint8_t> struct set_to {};
        };

        template <class... t_elements> using modify = mtl::traits::list<t_elements...>;
    }; // namespace bmp

    namespace detail {
        template <class t_underlying_type, uint8_t v_range_start, uint8_t v_range_end, uint8_t v_index = 0,
                  typename std::make_unsigned<t_underlying_type>::type v_local_mask = 1>
        struct build_mask_by_range {
            using bit = typename std::conditional<
                (v_range_start <= v_index && v_index < v_range_end),
                std::integral_constant<t_underlying_type, static_cast<t_underlying_type>(v_local_mask)>,
                std::integral_constant<t_underlying_type, 0>>::type;
            using next_bit = typename std::conditional<
                (v_index < v_range_end),
                build_mask_by_range<t_underlying_type, v_range_start, v_range_end, v_index + 1,
                                    static_cast<typename std::make_unsigned<t_underlying_type>::type>(v_local_mask
                                                                                                      << 1)>,
                std::integral_constant<t_underlying_type, 0>>::type;
            constexpr static t_underlying_type value = bit::value | next_bit::value;
        };

        template <auto, class> struct apply_operator;

        template <auto v_value> struct apply_operator<v_value, bmp::operators::set> {
            using underlying_type = decltype(v_value);
            constexpr static underlying_type value
                = build_mask_by_range<underlying_type, 0, sizeof(underlying_type) * 8>::value;
        };

        template <auto v_value, uint8_t v_srart_index>
        struct apply_operator<v_value, bmp::operators::set_from<v_srart_index>> {
            using underlying_type = decltype(v_value);
            constexpr static underlying_type value
                = build_mask_by_range<underlying_type, v_srart_index, sizeof(underlying_type) * 8>::value;
        };

        template <auto v_value, uint8_t v_end_index>
        struct apply_operator<v_value, bmp::operators::set_to<v_end_index>> {
            using underlying_type = decltype(v_value);
            constexpr static underlying_type value = build_mask_by_range<underlying_type, 0, v_end_index>::value;
        };

        template <auto v_value> struct apply_operator<v_value, void> {
            using underlying_type = decltype(v_value);
            constexpr static underlying_type value = v_value;
        };

        template <auto v_value, class t_modify> struct apply_operators {
            constexpr static decltype(v_value) value
                = apply_operators<apply_operator<v_value, typename t_modify::type>::value,
                                  typename t_modify::next>::value;
        };

        template <auto v_value> struct apply_operators<v_value, void> {
            constexpr static decltype(v_value) value = v_value;
        };

    }; // namespace detail

    template <class... t_parameters> class bitmask {
    public:
        using underlying_type =
            typename mtl::parameters<t_parameters...>::template find_type<bmp::underlying_type>::type::type;
        using modify = typename mtl::parameters<t_parameters...>::template find_type<bmp::modify, bmp::modify<>>::type;
        using raw_value_type =
            typename mtl::parameters<t_parameters...>::template find<bmp::raw,
                                                                     bmp::raw<static_cast<underlying_type>(0)>>::type;

        constexpr static underlying_type raw_value = raw_value_type::value;
        constexpr static underlying_type value = detail::apply_operators<raw_value, modify>::value;
    };
} // namespace mtl
