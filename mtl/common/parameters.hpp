#pragma once

#include <type_traits>



namespace mtl {
    namespace detail {
        template<template<class...> class t_template_type, class>
        struct types_has_same_enclosure {
            constexpr static bool value = false;
        };
        
        template<template<class...> class t_template_type, class... t_parameters>
        struct types_has_same_enclosure<t_template_type, t_template_type<t_parameters...>> {
            constexpr static bool value = true;
        };
        
        template<template<auto...> class t_template_type, class>
        struct values_has_same_enclosure {
            constexpr static bool value = false;  
        };
        
        template<template<auto...> class t_template_type, auto... t_parameters>
        struct values_has_same_enclosure<t_template_type, t_template_type<t_parameters...>> {
            constexpr static bool value = true;
        };
        
        struct find_parameter_in_set {
            template<template<class...> class t_template_type, class t_first, class... t_rest>
            static auto evaluate() {
                return typename std::add_pointer<typename std::conditional<
                    types_has_same_enclosure<t_template_type, t_first>::value,
                    t_first,
                    typename std::remove_pointer<decltype(find_parameter_in_set::evaluate<t_template_type, t_rest...>())>::type
                >::type>::type{};
            }
            
            template<template<class...> class t_template_type>
            static auto evaluate() {
                return typename std::add_pointer<void>::type{};
            }
            
            template<template<auto...> class t_template_type, class t_first, class... t_rest>
            static auto evaluate() {
                return typename std::add_pointer<typename std::conditional<
                    values_has_same_enclosure<t_template_type, t_first>::value,
                    t_first,
                    typename std::remove_pointer<decltype(find_parameter_in_set::evaluate<t_template_type, t_rest...>())>::type
                >::type>::type{};
            }
            
            template<template<auto...> class t_template_type>
            static auto evaluate() {
                return typename std::add_pointer<void>::type{};
            }
        };
    }

    
    template<class... t_parameters>
    struct parameters {
        template<template<auto...> class t_template_type>
        struct find {
            using type = typename std::remove_pointer<decltype(detail::find_parameter_in_set::evaluate<t_template_type, t_parameters...>())>::type;
        };
        
        template<template<class...> class t_template_type>
        struct find_type {
            using type = typename std::remove_pointer<decltype(detail::find_parameter_in_set::evaluate<t_template_type, t_parameters...>())>::type;
        };
    };
}
