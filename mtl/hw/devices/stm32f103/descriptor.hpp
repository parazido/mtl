#pragma once

#include <mtl/traits/map.hpp>

namespace mtl::hw {
    namespace types {
        struct adc;
        struct afio;
        struct bkp;
        struct can;
        struct crc;
        struct dac;
        struct dma;
        struct flitf;
        struct fsmc;
        struct gpio;
        struct i2c;
        struct pwr;
        struct sdio;
        struct spi;
        struct sram;
        struct timer;
        struct usart;
        struct usb;
        struct wwdg;
    } // namespace types

    namespace ids {
        struct adc1;
        struct adc2;
        struct adc3;
        struct afio;
        struct bkp;
        struct can;
        struct crc;
        struct dac;
        struct dma1;
        struct dma2;
        struct flitf;
        struct fsmc;
        struct gpioa;
        struct gpiob;
        struct gpioc;
        struct gpiod;
        struct gpioe;
        struct gpiof;
        struct gpiog;
        struct i2c1;
        struct i2c2;
        struct pwr;
        struct sdio;
        struct spi1;
        struct spi2;
        struct spi3;
        struct sram;
        struct timer1;
        struct timer2;
        struct timer3;
        struct timer4;
        struct timer5;
        struct timer6;
        struct timer7;
        struct timer8;
        struct timer9;
        struct timer10;
        struct timer11;
        struct timer12;
        struct timer13;
        struct timer14;
        struct usart1;
        struct usart2;
        struct usart3;
        struct usart4;
        struct usart5;
        struct usb;
        struct wwdg;
    } // namespace ids

    using device_type_mapping
        = mtl::traits::map<mtl::traits::pair<ids::adc1, types::adc>, mtl::traits::pair<ids::adc2, types::adc>,
                           mtl::traits::pair<ids::adc3, types::adc>, mtl::traits::pair<ids::afio, types::afio>,
                           mtl::traits::pair<ids::bkp, types::bkp>, mtl::traits::pair<ids::can, types::can>,
                           mtl::traits::pair<ids::crc, types::crc>, mtl::traits::pair<ids::dac, types::dac>,
                           mtl::traits::pair<ids::dma1, types::dma>, mtl::traits::pair<ids::dma2, types::dma>,
                           mtl::traits::pair<ids::flitf, types::flitf>, mtl::traits::pair<ids::fsmc, types::fsmc>,
                           mtl::traits::pair<ids::gpioa, types::gpio>, mtl::traits::pair<ids::gpiob, types::gpio>,
                           mtl::traits::pair<ids::gpioc, types::gpio>, mtl::traits::pair<ids::gpiod, types::gpio>,
                           mtl::traits::pair<ids::gpioe, types::gpio>, mtl::traits::pair<ids::gpiof, types::gpio>,
                           mtl::traits::pair<ids::gpiog, types::gpio>, mtl::traits::pair<ids::i2c1, types::i2c>,
                           mtl::traits::pair<ids::i2c2, types::i2c>, mtl::traits::pair<ids::pwr, types::pwr>,
                           mtl::traits::pair<ids::sdio, types::sdio>, mtl::traits::pair<ids::spi1, types::spi>,
                           mtl::traits::pair<ids::spi2, types::spi>, mtl::traits::pair<ids::spi3, types::spi>,
                           mtl::traits::pair<ids::sram, types::sram>, mtl::traits::pair<ids::timer1, types::timer>,
                           mtl::traits::pair<ids::timer2, types::timer>, mtl::traits::pair<ids::timer3, types::timer>,
                           mtl::traits::pair<ids::timer4, types::timer>, mtl::traits::pair<ids::timer5, types::timer>,
                           mtl::traits::pair<ids::timer6, types::timer>, mtl::traits::pair<ids::timer7, types::timer>,
                           mtl::traits::pair<ids::timer8, types::timer>, mtl::traits::pair<ids::timer9, types::timer>,
                           mtl::traits::pair<ids::timer10, types::timer>, mtl::traits::pair<ids::timer11, types::timer>,
                           mtl::traits::pair<ids::timer12, types::timer>, mtl::traits::pair<ids::timer13, types::timer>,
                           mtl::traits::pair<ids::timer14, types::timer>, mtl::traits::pair<ids::usart1, types::usart>,
                           mtl::traits::pair<ids::usart2, types::usart>, mtl::traits::pair<ids::usart3, types::usart>,
                           mtl::traits::pair<ids::usart4, types::usart>, mtl::traits::pair<ids::usart5, types::usart>,
                           mtl::traits::pair<ids::usb, types::usb>, mtl::traits::pair<ids::wwdg, types::wwdg>>;

    template <class t_device_id> using device_type_by_id = typename device_type_mapping::find<t_device_id>::type::value;

    namespace bus {
        struct hsi {};
        struct hse {};
        struct lsi {};
        struct lse {};
        struct pllclk {};
        struct sysclk {};
        struct ahb {};
        struct hclk {};
        struct cst {};
        struct fclk {};
        struct apb1 {};
        struct apb2 {};
        struct hclk_div2 {};
        struct pclk1 {};
        struct timclk1 {};
        struct pclk2 {};
        struct timclk2 {};
        struct adcclk {};
        struct rtcclk {};
        struct iwdgclk {};
        struct flitfclk {};
        struct usbclk {};
        struct i2s2clk {};
        struct i2s3clk {};
        struct sdioclk {};
        struct fsmcclk {};
    } // namespace bus

    namespace signal {
        struct ck;
        struct cts;
        struct rts;
        struct rx;
        struct tx;
        struct bkin;
        struct etr;
        struct ch1;
        struct ch1_oc;
        struct ch1n_oc;
        struct ch1_ic;
        struct ch2;
        struct ch2_oc;
        struct ch2n_oc;
        struct ch2_ic;
        struct ch3;
        struct ch3_oc;
        struct ch3n_oc;
        struct ch3_ic;
        struct ch4;
        struct ch4_oc;
        struct ch4_ic;
        struct nss;
        struct sck;
        struct miso;
        struct mosi;
        struct scl;
        struct sda;
        struct smbai;
        struct dm;
        struct dp;
    } // namespace signal

    template <class t_bus> constexpr double frequency = 0.0;
    template <> constexpr double frequency<bus::hsi> = 8000000.0;
    template <> constexpr double frequency<bus::lsi> = 40000.0;
} // namespace mtl::hw
