#pragma once

#include <mtl/buffers/ring_buffer.hpp>
#include <mtl/common/parameters.hpp>
#include <mtl/drivers/common.hpp>
#include <mtl/drivers/dma.hpp>
#include <mtl/hw/usart.hpp>

namespace mtl::drivers {
    namespace usart_ {
        // Duplex parameter.
        enum class duplex_ : uint8_t { half, full };
        template <duplex_ v_value> struct duplex { constexpr static auto value = v_value; };

        // Active lines.
        enum class lines_ : uint8_t { rx, tx, both };
        template <lines_ v_value> struct lines { constexpr static auto value = v_value; };

        // Tx/Rx lines.
        template <class t_port> struct tx { using type = t_port; };
        template <class t_port> struct rx { using type = t_port; };
    } // namespace usart_

    namespace detail {
        template <auto, class...> class usart_holder;

        template <class... t_parameters> class usart_holder<usart_::lines_::tx, t_parameters...> {
        public:
            using sys = typename mtl::parameters<t_parameters...>::find_type<mtl::sys>::type;
            using device_id = typename mtl::parameters<t_parameters...>::find_type<mtl::drivers::device_id>::type::type;
            using tx = typename mtl::parameters<t_parameters...>::find_type<usart_::tx>::type::type;
            using tx_link = mtl::hw::link<device_signal<device_id, mtl::hw::signal::tx>, tx>;

        public:
            // bool open() {
            //     m_tx_dma.open();
            //     m_tx_gpio.open();
            //     return true;
            // }

            auto write(void *buffer, size_t buffer_size) { return m_dma.transfer(buffer, buffer_size); }

        public:
             mtl::drivers::gpio<sys, tx_link> m_gpio;
             mtl::drivers::dma<sys, mtl::hw::device_signal<device_id, mtl::hw::signal::tx>> m_dma;
        };

        template <class... t_parameters> class usart_holder<usart_::lines_::rx, t_parameters...> {
        public:
            // using sys = typename mtl::parameters<t_parameters...>::find_type<mtl::sys>::type;
            // using device_id = typename mtl::parameters<t_parameters...>::find_type<mtl::drivers::device_id>::type::type;
            // using rx = typename mtl::parameters<t_parameters...>::find_type<usart_::rx>::type::type;
            // using rx_link = mtl::hw::link<device_signal<device_id, mtl::hw::signal::rx>, rx>;

        public:
            // bool open() {
            //     m_dma.open();
            //     m_gpio.open();
            //     return true;
            // }

            // auto read(void *buffer, size_t buffer_size) {
            //     return m_buffer.read(static_cast<uint8_t *>(buffer), buffer_size);
            // }

        public:
            // mtl::drivers::gpio<sys, rx_link> m_gpio;
            // mtl::drivers::dma<sys, mtl::hw::device_signal<device_id, mtl::hw::signal::rx>> m_dma;
            // mtl::buffers::ring_buffer<uint8_t, 32> m_buffer;
            // // inline static mtl::event m_event;
        };

        template <class... t_parameters>
        class usart_holder<usart_::lines_::both, t_parameters...> :
            public usart_holder<usart_::lines_::rx, t_parameters...>,
            public usart_holder<usart_::lines_::tx, t_parameters...> {};
    } // namespace detail

    template <class... t_parameters>
    class usart : public detail::usart_holder<usart_::lines_::tx, t_parameters...> {
        // public detail::usart_holder<
        //     mtl::parameters<t_parameters...>::template find<usart_::lines, usart_::lines_::both>::type::value,
        //     t_parameters...> {
    public:
        using sys = typename mtl::parameters<t_parameters...>::find_type<mtl::sys>::type;
        using device_id = typename mtl::parameters<t_parameters...>::find_type<mtl::drivers::device_id>::type::type;
        // using tx = typename mtl::parameters<t_parameters...>::find_type<usart_::tx>::type::type;
        // using rx = typename mtl::parameters<t_parameters...>::find_type<usart_::rx>::type::type;
        constexpr static auto duplex
            = mtl::parameters<t_parameters...>::template find<usart_::duplex, usart_::duplex_::full>::type::value;
        constexpr static auto active_lines
            = mtl::parameters<t_parameters...>::template find<usart_::lines, usart_::lines_::both>::type::value;
        constexpr static bool tx_enabled = active_lines == usart_::lines_::tx || active_lines == usart_::lines_::both;
        constexpr static bool rx_enabled = active_lines == usart_::lines_::rx || active_lines == usart_::lines_::both;
        using registers = mtl::hw::usart<device_id>;

        bool open(int baud_rate) {
            // Open auxiliary devices.
            if constexpr (rx_enabled) {
            }

            if constexpr (tx_enabled) {
            }

            // Initialize USART device.
            // Enable port.
            sys::pwr::template enable<device_id>();
            // Configure USART.
            // registers::brr::write(0x22c);
            registers::brr::write_value(0x116);
            registers::cr2::write(usart1::cr2::stop::bits1);
            if constexpr (tx_enabled) {
                registers::cr3::dmat::write(usart1::cr3::dmat::enabled);
                registers::cr1::te::write(registers::cr1::te::enabled);
            }
            if constexpr (rx_enabled) {
                registers::cr3::dmar::write(usart1::cr3::dmar::enabled);
                registers::cr1::re::write(registers::cr1::re::enabled);
            }
            registers::cr1::ue::write(registers::cr1::ue::enabled);

            return true;
        }
    };
} // namespace mtl::drivers
