#pragma once

#include <cstdint>

#include <mtl/hw/descriptor.hpp>
#include <mtl/hw/rcc.hpp>
#include <mtl/traits/map.hpp>

namespace mtl::pwr {
    namespace detail {
        template <class t_bus, uint8_t v_index> struct bus_line {
            using bus = t_bus;
            constexpr static uint8_t index = v_index;
        };

        using pwr = mtl::traits::map<
            // AHB.
            mtl::traits::pair<mtl::hw::ids::dma1, bus_line<mtl::hw::bus::ahb, 0>>,
            mtl::traits::pair<mtl::hw::ids::dma2, bus_line<mtl::hw::bus::ahb, 1>>,
            mtl::traits::pair<mtl::hw::ids::sram, bus_line<mtl::hw::bus::ahb, 2>>,
            mtl::traits::pair<mtl::hw::ids::flitf, bus_line<mtl::hw::bus::ahb, 4>>,
            mtl::traits::pair<mtl::hw::ids::crc, bus_line<mtl::hw::bus::ahb, 6>>,
            mtl::traits::pair<mtl::hw::ids::gpioa, bus_line<mtl::hw::bus::ahb, 17>>,
            mtl::traits::pair<mtl::hw::ids::gpiob, bus_line<mtl::hw::bus::ahb, 18>>,
            mtl::traits::pair<mtl::hw::ids::gpioc, bus_line<mtl::hw::bus::ahb, 19>>,
            mtl::traits::pair<mtl::hw::ids::gpiod, bus_line<mtl::hw::bus::ahb, 20>>,
            mtl::traits::pair<mtl::hw::ids::gpioe, bus_line<mtl::hw::bus::ahb, 21>>,
            mtl::traits::pair<mtl::hw::ids::gpiof, bus_line<mtl::hw::bus::ahb, 22>>,
            mtl::traits::pair<mtl::hw::ids::tsc, bus_line<mtl::hw::bus::ahb, 24>>,
            // APB1.
            mtl::traits::pair<mtl::hw::ids::timer2, bus_line<mtl::hw::bus::apb1, 0>>,
            mtl::traits::pair<mtl::hw::ids::timer3, bus_line<mtl::hw::bus::apb1, 1>>,
            mtl::traits::pair<mtl::hw::ids::timer6, bus_line<mtl::hw::bus::apb1, 4>>,
            mtl::traits::pair<mtl::hw::ids::timer7, bus_line<mtl::hw::bus::apb1, 5>>,
            mtl::traits::pair<mtl::hw::ids::timer14, bus_line<mtl::hw::bus::apb1, 8>>,
            mtl::traits::pair<mtl::hw::ids::wwdg, bus_line<mtl::hw::bus::apb1, 11>>,
            mtl::traits::pair<mtl::hw::ids::spi2, bus_line<mtl::hw::bus::apb1, 14>>,
            mtl::traits::pair<mtl::hw::ids::usart2, bus_line<mtl::hw::bus::apb1, 17>>,
            mtl::traits::pair<mtl::hw::ids::usart3, bus_line<mtl::hw::bus::apb1, 18>>,
            mtl::traits::pair<mtl::hw::ids::usart4, bus_line<mtl::hw::bus::apb1, 19>>,
            mtl::traits::pair<mtl::hw::ids::usart5, bus_line<mtl::hw::bus::apb1, 20>>,
            mtl::traits::pair<mtl::hw::ids::i2c1, bus_line<mtl::hw::bus::apb1, 21>>,
            mtl::traits::pair<mtl::hw::ids::i2c2, bus_line<mtl::hw::bus::apb1, 22>>,
            mtl::traits::pair<mtl::hw::ids::usb, bus_line<mtl::hw::bus::apb1, 23>>,
            mtl::traits::pair<mtl::hw::ids::can, bus_line<mtl::hw::bus::apb1, 25>>,
            mtl::traits::pair<mtl::hw::ids::crs, bus_line<mtl::hw::bus::apb1, 27>>,
            mtl::traits::pair<mtl::hw::ids::pwr, bus_line<mtl::hw::bus::apb1, 28>>,
            mtl::traits::pair<mtl::hw::ids::dac, bus_line<mtl::hw::bus::apb1, 29>>,
            mtl::traits::pair<mtl::hw::ids::cec, bus_line<mtl::hw::bus::apb1, 30>>,
            // APB2.
            mtl::traits::pair<mtl::hw::ids::comp1, bus_line<mtl::hw::bus::apb2, 0>>,
            mtl::traits::pair<mtl::hw::ids::usart6, bus_line<mtl::hw::bus::apb2, 5>>,
            mtl::traits::pair<mtl::hw::ids::usart7, bus_line<mtl::hw::bus::apb2, 6>>,
            mtl::traits::pair<mtl::hw::ids::usart8, bus_line<mtl::hw::bus::apb2, 7>>,
            mtl::traits::pair<mtl::hw::ids::adc1, bus_line<mtl::hw::bus::apb2, 9>>,
            mtl::traits::pair<mtl::hw::ids::timer1, bus_line<mtl::hw::bus::apb2, 11>>,
            mtl::traits::pair<mtl::hw::ids::spi1, bus_line<mtl::hw::bus::apb2, 12>>,
            mtl::traits::pair<mtl::hw::ids::usart1, bus_line<mtl::hw::bus::apb2, 14>>,
            mtl::traits::pair<mtl::hw::ids::timer15, bus_line<mtl::hw::bus::apb2, 16>>,
            mtl::traits::pair<mtl::hw::ids::timer16, bus_line<mtl::hw::bus::apb2, 17>>,
            mtl::traits::pair<mtl::hw::ids::timer17, bus_line<mtl::hw::bus::apb2, 18>>,
            mtl::traits::pair<mtl::hw::ids::dbg1, bus_line<mtl::hw::bus::apb2, 22>>>;

        template <class t_enable_register, class t_reset_register> struct registers {
            using enable_register = t_enable_register;
            using reset_register = t_reset_register;
        };

        using pwr_registers = mtl::traits::map<
            mtl::traits::pair<mtl::hw::bus::ahb, registers<mtl::hw::rcc::ahbenr, void>>,
            mtl::traits::pair<mtl::hw::bus::apb1, registers<mtl::hw::rcc::apb1enr, mtl::hw::rcc::apb1rstr>>,
            mtl::traits::pair<mtl::hw::bus::apb2, registers<mtl::hw::rcc::apb2enr, mtl::hw::rcc::apb2rstr>>>;
    } // namespace detail

    template <class t_device_id>[[gnu::always_inline]] inline void enable() noexcept {
        using line = typename detail::pwr::find<t_device_id>::type::value;
        using registers_ = typename detail::pwr_registers::find<typename line::bus>::type::value;
        registers_::enable_register::set(1 << line::index);
    }
} // namespace mtl::pwr
