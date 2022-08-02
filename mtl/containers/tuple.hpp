#pragma once

#include <cstddef>
#include <utility>

#include <mtl/traits/list.hpp>

namespace mtl {
    namespace detail {
        template <size_t v_index, class t_type> struct tuple_leaf {
            using type = t_type;
            constexpr static size_t index = v_index;

            tuple_leaf(type &&value_) : value(value_) {}

            type value;
        };

        template <class...> class tuple;

        template <size_t... v_indexes, class... t_parameters>
        class tuple<std::index_sequence<v_indexes...>, t_parameters...> :
            public tuple_leaf<v_indexes, t_parameters>... {
        public:
            using types = mtl::traits::list<t_parameters...>;
            constexpr static size_t size = types::length;
            
            tuple(t_parameters &&... values)
                : tuple_leaf<v_indexes, t_parameters>(std::forward<t_parameters>(values))... {}

            template <size_t v_index> auto &get() {
                return static_cast<tuple_leaf<v_index, typename mtl::traits::find_by_index<v_index, types>::type> *>(
                           this)
                    ->value;
            }

            template <size_t v_index> const auto &get() const {
                return static_cast<
                           const tuple_leaf<v_index, typename mtl::traits::find_by_index<v_index, types>::type> *>(this)
                    ->value;
            }
        };

    } // namespace detail

    template <class... t_parameters>
    using tuple = detail::tuple<std::make_index_sequence<sizeof...(t_parameters)>, t_parameters...>;

    template <size_t v_index, class... t_parameters> auto &get(tuple<t_parameters...> &value) {
        return value.template get<v_index>();
    }

    template <size_t v_index, class... t_parameters> const auto &get(const tuple<t_parameters...> &value) {
        return value.template get<v_index>();
    }
} // namespace mtl
