#pragma once

#include <type_traits>
#include <utility>

#include <mtl/common/parameters.hpp>
#include <mtl/containers/tuple.hpp>
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
            constexpr static auto function = v_function;
            constexpr static auto ppod = v_ppod;
            constexpr static auto pupd = v_pupd;
            constexpr static auto speed = v_speed;
        };

        template <class... t_parameters> using map = mtl::traits::map<t_parameters...>;
        template <class... t_parameters> using pair = mtl::traits::pair<t_parameters...>;
        namespace types = mtl::hw::types;
        namespace signal = mtl::hw::signal;
        using function = gpio_::function_;
        using ppod = gpio_::ppod_;
        using pupd = gpio_::pupd_;
        using speed = gpio_::speed_;

        using defaul_port_configuration = map<
            // Timer.
            pair<device_type_signal<types::timer, signal::bkin>,
                 port_configuration<function::user_in, ppod::push_pull, pupd::floating, speed::very_high>>,
            pair<device_type_signal<types::timer, signal::etr>,
                 port_configuration<function::user_in, ppod::push_pull, pupd::floating, speed::very_high>>,
            pair<device_type_signal<types::timer, signal::ch1_ic>,
                 port_configuration<function::user_in, ppod::push_pull, pupd::pull_down, speed::very_high>>,
            pair<device_type_signal<types::timer, signal::ch1_oc>,
                 port_configuration<function::device_control, ppod::push_pull, pupd::pull_down, speed::very_high>>,
            pair<device_type_signal<types::timer, signal::ch1n_oc>,
                 port_configuration<function::device_control, ppod::push_pull, pupd::pull_down, speed::very_high>>,
            pair<device_type_signal<types::timer, signal::ch2_ic>,
                 port_configuration<function::user_in, ppod::push_pull, pupd::pull_down, speed::very_high>>,
            pair<device_type_signal<types::timer, signal::ch2_oc>,
                 port_configuration<function::device_control, ppod::push_pull, pupd::pull_down, speed::very_high>>,
            pair<device_type_signal<types::timer, signal::ch2n_oc>,
                 port_configuration<function::device_control, ppod::push_pull, pupd::pull_down, speed::very_high>>,
            pair<device_type_signal<types::timer, signal::ch3_ic>,
                 port_configuration<function::user_in, ppod::push_pull, pupd::pull_down, speed::very_high>>,
            pair<device_type_signal<types::timer, signal::ch3_oc>,
                 port_configuration<function::device_control, ppod::push_pull, pupd::pull_down, speed::very_high>>,
            pair<device_type_signal<types::timer, signal::ch3n_oc>,
                 port_configuration<function::device_control, ppod::push_pull, pupd::pull_down, speed::very_high>>,
            pair<device_type_signal<types::timer, signal::ch4_ic>,
                 port_configuration<function::user_in, ppod::push_pull, pupd::pull_down, speed::very_high>>,
            pair<device_type_signal<types::timer, signal::ch4_oc>,
                 port_configuration<function::device_control, ppod::push_pull, pupd::pull_down, speed::very_high>>,
            // USART.
            pair<device_type_signal<types::usart, signal::rx>,
                 port_configuration<function::user_in, ppod::push_pull, pupd::pull_up, speed::very_high>>,
            pair<device_type_signal<types::usart, signal::tx>,
                 port_configuration<function::device_control, ppod::push_pull, pupd::floating, speed::very_high>>,
            pair<device_type_signal<types::usart, signal::ck>,
                 port_configuration<function::device_control, ppod::push_pull, pupd::floating, speed::very_high>>,
            pair<device_type_signal<types::usart, signal::rts>,
                 port_configuration<function::device_control, ppod::push_pull, pupd::floating, speed::very_high>>,
            pair<device_type_signal<types::usart, signal::cts>,
                 port_configuration<function::user_in, ppod::push_pull, pupd::pull_up, speed::very_high>>,
            // ADC.
            pair<device_type_signal<types::adc, void>, port_configuration<function::analog, ppod::push_pull, pupd::floating, speed::low>>>;
    } // namespace detail

    template <class... t_parameters> class gpio {
    public:
        using sys = typename mtl::parameters<t_parameters...>::template find_type<mtl::sys>::type;
        using link = typename mtl::parameters<t_parameters...>::template find_type<mtl::hw::link>::type;
        using device = typename link::io::port;
        using port_values = typename detail::defaul_port_configuration::find<
            detail::device_type_signal<device_type_by_id<typename link::device_signal::device>,
                                       typename link::device_signal::signal>>::type::value;
        // // using device_type = device_type_by_id<device_id>;
        // // using linked_device_id = typename link::device_signal::device;
        // // using linked_device_type = device_type_by_id<linked_device_id>;
        // // using linked_device_signal = typename link::device_signal::signal;
        // // using port_values = typename detail::defaul_port_configuration::find<
        // //     detail::device_type_signal<linked_device_type, linked_device_signal>>::type::value;
        constexpr static gpio_::function_ function = port_values::function;
        constexpr static gpio_::ppod_ ppod = port_values::ppod;
        constexpr static gpio_::pupd_ pupd = port_values::pupd;
        constexpr static gpio_::speed_ speed = port_values::speed;
        // constexpr static bool is_controlled_by_device = function == gpio_::function_::device_control;
        // constexpr static bool is_analog = function == gpio_::function_::analog;
        constexpr static uint8_t index = link::io::index;
        using registers = mtl::hw::gpio<device>;

        bool open() {
            // Enable port.
            sys::template enable<device>();

            // Configure ports.
            if constexpr (function == gpio_::function_::user_in) {
                // Configure mode.
                registers::moder::template moder<index>::set(registers::moder::template mode<index>::input);
                registers::moder::template moder<index>::set(registers::moder::template cnf_in<index>::floating);
            } else if (function == gpio_::function_::user_out) {
                static_assert("User output mode is not supported.");
            } else if (function == gpio_::function_::device_control) {
                // Configure mode.
                registers::moder::set(
                    static_cast<std::underlying_type<decltype(function)>::type>(function) << 2 * index);
                registers::ospeedr::set(
                    static_cast<std::underlying_type<decltype(speed)>::type>(speed) << 2 * index);
                registers::otyper::set(
                    static_cast<std::underlying_type<decltype(ppod)>::type>(ppod) << index);
                registers::pupdr::set(
                    static_cast<std::underlying_type<decltype(pupd)>::type>(pupd) << 2 * index);
            } else if (function == gpio_::function_::analog) {
                registers::moder::set(
                    static_cast<std::underlying_type<decltype(function)>::type>(function) << 2 * index);
            } else {
                static_assert("Unknown operation mode selected.");
            }

            return true;
        }

        bool test() const { return registers::idr::test(1 << index); }
    };

    template <class sys, class... t_links> class gpios {
    public:
        bool open() { return open_gpios(std::make_index_sequence<mtl::tuple<t_links...>::size>{}); }

    private:
        template <uint8_t v_index> bool open_gpio() { return mtl::get<v_index>(m_gpios).open(); }

        template <std::size_t... v_indexes> bool open_gpios(const std::index_sequence<v_indexes...> &) {
            return (open_gpio<v_indexes>() && ...);
        }

    private:
        mtl::tuple<gpio<sys, t_links>...> m_gpios{gpio<sys, t_links>()...};
    };

    template <class sys, template <class...> class t_container, class... t_links>
    class gpios<sys, t_container<t_links...>> : public gpios<sys, t_links...> {};
} // namespace mtl::drivers
