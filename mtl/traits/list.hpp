#pragma once

#include <cstddef>
#include <type_traits>

namespace mtl::traits {
    namespace detail {
        template <class t_entry, class... t_entries> struct entry_in_list {
            constexpr static bool value = (std::is_same<t_entry, t_entries>::value | ...);
        };
    } // namespace detail

    // List.
    template <class...> struct list;

    template <class t_first, class... t_rest> struct list<t_first, t_rest...> {
        using type = t_first;
        using next = list<t_rest...>;

        template <class t_entry>
        constexpr static bool contains = detail::entry_in_list<t_entry, t_first, t_rest...>::value;
        constexpr static size_t length = sizeof...(t_rest) + 1;
    };

    template <class t_last> struct list<t_last> {
        using type = t_last;
        using next = void;

        template <class t_entry> constexpr static bool contains = detail::entry_in_list<t_entry, t_last>::value;
        constexpr static size_t length = 1;
    };

    template <> struct list<> {
        using type = void;
        using next = void;

        template <class t_entry> constexpr static bool contains = false;
        constexpr static size_t length = 0;
    };

    // Checks if type is in container.
    template <class...> struct is_in;

    template <class t_type, class... t_list_types> struct is_in<list<t_list_types...>, t_type> {
        constexpr static bool value = (std::is_same<t_list_types, t_type>::value | ...);
    };
} // namespace mtl::traits
