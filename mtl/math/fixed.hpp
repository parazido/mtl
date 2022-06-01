#pragma once

#include <cmath>
#include <cstdint>
#include <initializer_list>
#include <type_traits>
#include <mtl/algorithm/bitmask.hpp>
#include <mtl/common/parameters.hpp>
#include <mtl/traits/types.hpp>


namespace mtl::math {
    namespace fp {
        enum class strategies {
            saturate = 0
        };

        template<strategies v_strategy>
        struct strategy {
            constexpr static strategies value = v_strategy;
        };
    }

    template<bool, uint8_t, uint8_t, class...>
    class fixed;

    namespace detail {
        template<class t_type, bool v_is_signed, uint8_t v_integral_bits, uint8_t v_fraction_bits>
        constexpr auto min() {
            using mask = typename std::conditional<
                v_is_signed,
                mtl::bitmask<
                    mtl::bmp::underlying_type<t_type>,
                    mtl::bmp::modify<mtl::bmp::operators::set_from<v_integral_bits + v_fraction_bits>>
                >,
                mtl::bitmask<mtl::bmp::underlying_type<t_type>>
            >::type;
            return mask::value;
        }

        template<class t_type, bool v_is_signed, uint8_t v_integral_bits, uint8_t v_fraction_bits>
        constexpr auto max() {
            return mtl::bitmask<
                mtl::bmp::underlying_type<t_type>,
                mtl::bmp::modify<mtl::bmp::operators::set_to<v_integral_bits + v_fraction_bits>>
            >::value;
        }
    }

    template<bool v_is_signed, uint8_t v_integral_bits, uint8_t v_fraction_bits, class... t_parameters>
    class fixed {
    public:
        // Configuration parameters.
        constexpr static bool is_signed = v_is_signed;
        constexpr static uint8_t integral_bits = v_integral_bits;
        constexpr static uint8_t fraction_bits = v_fraction_bits;
        
        using strategy = typename mtl::parameters<t_parameters...>::template find<
            mtl::math::fp::strategy,
            mtl::math::fp::strategy<mtl::math::fp::strategies::saturate>
        >::type;

        // Defining underlying type.
        using underlying_type = typename mtl::traits::types::pick<
            mtl::traits::typesp::min_integral<is_signed, integral_bits + fraction_bits + (is_signed?1:0)>
        >::type;
        using fraction_type = typename mtl::traits::types::pick<
            mtl::traits::typesp::min_floating<fraction_bits>
        >::type;
        // using fraction_type = typename std::conditional<
        //     (fraction_bits <= 23),
        //     float,
        //     typename std::conditional<
        //         (fraction_bits <= 52),
        //         double,
        //         long double
        //     >::type
        // >::type;

        fixed() = default;
    
    private:
        constexpr fixed(const std::initializer_list<underlying_type>& list) : m_value(*list.begin()) {}

    public:
        // Define min/max values.
        constexpr static fixed min = {detail::min<underlying_type, is_signed, integral_bits, fraction_bits>()};
        constexpr static fixed max = {detail::max<underlying_type, is_signed, integral_bits, fraction_bits>()};

        inline underlying_type integral() const noexcept {
            if constexpr (integral_bits == 0) {
                return 0;
            } else {
                return m_value >> fraction_bits;
            }
        }

        inline fraction_type floating() const noexcept {
            if constexpr (is_signed) {
                underlying_type value = m_value;
                if (m_value < 0) {
                    value |= mtl::bitmask<
                        mtl::bmp::underlying_type<underlying_type>,
                        mtl::bmp::modify<mtl::bmp::operators::set_from<fraction_bits>>
                    >::value;
                } else {
                    value &= mtl::bitmask<
                        mtl::bmp::underlying_type<underlying_type>,
                        mtl::bmp::modify<mtl::bmp::operators::set_to<fraction_bits>>
                    >::value;
                }
                return ldexp(static_cast<fraction_type>(value), -fraction_bits);
            } else {
                return ldexp(static_cast<fraction_type>(m_value & mtl::bitmask<
                    mtl::bmp::underlying_type<underlying_type>,
                    mtl::bmp::modify<mtl::bmp::operators::set_to<fraction_bits>>
                >::value), -fraction_bits);
            }
        }

    private:
        underlying_type m_value;
    };
}
