#pragma once

#include <type_traits>

#include <mtl/common/parameters.hpp>
#include <mtl/hw/descriptor.hpp>
#include <mtl/hw/devices.hpp>
#include <mtl/hw/gpio.hpp>
#include <mtl/sys/sys.hpp>
#include <mtl/traits/map.hpp>


namespace mtl::drivers {
    using namespace mtl::hw;

    namespace gpio_ {
        // Speed.
        enum class speed_ : uint8_t { low = 0, medium = 1, high = 2, very_high = 3 };
        template <speed_ v_speed> struct speed { constexpr static speed_ value = v_speed; };

        // Push-pull/open-drain.
        enum class ppod_ : uint8_t { push_pull = 0, open_drain = 1 };
        template <ppod_ v_ppod> struct ppod { constexpr static ppod_ value = v_ppod; };

        // Pull-up/pull-down.
        enum class pupd_ : uint8_t { floating = 0, pull_up = 1, pull_down = 2 };
        template <pupd_ v_pupd> struct pupd { constexpr static pupd_ value = v_pupd; };

        // Function.
        enum class function_ : uint8_t { user_in = 0, user_out = 1, device_control = 2, analog = 3 };
        template <function_ v_function> struct function { constexpr static function_ value = v_function; };
    } // namespace gpio_

    namespace detail {
        template <class...> struct alternate_t;

        template <class t_device_signal, class t_io> struct alternate_t<t_device_signal, t_io> {
            using device_signal = t_device_signal;
            using port = typename t_io::port;
            constexpr static uint8_t index = t_io::index;
        };

        template <class t_device_type, class t_signal> struct device_type_signal {
            using device_type = t_device_type;
            using signal = t_signal;
        };

        template <gpio_::function_ v_function, gpio_::ppod_ v_ppod, gpio_::pupd_ v_pupd, gpio_::speed_ v_speed>
        struct port_configuration {
            constexpr static gpio_::function_ function = v_function;
            constexpr static gpio_::ppod_ ppod = v_ppod;
            constexpr static gpio_::pupd_ pupd = v_pupd;
            constexpr static gpio_::speed_ speed = v_speed;
        };

        using defaul_port_configuration = mtl::traits::map<
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::bkin>,
                              port_configuration<gpio_::function_::user_in, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::floating, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::etr>,
                              port_configuration<gpio_::function_::user_in, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::floating, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::ch1_ic>,
                              port_configuration<gpio_::function_::user_in, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_down, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::ch1_oc>,
                              port_configuration<gpio_::function_::device_control, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_down, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::ch1n_oc>,
                              port_configuration<gpio_::function_::device_control, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_down, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::ch2_ic>,
                              port_configuration<gpio_::function_::user_in, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_down, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::ch2_oc>,
                              port_configuration<gpio_::function_::device_control, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_down, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::ch2n_oc>,
                              port_configuration<gpio_::function_::device_control, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_down, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::ch3_ic>,
                              port_configuration<gpio_::function_::user_in, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_down, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::ch3_oc>,
                              port_configuration<gpio_::function_::device_control, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_down, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::ch3n_oc>,
                              port_configuration<gpio_::function_::device_control, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_down, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::ch4_ic>,
                              port_configuration<gpio_::function_::user_in, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_down, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::timer, mtl::hw::signal::ch4_oc>,
                              port_configuration<gpio_::function_::device_control, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_down, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::usart, mtl::hw::signal::rx>,
                              port_configuration<gpio_::function_::user_in, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_up, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::usart, mtl::hw::signal::tx>,
                              port_configuration<gpio_::function_::device_control, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::floating, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::usart, mtl::hw::signal::ck>,
                              port_configuration<gpio_::function_::device_control, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::floating, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::usart, mtl::hw::signal::rts>,
                              port_configuration<gpio_::function_::device_control, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::floating, gpio_::speed_::very_high>>,
            mtl::traits::pair<device_type_signal<mtl::hw::types::usart, mtl::hw::signal::cts>,
                              port_configuration<gpio_::function_::user_in, gpio_::ppod_::push_pull,
                                                 gpio_::pupd_::pull_up, gpio_::speed_::very_high>>>;
    } // namespace detail

    template <class... t_parameters> class gpio {
    public:
        using sys = typename mtl::parameters<t_parameters...>::template find_type<mtl::sys>::type;
        using link = typename mtl::parameters<t_parameters...>::template find_type<mtl::hw::link>::type;
        using device = typename link::io::port;
        // using speed = mcu::drivers::parameters::find_speed_t<t_parameters...>;
        // using pupd = mcu::drivers::parameters::find_pupd_t<t_parameters...>;
        // using ppod = mcu::drivers::parameters::find_ppod_t<t_parameters...>;
        // constexpr static bool is_pull_up = std::is_same<pupd, parameters::pull_up>::value;
        // constexpr static bool is_open_drain = std::is_same<ppod, parameters::open_drain>::value;
        // constexpr static bool is_controlled_by_user = std::is_same<function, parameters::user_in>::value ||
        // std::is_same<function, parameters::user_out>::value;
        using port_values = typename detail::defaul_port_configuration::find<
            detail::device_type_signal<device_type_by_id<typename link::device_signal::device>,
                                       typename link::device_signal::signal>>::type::value;
        constexpr static gpio_::function_ function = port_values::function;
        constexpr static gpio_::ppod_ ppod = port_values::ppod;
        constexpr static bool is_controlled_by_device = function == gpio_::function_::device_control;
        constexpr static bool is_analog = function == gpio_::function_::analog;
        constexpr static uint8_t index = link::io::index;

        bool open() {
            // Enable port.
            sys::template enable<device>();

            // Configure ports.
            using registers = mtl::hw::gpio<device>;
            if constexpr (function == gpio_::function_::user_in) {
                // Configure mode.
                if constexpr (index < 8) {
                    registers::crl::template mode<index>::set(registers::crl::template mode<index>::input);
                    registers::crl::template cnf_in<index>::set(registers::crl::template cnf_in<index>::floating);
                } else {
                    registers::crh::template mode<index - 8>::set(registers::crh::template mode<index>::input);
                    registers::crh::template cnf_in<index - 8>::set(registers::crh::template cnf_in<index>::floating);
                }
            } else if (function == gpio_::function_::user_out) {
                static_assert("User output mode is not supported.");
            } else if (function == gpio_::function_::device_control) {
                // Configure mode.
                if constexpr (index < 8) {
                    registers::crl::template mode<index>::set(registers::crl::template mode<index>::output_50mhz);
                    if constexpr (ppod == gpio_::ppod_::push_pull) {
                        registers::crl::template cnf_out<index>::set(registers::crl::template cnf_out<index>::alternate_pp);
                    } else {
                        registers::crl::template cnf_out<index>::set(registers::crl::template cnf_out<index>::alternate_od);
                    }
                } else {
                    registers::crh::template mode<index - 8>::set(registers::crh::template mode<index - 8>::output_50mhz);
                    if constexpr (ppod == gpio_::ppod_::push_pull) {
                        registers::crh::template cnf_out<index - 8>::set(registers::crh::template cnf_out<index - 8>::alternate_pp);
                    } else {
                        registers::crh::template cnf_out<index - 8>::set(registers::crh::template cnf_out<index - 8>::alternate_od);
                    }
                }
            //} else if (function == gpio_::function_::analog) {
            //    registers::moder::set(static_cast<std::underlying_type<gpio_::function_>::type>(function) << 2 * index);
            } else {
                static_assert("Unknown operation mode selected.");
            }

            return true;
        }

        bool test() const {
            using registers = mtl::hw::gpio<device>;
            return registers::idr::test(1 << index);
        }
    };
} // namespace mtl::drivers
