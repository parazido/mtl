#pragma once

#include <cstdint>

#include <mtl/common/parameters.hpp>
#include <mtl/drivers/common.hpp>
#include <mtl/hw/devices.hpp>
#include <mtl/hw/dma.hpp>
#include <mtl/os/api.hpp>
#include <mtl/os/event.hpp>
#include <mtl/os/isr.hpp>
#include <mtl/sys/sys.hpp>

namespace mtl::drivers {
    namespace detail {
        template <auto v_value> struct enclosing { constexpr static auto value = v_value; };

        template <class...> struct default_dma_configuration;

        template <class t_direction, class t_pinc, class t_minc, class t_psize, class t_msize, class t_pl,
                  class t_address>
        struct default_dma_configuration<t_direction, t_pinc, t_minc, t_psize, t_msize, t_pl, t_address> {
            constexpr static uint32_t sr_value = t_direction::value | t_pinc::value | t_minc::value | t_psize::value
                                                 | t_msize::value | t_pl::value | 0x02;
            constexpr static uint32_t address = t_address::value;
        };

        // template <>
        // struct default_dma_configuration<::devices::device_signal<::devices::ids::usart2, ::devices::signals::tx>> :
        //     default_dma_configuration<enclosing<::devices::dma1::ccr<3>::dir::from_memory.value()>,
        //                               enclosing<::devices::dma1::ccr<3>::pinc::disabled.value()>,
        //                               enclosing<::devices::dma1::ccr<3>::minc::enabled.value()>,
        //                               enclosing<::devices::dma1::ccr<3>::psize::bits8.value()>,
        //                               enclosing<::devices::dma1::ccr<3>::msize::bits8.value()>,
        //                               enclosing<::devices::dma1::ccr<3>::pl::low.value()>, enclosing<0x40004428>> {};

        // template <>
        // struct default_dma_configuration<::devices::device_signal<::devices::ids::adc, void>> :
        //     default_dma_configuration<enclosing<::devices::dma1::ccr<0>::dir::from_peripheral.value()>,
        //                               enclosing<::devices::dma1::ccr<0>::pinc::disabled.value()>,
        //                               enclosing<::devices::dma1::ccr<0>::minc::disabled.value()>,
        //                               enclosing<::devices::dma1::ccr<0>::psize::bits16.value()>,
        //                               enclosing<::devices::dma1::ccr<0>::msize::bits16.value()>,
        //                               enclosing<::devices::dma1::ccr<0>::pl::medium.value()>, enclosing<0x40012440>>
        //                               {};

        template <class t_device_id, uint8_t v_index> struct dma_channel {
            using device_id = t_device_id;
            constexpr static auto index = v_index;
        };

        template <class... t_parameters> using map = mtl::traits::map<t_parameters...>;
        template <class... t_parameters> using pair = mtl::traits::pair<t_parameters...>;
        template <class... t_parameters> using device_signal = mtl::hw::device_signal<t_parameters...>;
        using dma_channels
            = map<pair<device_signal<mtl::hw::ids::adc1>, dma_channel<mtl::hw::ids::dma1, 0>>,
                  pair<device_signal<mtl::hw::ids::timer2, mtl::hw::signal::ch3>, dma_channel<mtl::hw::ids::dma1, 0>>,
                  pair<device_signal<mtl::hw::ids::timer17, mtl::hw::signal::ch1>, dma_channel<mtl::hw::ids::dma1, 0>>,
                  pair<device_signal<mtl::hw::ids::timer17, mtl::hw::signal::up>, dma_channel<mtl::hw::ids::dma1, 0>>,
                  pair<device_signal<mtl::hw::ids::spi1, mtl::hw::signal::rx>, dma_channel<mtl::hw::ids::dma1, 1>>,
                  pair<device_signal<mtl::hw::ids::usart1, mtl::hw::signal::tx>, dma_channel<mtl::hw::ids::dma1, 1>>,
                  pair<device_signal<mtl::hw::ids::i2c1, mtl::hw::signal::tx>, dma_channel<mtl::hw::ids::dma1, 1>>,
                  pair<device_signal<mtl::hw::ids::timer1, mtl::hw::signal::ch1>, dma_channel<mtl::hw::ids::dma1, 1>>,
                  pair<device_signal<mtl::hw::ids::timer2, mtl::hw::signal::up>, dma_channel<mtl::hw::ids::dma1, 1>>,
                  pair<device_signal<mtl::hw::ids::timer3, mtl::hw::signal::ch3>, dma_channel<mtl::hw::ids::dma1, 1>>,
                  pair<device_signal<mtl::hw::ids::spi1, mtl::hw::signal::tx>, dma_channel<mtl::hw::ids::dma1, 2>>,
                  pair<device_signal<mtl::hw::ids::usart1, mtl::hw::signal::rx>, dma_channel<mtl::hw::ids::dma1, 2>>,
                  pair<device_signal<mtl::hw::ids::i2c1, mtl::hw::signal::rx>, dma_channel<mtl::hw::ids::dma1, 2>>,
                  pair<device_signal<mtl::hw::ids::timer1, mtl::hw::signal::ch2>, dma_channel<mtl::hw::ids::dma1, 2>>,
                  pair<device_signal<mtl::hw::ids::timer2, mtl::hw::signal::ch2>, dma_channel<mtl::hw::ids::dma1, 2>>,
                  pair<device_signal<mtl::hw::ids::timer3, mtl::hw::signal::ch4>, dma_channel<mtl::hw::ids::dma1, 2>>,
                  pair<device_signal<mtl::hw::ids::timer3, mtl::hw::signal::up>, dma_channel<mtl::hw::ids::dma1, 2>>,
                  pair<device_signal<mtl::hw::ids::timer6, mtl::hw::signal::up>, dma_channel<mtl::hw::ids::dma1, 2>>,
                  pair<device_signal<mtl::hw::ids::dac, mtl::hw::signal::ch1>, dma_channel<mtl::hw::ids::dma1, 2>>,
                  pair<device_signal<mtl::hw::ids::timer16, mtl::hw::signal::ch1>, dma_channel<mtl::hw::ids::dma1, 2>>,
                  pair<device_signal<mtl::hw::ids::timer16, mtl::hw::signal::up>, dma_channel<mtl::hw::ids::dma1, 2>>,
                  pair<device_signal<mtl::hw::ids::spi2, mtl::hw::signal::rx>, dma_channel<mtl::hw::ids::dma1, 3>>,
                  pair<device_signal<mtl::hw::ids::usart2, mtl::hw::signal::tx>, dma_channel<mtl::hw::ids::dma1, 3>>,
                  pair<device_signal<mtl::hw::ids::i2c2, mtl::hw::signal::tx>, dma_channel<mtl::hw::ids::dma1, 3>>,
                  pair<device_signal<mtl::hw::ids::timer1, mtl::hw::signal::ch4>, dma_channel<mtl::hw::ids::dma1, 3>>,
                  pair<device_signal<mtl::hw::ids::timer1, mtl::hw::signal::trig>, dma_channel<mtl::hw::ids::dma1, 3>>,
                  pair<device_signal<mtl::hw::ids::timer1, mtl::hw::signal::com>, dma_channel<mtl::hw::ids::dma1, 3>>,
                  pair<device_signal<mtl::hw::ids::timer2, mtl::hw::signal::ch4>, dma_channel<mtl::hw::ids::dma1, 3>>,
                  pair<device_signal<mtl::hw::ids::timer3, mtl::hw::signal::ch1>, dma_channel<mtl::hw::ids::dma1, 3>>,
                  pair<device_signal<mtl::hw::ids::timer3, mtl::hw::signal::trig>, dma_channel<mtl::hw::ids::dma1, 3>>,
                  pair<device_signal<mtl::hw::ids::timer7, mtl::hw::signal::up>, dma_channel<mtl::hw::ids::dma1, 3>>,
                  pair<device_signal<mtl::hw::ids::dac, mtl::hw::signal::ch2>, dma_channel<mtl::hw::ids::dma1, 3>>,
                  pair<device_signal<mtl::hw::ids::spi2, mtl::hw::signal::tx>, dma_channel<mtl::hw::ids::dma1, 4>>,
                  pair<device_signal<mtl::hw::ids::usart2, mtl::hw::signal::rx>, dma_channel<mtl::hw::ids::dma1, 4>>,
                  pair<device_signal<mtl::hw::ids::i2c2, mtl::hw::signal::rx>, dma_channel<mtl::hw::ids::dma1, 4>>,
                  pair<device_signal<mtl::hw::ids::timer1, mtl::hw::signal::ch3>, dma_channel<mtl::hw::ids::dma1, 4>>,
                  pair<device_signal<mtl::hw::ids::timer1, mtl::hw::signal::up>, dma_channel<mtl::hw::ids::dma1, 4>>,
                  pair<device_signal<mtl::hw::ids::timer2, mtl::hw::signal::ch1>, dma_channel<mtl::hw::ids::dma1, 4>>,
                  pair<device_signal<mtl::hw::ids::timer15, mtl::hw::signal::ch1>, dma_channel<mtl::hw::ids::dma1, 4>>,
                  pair<device_signal<mtl::hw::ids::timer15, mtl::hw::signal::up>, dma_channel<mtl::hw::ids::dma1, 4>>,
                  pair<device_signal<mtl::hw::ids::timer15, mtl::hw::signal::trig>, dma_channel<mtl::hw::ids::dma1, 4>>,
                  pair<device_signal<mtl::hw::ids::timer15, mtl::hw::signal::com>, dma_channel<mtl::hw::ids::dma1, 4>>,
                  pair<device_signal<mtl::hw::ids::usart3, mtl::hw::signal::rx>, dma_channel<mtl::hw::ids::dma1, 5>>,
                  pair<device_signal<mtl::hw::ids::usart4, mtl::hw::signal::rx>, dma_channel<mtl::hw::ids::dma1, 5>>,
                  pair<device_signal<mtl::hw::ids::usart3, mtl::hw::signal::tx>, dma_channel<mtl::hw::ids::dma1, 6>>>;

        using dma_interrupts
            = map<pair<dma_channel<mtl::hw::ids::dma1, 0>, mtl::hw::interrupts::dma_ch1>,
                  pair<dma_channel<mtl::hw::ids::dma1, 1>, mtl::hw::interrupts::dma_ch2_3_dma2_ch1_2>,
                  pair<dma_channel<mtl::hw::ids::dma1, 2>, mtl::hw::interrupts::dma_ch2_3_dma2_ch1_2>,
                  pair<dma_channel<mtl::hw::ids::dma1, 3>, mtl::hw::interrupts::dma_ch4_5_6_7_dma2_ch3_4_5>,
                  pair<dma_channel<mtl::hw::ids::dma1, 4>, mtl::hw::interrupts::dma_ch4_5_6_7_dma2_ch3_4_5>,
                  pair<dma_channel<mtl::hw::ids::dma1, 5>, mtl::hw::interrupts::dma_ch4_5_6_7_dma2_ch3_4_5>,
                  pair<dma_channel<mtl::hw::ids::dma1, 6>, mtl::hw::interrupts::dma_ch4_5_6_7_dma2_ch3_4_5>>;
    } // namespace detail

    template <class...> struct get_dma_channel;

    template <class t_device_id, class t_signal_id> struct get_dma_channel<t_device_id, t_signal_id> {
        using type = typename detail::dma_channels::find<mtl::hw::device_signal<t_device_id, t_signal_id>>::value;
    };

    template <class t_device_id, class t_signal_id>
    struct get_dma_channel<mtl::hw::device_signal<t_device_id, t_signal_id>> {
        using type = typename detail::dma_channels::find<mtl::hw::device_signal<t_device_id, t_signal_id>>::type::value;
    };

    template <class... t_parameters> class dma {
    public:
        using sys = typename mtl::parameters<t_parameters...>::find_type<mtl::sys>::type;
        using device_signal = typename mtl::parameters<t_parameters...>::find_type<mtl::hw::device_signal>::type;
        using dma_channel = typename get_dma_channel<device_signal>::type;
        using device_id = typename dma_channel::device_id;
        using interrupt = typename detail::dma_interrupts::template find<dma_channel>::type;
        using registers = mtl::hw::dma<device_id>;
        constexpr static uint8_t channel_index = dma_channel::index;

        bool open() {
            // Enable dma.
            mtl::pwr::template enable<device_id>();

            // Configure ports.
            registers::template ccr<channel_index>::write(detail::default_dma_configuration<device_signal>::sr_value);
            registers::template cpar<channel_index>::write(detail::default_dma_configuration<device_signal>::address);

            // Set interrupt handler and enable interrupt.
            sys::interrupts::template set_handler<interrupt>(&transfer_finished);
            sys::interrupts::template enable<interrupt>();

            return true;
        }

        int transfer(void *data, uint16_t size) noexcept {
            // Set source address and data length.
            registers::template cndtr<channel_index>::write(size);
            registers::template cmar<channel_index>::write(reinterpret_cast<uint32_t>(data));
            // Enable channel.
            registers::template ccr<channel_index>::en::set(registers::template ccr<channel_index>::en::enabled);
            mtl::api::wait(m_transfer_complete);
            return size;
        }

    private:
        static void transfer_finished() {
            registers::ifcr::write(0x0f << (channel_index * 4));
            registers::template ccr<channel_index>::en::clear();
            mtl::isr::set(m_transfer_complete);
        }

        inline static mtl::event m_transfer_complete;
    };
} // namespace mtl::drivers
