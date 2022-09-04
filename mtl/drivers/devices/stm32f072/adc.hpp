#pragma once

#include <type_traits>

#include <mtl/buffers/pp_buffer.hpp>
#include <mtl/common/parameters.hpp>
#include <mtl/drivers/common.hpp>
#include <mtl/drivers/dma.hpp>
#include <mtl/drivers/gpio.hpp>
#include <mtl/drivers/timer.hpp>
#include <mtl/hw/adc.hpp>
#include <mtl/os/event.hpp>
#include <mtl/traits/list.hpp>
#include <mtl/units/units.hpp>

namespace mtl::drivers {
    namespace adc_ {
        // Period.
        template <uint8_t v_value> struct period { constexpr static auto value = v_value; };

        // Resolution.
        template <uint8_t v_value> struct resolution { constexpr static auto value = v_value; };

        // Channels.
        template <class... t_ports> struct channels { using type = typename mtl::traits::list<t_ports...>; };

        // Timer id.
        template <class t_timer_id> struct timer_id { using type = t_timer_id; };

        // Channels.
        template <uint16_t v_value> struct samples { constexpr static auto value = v_value; };
    } // namespace adc_

    namespace detail {
        template <class... t_parameters> using map = mtl::traits::map<t_parameters...>;
        template <class... t_parameters> using pair = mtl::traits::pair<t_parameters...>;
        using adc_interrupts = map<pair<mtl::hw::ids::adc1, mtl::hw::interrupts::adc_comp>>;

        template <uint8_t v_value> using in = std::integral_constant<uint8_t, v_value>;
        using gpioa = mtl::hw::ids::gpioa;
        using gpiob = mtl::hw::ids::gpiob;
        using gpioc = mtl::hw::ids::gpioc;
        using gpiod = mtl::hw::ids::gpiod;
        using gpioe = mtl::hw::ids::gpioe;
        using adc_channels = map<pair<mtl::hw::io<gpioa, 0>, in<0>>, pair<mtl::hw::io<gpioa, 1>, in<1>>,
                                 pair<mtl::hw::io<gpioa, 2>, in<2>>, pair<mtl::hw::io<gpioa, 3>, in<3>>,
                                 pair<mtl::hw::io<gpioa, 4>, in<4>>, pair<mtl::hw::io<gpioa, 5>, in<5>>,
                                 pair<mtl::hw::io<gpioa, 6>, in<6>>, pair<mtl::hw::io<gpioa, 7>, in<7>>,
                                 pair<mtl::hw::io<gpiob, 0>, in<8>>, pair<mtl::hw::io<gpiob, 1>, in<9>>,
                                 pair<mtl::hw::io<gpioc, 0>, in<10>>, pair<mtl::hw::io<gpioc, 1>, in<11>>,
                                 pair<mtl::hw::io<gpioc, 2>, in<12>>, pair<mtl::hw::io<gpioc, 3>, in<13>>,
                                 pair<mtl::hw::io<gpioc, 4>, in<14>>, pair<mtl::hw::io<gpioc, 5>, in<15>>>;
    } // namespace detail

    template <class... t_parameters> class adc {
    public:
        using sys = typename mtl::parameters<t_parameters...>::find_type<mtl::sys>::type;
        using device_id = typename mtl::parameters<t_parameters...>::find_type<mtl::drivers::device_id>::type::type;
        using timer_id = typename mtl::parameters<t_parameters...>::find_type<mtl::drivers::adc_::timer_id>::type::type;
        using device_signal = typename mtl::hw::device_signal<device_id, void>;
        using channels = typename mtl::parameters<t_parameters...>::find_type<adc_::channels>::type;
        using interrupt = typename detail::adc_interrupts::find<device_id>::type;
        using registers = typename mtl::hw::adc<device_id>;

        template <class t_adc_channel> struct to_links { using type = mtl::hw::link<device_signal, t_adc_channel>; };
        using links = typename mtl::traits::apply<typename channels::type, to_links>::type;

        template <class t_adc_channel> struct to_ins {
            using type = typename detail::adc_channels::template find<t_adc_channel>::type::value;
        };
        using ins = typename mtl::traits::apply<typename channels::type, to_ins>::type;

        constexpr static auto resolution
            = mtl::parameters<t_parameters...>::template find<adc_::resolution>::type::value;
        constexpr static auto samples = mtl::parameters<t_parameters...>::template find<adc_::samples>::type::value;
        using element_type = typename std::conditional<resolution <= 8, uint8_t, uint16_t>::type;

        template <class t_initial, class t_value> struct select_channel {
            using type
                = std::integral_constant<typename t_initial::value_type, t_initial::value | (1 << t_value::value)>;
        };

        bool open() {
            // Setup GPIO.
            m_channels.open();

            // Setup DMA.

            m_dma.open();

            // Setup ADC.
            // Enable power.
            mtl::pwr::template enable<device_id>();
            registers::ier::write(0);

            registers::cfgr1::write(
                registers::cfgr1::dmaen::enabled, registers::cfgr1::dmacfg::circular, registers::cfgr1::scandir::upward,
                resolution_value<resolution>(), registers::cfgr1::align::right, trigger_value<timer_id>(),
                registers::cfgr1::exten::rising, registers::cfgr1::ovrmod::old, registers::cfgr1::cont::single,
                registers::cfgr1::wait::disabled, registers::cfgr1::autoff::disabled, registers::cfgr1::discen::enabled,
                registers::cfgr1::awden::disabled);

            registers::cfgr2::write(registers::cfgr2::ckmode::adcclk);
            registers::smpr::write(registers::smpr::smp::cycles_7_5);

            registers::chselr::write(
                mtl::traits::accumulate<ins, std::integral_constant<typename registers::chselr::type, 0>,
                                        select_channel>::type::value);

            registers::cr::aden::set(registers::cr::aden::enabled);

            // Setup timer.
            m_timer.open(100_Hz * samples);

            return true;
        }

        element_type *read() {
            auto area = m_buffer.dma_read_area();
            m_dma.transfer(area.data, area.size);
            m_buffer.switch_buffers();
            return area.data;
        }

    private:
        template <auto v_value> constexpr auto resolution_value() const {
            if constexpr (v_value == 6) {
                return registers::cfgr1::res::bits6;
            } else if constexpr (v_value == 8) {
                return registers::cfgr1::res::bits8;
            } else if constexpr (v_value == 10) {
                return registers::cfgr1::res::bitsdfr10;
            } else if constexpr (v_value == 12) {
                return registers::cfgr1::res::bits12;
            }
        }

        template <class t_timer> constexpr auto trigger_value() const {
            if constexpr (std::is_same<timer_id, mtl::hw::ids::timer1>::value) {
                return registers::cfgr1::extsel::trg0;
            } else if (std::is_same<timer_id, mtl::hw::ids::timer2>::value) {
                return registers::cfgr1::extsel::trg2;
            } else if (std::is_same<timer_id, mtl::hw::ids::timer3>::value) {
                return registers::cfgr1::extsel::trg3;
            } else if (std::is_same<timer_id, mtl::hw::ids::timer15>::value) {
                return registers::cfgr1::extsel::trg4;
            }
        }

    private:
        mtl::drivers::timer<sys, mtl::drivers::device_id<timer_id>> m_timer;
        mtl::drivers::gpios<sys, links> m_channels;
        mtl::drivers::dma<sys, device_signal> m_dma;
        mtl::buffers::pp_buffer<element_type, samples * channels::type::length> m_buffer;
    };
} // namespace mtl::drivers
