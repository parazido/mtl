#pragma once

#include <cstdint>

#include <mtl/common/parameters.hpp>
#include <mtl/hw/dma.hpp>
#include <mtl/os/api.hpp>
#include <mtl/os/event.hpp>
#include <mtl/os/isr.hpp>
#include <mtl/sys/sys.hpp>

namespace drivers {
    namespace detail {
        template <class t_device, class t_signal, class t_dma, uint8_t v_index> struct dma_channels_mapping_t {
            using device = t_device;
            using signal = t_signal;
            using dma = t_dma;
            constexpr static uint8_t index = v_index;
        };

        template <class t_device, class t_signal = void> struct dma_channels_mapping;

        template <>
        struct dma_channels_mapping<devices::ids::adc1> :
            dma_channels_mapping_t<devices::ids::adc1, void, devices::ids::dma1, 0> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer2, devices::signals::channel3> :
            dma_channels_mapping_t<devices::ids::timer2, devices::signals::channel3, devices::ids::dma1, 0> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer4, devices::signals::channel1> :
            dma_channels_mapping_t<devices::ids::timer4, devices::signals::channel1, devices::ids::dma1, 0> {};
        template <>
        struct dma_channels_mapping<devices::ids::spi1, devices::signals::rx> :
            dma_channels_mapping_t<devices::ids::spi1, devices::signals::rx, devices::ids::dma1, 1> {};
        template <>
        struct dma_channels_mapping<devices::ids::usart3, devices::signals::tx> :
            dma_channels_mapping_t<devices::ids::usart3, devices::signals::tx, devices::ids::dma1, 1> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer2, devices::signals::up> :
            dma_channels_mapping_t<devices::ids::timer2, devices::signals::up, devices::ids::dma1, 1> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer3, devices::signals::channel3> :
            dma_channels_mapping_t<devices::ids::timer3, devices::signals::channel3, devices::ids::dma1, 1> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer6, devices::signals::up> :
            dma_channels_mapping_t<devices::ids::timer6, devices::signals::up, devices::ids::dma1, 1> {};
        template <>
        struct dma_channels_mapping<devices::ids::dac, devices::signals::channel1> :
            dma_channels_mapping_t<devices::ids::dac, devices::signals::channel1, devices::ids::dma1, 1> {};
        template <>
        struct dma_channels_mapping<devices::ids::spi1, devices::signals::tx> :
            dma_channels_mapping_t<devices::ids::spi1, devices::signals::tx, devices::ids::dma1, 2> {};
        template <>
        struct dma_channels_mapping<devices::ids::usart3, devices::signals::rx> :
            dma_channels_mapping_t<devices::ids::usart3, devices::signals::rx, devices::ids::dma1, 2> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer3, devices::signals::channel4> :
            dma_channels_mapping_t<devices::ids::timer3, devices::signals::channel4, devices::ids::dma1, 2> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer3, devices::signals::up> :
            dma_channels_mapping_t<devices::ids::timer3, devices::signals::up, devices::ids::dma1, 2> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer7, devices::signals::up> :
            dma_channels_mapping_t<devices::ids::timer7, devices::signals::up, devices::ids::dma1, 2> {};
        template <>
        struct dma_channels_mapping<devices::ids::dac, devices::signals::channel2> :
            dma_channels_mapping_t<devices::ids::dac, devices::signals::channel2, devices::ids::dma1, 2> {};
        template <>
        struct dma_channels_mapping<devices::ids::spi2, devices::signals::rx> :
            dma_channels_mapping_t<devices::ids::spi2, devices::signals::rx, devices::ids::dma1, 3> {};
        template <>
        struct dma_channels_mapping<devices::ids::usart1, devices::signals::tx> :
            dma_channels_mapping_t<devices::ids::usart1, devices::signals::tx, devices::ids::dma1, 3> {};
        template <>
        struct dma_channels_mapping<devices::ids::i2c2, devices::signals::tx> :
            dma_channels_mapping_t<devices::ids::i2c2, devices::signals::tx, devices::ids::dma1, 3> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer2, devices::signals::channel4> :
            dma_channels_mapping_t<devices::ids::timer2, devices::signals::channel4, devices::ids::dma1, 3> {};
        template <>
        struct dma_channels_mapping<devices::ids::spi2, devices::signals::tx> :
            dma_channels_mapping_t<devices::ids::spi2, devices::signals::tx, devices::ids::dma1, 4> {};
        template <>
        struct dma_channels_mapping<devices::ids::usart1, devices::signals::rx> :
            dma_channels_mapping_t<devices::ids::usart1, devices::signals::rx, devices::ids::dma1, 4> {};
        template <>
        struct dma_channels_mapping<devices::ids::i2c2, devices::signals::rx> :
            dma_channels_mapping_t<devices::ids::i2c2, devices::signals::rx, devices::ids::dma1, 4> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer2, devices::signals::channel1> :
            dma_channels_mapping_t<devices::ids::timer2, devices::signals::channel1, devices::ids::dma1, 4> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer4, devices::signals::channel3> :
            dma_channels_mapping_t<devices::ids::timer4, devices::signals::channel3, devices::ids::dma1, 4> {};
        template <>
        struct dma_channels_mapping<devices::ids::usart2, devices::signals::rx> :
            dma_channels_mapping_t<devices::ids::usart2, devices::signals::rx, devices::ids::dma1, 5> {};
        template <>
        struct dma_channels_mapping<devices::ids::i2c1, devices::signals::tx> :
            dma_channels_mapping_t<devices::ids::i2c1, devices::signals::tx, devices::ids::dma1, 5> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer3, devices::signals::channel1> :
            dma_channels_mapping_t<devices::ids::timer3, devices::signals::channel1, devices::ids::dma1, 5> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer3, devices::signals::trig> :
            dma_channels_mapping_t<devices::ids::timer3, devices::signals::trig, devices::ids::dma1, 5> {};
        template <>
        struct dma_channels_mapping<devices::ids::usart2, devices::signals::tx> :
            dma_channels_mapping_t<devices::ids::usart2, devices::signals::tx, devices::ids::dma1, 6> {};
        template <>
        struct dma_channels_mapping<devices::ids::i2c1, devices::signals::rx> :
            dma_channels_mapping_t<devices::ids::i2c1, devices::signals::rx, devices::ids::dma1, 6> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer2, devices::signals::channel2> :
            dma_channels_mapping_t<devices::ids::timer2, devices::signals::channel2, devices::ids::dma1, 6> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer4, devices::signals::up> :
            dma_channels_mapping_t<devices::ids::timer4, devices::signals::up, devices::ids::dma1, 6> {};
        template <>
        struct dma_channels_mapping<devices::ids::spi3, devices::signals::rx> :
            dma_channels_mapping_t<devices::ids::spi3, devices::signals::rx, devices::ids::dma2, 0> {};
        template <>
        struct dma_channels_mapping<devices::ids::uart5, devices::signals::tx> :
            dma_channels_mapping_t<devices::ids::uart5, devices::signals::tx, devices::ids::dma2, 0> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer5, devices::signals::channel4> :
            dma_channels_mapping_t<devices::ids::timer5, devices::signals::channel4, devices::ids::dma2, 0> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer5, devices::signals::trig> :
            dma_channels_mapping_t<devices::ids::timer5, devices::signals::trig, devices::ids::dma2, 0> {};
        template <>
        struct dma_channels_mapping<devices::ids::spi3, devices::signals::tx> :
            dma_channels_mapping_t<devices::ids::spi3, devices::signals::tx, devices::ids::dma2, 1> {};
        template <>
        struct dma_channels_mapping<devices::ids::uart5, devices::signals::rx> :
            dma_channels_mapping_t<devices::ids::uart5, devices::signals::rx, devices::ids::dma2, 1> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer5, devices::signals::channel3> :
            dma_channels_mapping_t<devices::ids::timer5, devices::signals::channel3, devices::ids::dma2, 1> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer5, devices::signals::up> :
            dma_channels_mapping_t<devices::ids::timer5, devices::signals::up, devices::ids::dma2, 1> {};
        template <>
        struct dma_channels_mapping<devices::ids::uart4, devices::signals::rx> :
            dma_channels_mapping_t<devices::ids::uart4, devices::signals::rx, devices::ids::dma2, 2> {};
        template <>
        struct dma_channels_mapping<devices::ids::aes, devices::signals::out> :
            dma_channels_mapping_t<devices::ids::aes, devices::signals::out, devices::ids::dma2, 2> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer5, devices::signals::channel2> :
            dma_channels_mapping_t<devices::ids::timer5, devices::signals::channel2, devices::ids::dma2, 3> {};
        template <>
        struct dma_channels_mapping<devices::ids::sd> :
            dma_channels_mapping_t<devices::ids::sd, void, devices::ids::dma2, 3> {};
        template <>
        struct dma_channels_mapping<devices::ids::mmc> :
            dma_channels_mapping_t<devices::ids::mmc, void, devices::ids::dma2, 3> {};
        template <>
        struct dma_channels_mapping<devices::ids::uart4, devices::signals::tx> :
            dma_channels_mapping_t<devices::ids::uart4, devices::signals::tx, devices::ids::dma2, 4> {};
        template <>
        struct dma_channels_mapping<devices::ids::timer5, devices::signals::channel1> :
            dma_channels_mapping_t<devices::ids::timer5, devices::signals::channel1, devices::ids::dma2, 4> {};
        template <>
        struct dma_channels_mapping<devices::ids::aes, devices::signals::in> :
            dma_channels_mapping_t<devices::ids::aes, devices::signals::in, devices::ids::dma2, 4> {};

        template <class t_device, uint8_t t_channel> struct dma_interrupt_mapping;
        template <> struct dma_interrupt_mapping<::devices::ids::dma1, 0> {
            using interrupt = ::devices::interrupts::dma1_channel1;
        };
        template <> struct dma_interrupt_mapping<::devices::ids::dma1, 1> {
            using interrupt = ::devices::interrupts::dma1_channel2;
        };
        template <> struct dma_interrupt_mapping<::devices::ids::dma1, 2> {
            using interrupt = ::devices::interrupts::dma1_channel3;
        };
        template <> struct dma_interrupt_mapping<::devices::ids::dma1, 3> {
            using interrupt = ::devices::interrupts::dma1_channel4;
        };
        template <> struct dma_interrupt_mapping<::devices::ids::dma1, 4> {
            using interrupt = ::devices::interrupts::dma1_channel5;
        };
        template <> struct dma_interrupt_mapping<::devices::ids::dma1, 5> {
            using interrupt = ::devices::interrupts::dma1_channel6;
        };
        template <> struct dma_interrupt_mapping<::devices::ids::dma1, 6> {
            using interrupt = ::devices::interrupts::dma1_channel7;
        };
        template <> struct dma_interrupt_mapping<::devices::ids::dma2, 0> {
            using interrupt = ::devices::interrupts::dma2_channel1;
        };
        template <> struct dma_interrupt_mapping<::devices::ids::dma2, 1> {
            using interrupt = ::devices::interrupts::dma2_channel2;
        };
        template <> struct dma_interrupt_mapping<::devices::ids::dma2, 2> {
            using interrupt = ::devices::interrupts::dma2_channel3;
        };
        template <> struct dma_interrupt_mapping<::devices::ids::dma2, 3> {
            using interrupt = ::devices::interrupts::dma2_channel4;
        };
        template <> struct dma_interrupt_mapping<::devices::ids::dma2, 4> {
            using interrupt = ::devices::interrupts::dma2_channel5;
        };

        template <auto v_value> struct enclosing { constexpr static auto value = v_value; };

        template <class...> struct default_dma_configuration;

        template <class t_direction, class t_pinc, class t_minc, class t_psize, class t_msize, class t_pl,
                  class t_address>
        struct default_dma_configuration<t_direction, t_pinc, t_minc, t_psize, t_msize, t_pl, t_address> {
            constexpr static uint32_t sr_value = t_direction::value | t_pinc::value | t_minc::value | t_psize::value
                                                 | t_msize::value | t_pl::value | 0x02;
            constexpr static uint32_t address = t_address::value;
        };

        template <>
        struct default_dma_configuration<::devices::device_signal<::devices::ids::usart1, ::devices::signals::tx>> :
            default_dma_configuration<enclosing<::devices::dma1::ccr<3>::dir::from_memory.value()>,
                                      enclosing<::devices::dma1::ccr<3>::pinc::disabled.value()>,
                                      enclosing<::devices::dma1::ccr<3>::minc::enabled.value()>,
                                      enclosing<::devices::dma1::ccr<3>::psize::bits8.value()>,
                                      enclosing<::devices::dma1::ccr<3>::msize::bits8.value()>,
                                      enclosing<::devices::dma1::ccr<3>::pl::low.value()>, enclosing<0x40013804>> {};
    } // namespace detail

    template <class... t_parameters> class dma {
    public:
        using device_signal = typename drivers::parameters::find_device_signal_t<t_parameters...>;
        using device =
            typename detail::dma_channels_mapping<typename device_signal::device, typename device_signal::signal>::dma;

        constexpr static uint8_t channel_index
            = detail::dma_channels_mapping<typename device_signal::device, typename device_signal::signal>::index;

        using interrupt = typename detail::dma_interrupt_mapping<device, channel_index>::interrupt;

        bool open() {
            // Enable dma.
            ::devices::manager::enable<device>();

            // Configure ports.
            using registers = ::devices::dma<device>;
            registers::template ccr<channel_index>::write(detail::default_dma_configuration<device_signal>::sr_value);
            registers::template cpar<channel_index>::write(detail::default_dma_configuration<device_signal>::address);

            // Set interrupt handler and enable interrupt.
            ::sys::interrupts::set_handler<interrupt>(&transfer_finished);
            ::sys::interrupts::enable<interrupt>();

            return true;
        }

        int transfer(void *data, uint16_t size) noexcept {
            using registers = ::devices::dma<device>;
            // Set source address and data length.
            registers::template cndtr<channel_index>::write(size);
            registers::template cmar<channel_index>::write(reinterpret_cast<uint32_t>(data));
            // Enable channel.
            registers::template ccr<channel_index>::en::set(registers::template ccr<channel_index>::en::enabled);
            ::os::api::wait(m_transfer_complete);
            return size;
        }

    private:
        static void transfer_finished() {
            using registers = ::devices::dma<device>;
            registers::ifcr::write(0x0f << (channel_index * 4));
            registers::template ccr<channel_index>::en::clear();
            ::os::isr::set(m_transfer_complete);
        }

        inline static ::os::event m_transfer_complete;
    };
} // namespace drivers
