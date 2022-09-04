#pragma once

#include <mtl/common/parameters.hpp>
#include <mtl/drivers/dma.hpp>
#include <mtl/drivers/gpio.hpp>
#include <mtl/hw/usart.hpp>

namespace drivers {
    using namespace ::devices;

    template <class... t_parameters> class usart {
    public:
        using device = typename drivers::parameters::find_device_t<t_parameters...>::type;
        using duplex = drivers::parameters::find_duplex_t<t_parameters...>;
        // using rx_buffer = mcu::drivers::parameters::find_receive_buffer_t<t_parameters...>;
        // using tx_buffer = mcu::drivers::parameters::find_transmit_buffer_t<t_parameters...>;
        // using rx_io = mcu::drivers::parameters::find_link_t<devices::signals::rx, t_parameters...>;
        using tx_io = typename drivers::parameters::find_tx_port_t<t_parameters...>::type;
        using registers = ::devices::usart<device>;

        bool open(int baud_rate) {
            // Open auxiliary devices.
            // m_rx_gpio.open();
            m_tx_gpio.open();
            // m_rx_dma.open();
            m_tx_dma.open();

            // Initialize USART device.
            // Enable port.
            ::devices::manager::enable<device>();
            // Configure USART.
            registers::brr::write_value(0x22c);
            registers::cr3::write(registers::cr3::dmar::enabled, registers::cr3::dmat::enabled);
            registers::cr1::write(registers::cr1::ue::enabled, registers::cr1::te::enabled);

            return true;
        }

        auto read(void *buffer, size_t buffer_size) {
            // m_rx_event.wait();
            // return m_rx_buffer.read(buffer, buffer_size);
        }

        auto write(void *buffer, size_t buffer_size) { m_tx_dma.transfer(buffer, buffer_size); }

    private:
        // gpio<device, signals::rx, rx_io> m_rx_gpio;
        gpio<link<typename tx_io::io, device_signal<device, signals::tx>>,
             parameters::function<parameters::device_control>>
            m_tx_gpio;
        // dma<device, signals::rx> m_rx_dma;
        ::drivers::dma<::devices::device_signal<device, signals::tx>> m_tx_dma;
        // rx_buffer m_rx_buffer;
    };
} // namespace drivers
