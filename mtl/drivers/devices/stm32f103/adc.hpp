#pragma once

#include <mtl/common/parameters.hpp>
#include <mtl/drivers/common.hpp>
#include <mtl/drivers/timer.hpp>

namespace mtl::drivers {
    namespace adc_ {
        template<uint32_t v_value> struct frequency {
            constexpr static uint32_t value = v_value;
        };

        template <class t_phase_a, class t_phase_b, class t_phase_c> struct channel {
            using phase_a = t_phase_a;
            using phase_b = t_phase_b;
            using phase_c = t_phase_c;
        };
    } // namespace hall_

    template <class... t_parameters> class adc {
    public:
        using sys = typename mtl::parameters<t_parameters...>::find_type<mtl::sys>::type;
        using device_id = typename mtl::parameters<t_parameters...>::find_type<mtl::drivers::device_id>::type::type;
        using device = mtl::hw::timer<device_id>;
        using io = typename mtl::parameters<t_parameters...>::find_type<hall_::io>::type;

        bool open() {}
    };
} // namespace mtl::drivers
