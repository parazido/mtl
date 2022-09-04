#pragma once

#include <cstddef>
#include <type_traits>

#include <mtl/traits/accumulate.hpp>
#include <mtl/traits/apply.hpp>

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

    // Find element by index.
    template <size_t v_index, class t_list> struct find_by_index {
        using type = typename find_by_index<v_index - 1, typename t_list::next>::type;
    };

    template <class t_list> struct find_by_index<0, t_list> { using type = typename t_list::type; };

    // Apply operator to list elements.
    template <class... t_elements, template <class> class t_operator>
    struct apply<mtl::traits::list<t_elements...>, t_operator> {
        using type = mtl::traits::list<typename t_operator<t_elements>::type...>;
    };

    // Accumulate list elements.
    template <template <class, class> class t_operator, class t_initial, class t_first, class... t_rest>
    struct accumulate<mtl::traits::list<t_first, t_rest...>, t_initial, t_operator> {
        using type = typename accumulate<mtl::traits::list<t_rest...>, typename t_operator<t_initial, t_first>::type, t_operator>::type;
    };

    template <template <class, class> class t_operator, class t_initial, class t_last>
    struct accumulate<mtl::traits::list<t_last>, t_initial, t_operator> {
        using type = typename t_operator<t_initial, t_last>::type;
    };

    template <template <class, class> class t_operator, class t_initial>
    struct accumulate<mtl::traits::list<>, t_initial, t_operator> {
        using type = t_initial;
    };

} // namespace mtl::traits
