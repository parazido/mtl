#pragma once

#include <cstdint>

#include <mtl/common/parameters.hpp>
#include <mtl/drivers/common.hpp>
#include <mtl/hw/descriptor.hpp>
#include <mtl/hw/nvic.hpp>
#include <mtl/hw/timer.hpp>
#include <mtl/os/api.hpp>
#include <mtl/os/isr.hpp>
#include <mtl/sys/sys.hpp>


namespace mtl::drivers {
    namespace detail {
        template <class...> struct timer_interrupt_map;

        template <class t_device, class t_interrupt> struct timer_interrupt_map<t_device, t_interrupt> {
            using device = t_device;
            using interrupt = t_interrupt;
        };

        template <>
        struct timer_interrupt_map<mtl::hw::ids::timer2> :
            timer_interrupt_map<mtl::hw::ids::timer2, mtl::hw::interrupts::tim2> {};
        template <>
        struct timer_interrupt_map<mtl::hw::ids::timer3> :
            timer_interrupt_map<mtl::hw::ids::timer3, mtl::hw::interrupts::tim3> {};
        template <>
        struct timer_interrupt_map<mtl::hw::ids::timer4> :
            timer_interrupt_map<mtl::hw::ids::timer4, mtl::hw::interrupts::tim4> {};
        template <>
        struct timer_interrupt_map<mtl::hw::ids::timer5> :
            timer_interrupt_map<mtl::hw::ids::timer5, mtl::hw::interrupts::tim5> {};
    } // namespace detail

    template <class... t_parameters> class timer {
    public:
        using sys = typename mtl::parameters<t_parameters...>::find_type<mtl::sys>::type;
        using device_id = typename mtl::parameters<t_parameters...>::find_type<mtl::drivers::device_id>::type::type;
        using interrupt = typename detail::timer_interrupt_map<device_id>::interrupt;

        bool open(int period) {
            // Enable timer.
            sys::template enable<device_id>();

            // Configure ports.
            using registers = mtl::hw::timer<device_id>;
            registers::cr1::write(registers::cr1::arpe::enabled, registers::cr1::urs::enabled, registers::cr1::dir::up);
            registers::dier::write(registers::dier::uie::enabled);
            registers::cnt::write(0);
            registers::psc::write(32000);
            registers::arr::write(10000);

            // Enable counter.
            registers::cr1::cen::set(registers::cr1::cen::enabled);

            // Set interrupt handler and enable interrupt.
            sys::interrupts::template set_handler<interrupt>(&handler);
            sys::interrupts::template enable<interrupt>();

            return true;
        }

        void wait() { mtl::api::wait(m_event); }

    private:
        static void handler() {
            using registers = mtl::hw::timer<device_id>;
            if (registers::sr::uif::test(registers::sr::uif::set)) {
                registers::sr::uif::clear();
                mtl::isr::set(m_event);
            }
        }

        inline static mtl::event m_event;
    };
} // namespace mtl::drivers
