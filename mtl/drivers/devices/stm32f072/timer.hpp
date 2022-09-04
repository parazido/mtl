#pragma once

#include <cstdint>

#include <mtl/common/parameters.hpp>
#include <mtl/drivers/common.hpp>
#include <mtl/drivers/timer.hpp>
#include <mtl/hw/timer.hpp>
#include <mtl/os/api.hpp>
#include <mtl/os/isr.hpp>
#include <mtl/os/os.hpp>
#include <mtl/units/units.hpp>

//#include <mtl/sys/sys.hpp>

namespace mtl::drivers {
    namespace detail {
        // TODO: add signals.
        using timer_interrupts
            = mtl::traits::map<mtl::traits::pair<mtl::hw::ids::timer1, mtl::hw::interrupts::tim1_brk_up_trg_com>,
                               mtl::traits::pair<mtl::hw::ids::timer2, mtl::hw::interrupts::tim2>,
                               mtl::traits::pair<mtl::hw::ids::timer3, mtl::hw::interrupts::tim3>,
                               mtl::traits::pair<mtl::hw::ids::timer6, mtl::hw::interrupts::tim6_dac>,
                               mtl::traits::pair<mtl::hw::ids::timer7, mtl::hw::interrupts::tim7>,
                               mtl::traits::pair<mtl::hw::ids::timer14, mtl::hw::interrupts::tim14>,
                               mtl::traits::pair<mtl::hw::ids::timer15, mtl::hw::interrupts::tim15>,
                               mtl::traits::pair<mtl::hw::ids::timer16, mtl::hw::interrupts::tim16>,
                               mtl::traits::pair<mtl::hw::ids::timer17, mtl::hw::interrupts::tim17>>;
    } // namespace detail

    template <class... t_parameters> class timer {
    public:
        using sys = typename mtl::parameters<t_parameters...>::find_type<mtl::sys>::type;
        using device_id = typename mtl::parameters<t_parameters...>::find_type<mtl::drivers::device_id>::type::type;
        using interrupt = typename detail::timer_interrupts::template find<device_id>::type::value;
        using registers = mtl::hw::timer<device_id>;

        bool open(mtl::units::frequency frequency) {
            // Enable timer.
            mtl::pwr::template enable<device_id>();

            // Configure ports.
            registers::cr1::write(registers::cr1::arpe::enabled,
                                  registers::cr1::urs::any); //, registers::cr1::dir::down);
            registers::dier::write(registers::dier::uie::enabled);
            registers::cnt::write(2000);
            registers::psc::write(32000);
            registers::arr::write(2000);

            // Enable counter.
            registers::cr1::cen::set(registers::cr1::cen::enabled);

            // Set interrupt handler and enable interrupt.
            ::sys::interrupts::set_handler<interrupt>(&handler);
            ::sys::interrupts::enable<interrupt>();

            return true;
        }

        void wait() { mtl::api::wait(m_event); }

    private:
        static void handler() {
            if (registers::sr::uif::test(registers::sr::uif::active)) {
                registers::sr::uif::clear();
                mtl::isr::set(m_event);
            }
        }

        inline static mtl::event m_event;
    };
} // namespace mtl::drivers
