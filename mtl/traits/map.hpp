#pragma once

#include <cstddef>
#include <type_traits>

#include <mtl/traits/isin.hpp>

namespace mtl::traits {
    namespace detail {
        template <class t_key, class... t_pairs> struct key_in_map {
            constexpr static bool value = (std::is_same<t_key, typename t_pairs::key>::value | ...);
        };
    } // namespace detail

    // Pair.
    template <class t_key, class t_value> struct pair {
        using key = t_key;
        using value = t_value;
    };

    // Map.
    template <class...> struct map;

    template <class t_first, class... t_rest> struct map<t_first, t_rest...> {
        using type = t_first;
        using next = map<t_rest...>;

        template <class t_key> struct find {
            using type = typename std::conditional<std::is_same<t_key, typename t_first::key>::value, t_first,
                                                   typename map<t_rest...>::find<t_key>::type>::type;
        };

        template <class t_key> constexpr static bool contains = detail::key_in_map<t_key, t_first, t_rest...>::value;
        constexpr static size_t length = sizeof...(t_rest) + 1;
    };

    template <class t_last> struct map<t_last> {
        using type = t_last;
        using next = void;

        template <class t_key> struct find {
            using type =
                typename std::conditional<std::is_same<t_key, typename t_last::key>::value, t_last, void>::type;
        };

        template <class t_key> constexpr static bool contains = detail::key_in_map<t_key, t_last>::value;
        constexpr static size_t length = 1;
    };

    template <> struct map<> {
        using type = void;
        using next = void;

        template <class t_key> struct find { using type = void; };

        template <class t_key> constexpr static bool contains = false;
        constexpr static size_t length = 0;
    };

    template <class t_key, class... t_pairs> struct is_in<map<t_pairs...>, t_key> {
        constexpr static bool value = (std::is_same<typename t_pairs::key, t_key>::value | ...);
    };
} // namespace mtl::traits
