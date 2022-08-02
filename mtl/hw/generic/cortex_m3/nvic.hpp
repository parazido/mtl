#pragma once

#include <cstdint>

#include <mtl/hw/device.hpp>

namespace mtl::hw {
    namespace descriptor {
        template <unsigned int v_base_address> struct nvic {
            constexpr static unsigned int base_address = v_base_address;
            template <uint32_t v_offset, class t_type>
            using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

            struct ictr : register_<0x004, uint32_t> {};

            struct stcsr : register_<0x010, uint32_t> {
                struct enable : mtl::hw::field<stcsr, 0, 1> {
                    using option = mtl::hw::option<enable>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct tickint : mtl::hw::field<stcsr, 1, 1> {
                    using option = mtl::hw::option<tickint>;
                    constexpr static option disabled = 0;
                    constexpr static option enabled = 1;
                };

                struct clksource : mtl::hw::field<stcsr, 2, 1> {
                    using option = mtl::hw::option<clksource>;
                    constexpr static option external = 0;
                    constexpr static option core = 1;
                };

                struct countflag : mtl::hw::field<stcsr, 16, 1> {
                    using option = mtl::hw::option<countflag>;
                    constexpr static option inactive = 0;
                    constexpr static option active = 1;
                };
            };

            struct strvr : register_<0x014, uint32_t> {};
            struct stcvr : register_<0x018, uint32_t> {};
            struct stclvr : register_<0x01c, uint32_t> {};
            struct irq_0_31_ser : register_<0x100, uint32_t> {};
            struct irq_32_63_ser : register_<0x104, uint32_t> {};
            struct irq_64_95_ser : register_<0x108, uint32_t> {};
            struct irq_96_127_ser : register_<0x10c, uint32_t> {};
            struct irq_128_159_ser : register_<0x110, uint32_t> {};
            struct irq_160_191_ser : register_<0x114, uint32_t> {};
            struct irq_192_223_ser : register_<0x118, uint32_t> {};
            struct irq_224_239_ser : register_<0x11c, uint32_t> {};
            struct irq_0_31_cer : register_<0x180, uint32_t> {};
            struct irq_32_63_cer : register_<0x184, uint32_t> {};
            struct irq_64_95_cer : register_<0x188, uint32_t> {};
            struct irq_96_127_cer : register_<0x18c, uint32_t> {};
            struct irq_128_159_cer : register_<0x190, uint32_t> {};
            struct irq_160_191_cer : register_<0x194, uint32_t> {};
            struct irq_192_223_cer : register_<0x198, uint32_t> {};
            struct irq_224_239_cer : register_<0x19c, uint32_t> {};
            struct irq_0_31_spr : register_<0x200, uint32_t> {};
            struct irq_32_63_spr : register_<0x204, uint32_t> {};
            struct irq_64_95_spr : register_<0x208, uint32_t> {};
            struct irq_96_127_spr : register_<0x20c, uint32_t> {};
            struct irq_128_159_spr : register_<0x210, uint32_t> {};
            struct irq_160_191_spr : register_<0x214, uint32_t> {};
            struct irq_192_223_spr : register_<0x218, uint32_t> {};
            struct irq_224_239_spr : register_<0x21c, uint32_t> {};
            struct irq_0_31_cpr : register_<0x280, uint32_t> {};
            struct irq_32_63_cpr : register_<0x284, uint32_t> {};
            struct irq_64_95_cpr : register_<0x288, uint32_t> {};
            struct irq_96_127_cpr : register_<0x28c, uint32_t> {};
            struct irq_128_159_cpr : register_<0x290, uint32_t> {};
            struct irq_160_191_cpr : register_<0x294, uint32_t> {};
            struct irq_192_223_cpr : register_<0x298, uint32_t> {};
            struct irq_224_239_cpr : register_<0x29c, uint32_t> {};
            struct irq_0_31_abr : register_<0x300, uint32_t> {};
            struct irq_32_63_abr : register_<0x304, uint32_t> {};
            struct irq_64_95_abr : register_<0x308, uint32_t> {};
            struct irq_96_127_abr : register_<0x30c, uint32_t> {};
            struct irq_128_159_abr : register_<0x310, uint32_t> {};
            struct irq_160_191_abr : register_<0x314, uint32_t> {};
            struct irq_192_223_abr : register_<0x318, uint32_t> {};
            struct irq_224_239_abr : register_<0x31c, uint32_t> {};
            struct irq_0_3_pr : register_<0x400, uint32_t> {};
            struct irq_4_7_pr : register_<0x404, uint32_t> {};
            struct irq_8_11_pr : register_<0x408, uint32_t> {};
            struct irq_12_15_pr : register_<0x40c, uint32_t> {};
            struct irq_16_19_pr : register_<0x410, uint32_t> {};
            struct irq_20_23_pr : register_<0x414, uint32_t> {};
            struct irq_24_27_pr : register_<0x418, uint32_t> {};
            struct irq_28_31_pr : register_<0x41c, uint32_t> {};
            struct irq_32_35_pr : register_<0x420, uint32_t> {};
            struct irq_36_39_pr : register_<0x424, uint32_t> {};
            struct irq_40_43_pr : register_<0x428, uint32_t> {};
            struct irq_44_47_pr : register_<0x42c, uint32_t> {};
            struct irq_48_51_pr : register_<0x430, uint32_t> {};
            struct irq_52_55_pr : register_<0x434, uint32_t> {};
            struct irq_56_59_pr : register_<0x438, uint32_t> {};
            struct irq_60_63_pr : register_<0x43c, uint32_t> {};
            struct irq_64_67_pr : register_<0x440, uint32_t> {};
            struct irq_68_71_pr : register_<0x444, uint32_t> {};
            struct irq_72_75_pr : register_<0x448, uint32_t> {};
            struct irq_76_79_pr : register_<0x44c, uint32_t> {};
            struct irq_80_83_pr : register_<0x450, uint32_t> {};
            struct irq_84_87_pr : register_<0x454, uint32_t> {};
            struct irq_88_91_pr : register_<0x458, uint32_t> {};
            struct irq_92_95_pr : register_<0x45c, uint32_t> {};
            struct irq_96_99_pr : register_<0x460, uint32_t> {};
            struct irq_100_103_pr : register_<0x464, uint32_t> {};
            struct irq_104_107_pr : register_<0x468, uint32_t> {};
            struct irq_108_111_pr : register_<0x46c, uint32_t> {};
            struct irq_112_115_pr : register_<0x470, uint32_t> {};
            struct irq_116_119_pr : register_<0x474, uint32_t> {};
            struct irq_120_123_pr : register_<0x478, uint32_t> {};
            struct irq_124_127_pr : register_<0x47c, uint32_t> {};
            struct irq_128_131_pr : register_<0x480, uint32_t> {};
            struct irq_132_135_pr : register_<0x484, uint32_t> {};
            struct irq_136_139_pr : register_<0x488, uint32_t> {};
            struct irq_140_143_pr : register_<0x48c, uint32_t> {};
            struct irq_144_147_pr : register_<0x490, uint32_t> {};
            struct irq_148_151_pr : register_<0x494, uint32_t> {};
            struct irq_152_155_pr : register_<0x498, uint32_t> {};
            struct irq_156_159_pr : register_<0x49c, uint32_t> {};
            struct irq_160_163_pr : register_<0x4a0, uint32_t> {};
            struct irq_164_167_pr : register_<0x4a4, uint32_t> {};
            struct irq_168_171_pr : register_<0x4a8, uint32_t> {};
            struct irq_172_175_pr : register_<0x4ac, uint32_t> {};
            struct irq_176_179_pr : register_<0x4b0, uint32_t> {};
            struct irq_180_183_pr : register_<0x4b4, uint32_t> {};
            struct irq_184_187_pr : register_<0x4b8, uint32_t> {};
            struct irq_188_191_pr : register_<0x4bc, uint32_t> {};
            struct irq_192_195_pr : register_<0x4c0, uint32_t> {};
            struct irq_196_199_pr : register_<0x4c4, uint32_t> {};
            struct irq_200_203_pr : register_<0x4c8, uint32_t> {};
            struct irq_204_207_pr : register_<0x4cc, uint32_t> {};
            struct irq_208_211_pr : register_<0x4d0, uint32_t> {};
            struct irq_212_215_pr : register_<0x4d4, uint32_t> {};
            struct irq_216_219_pr : register_<0x4d8, uint32_t> {};
            struct irq_220_223_pr : register_<0x4dc, uint32_t> {};
            struct irq_224_227_pr : register_<0x4e0, uint32_t> {};
            struct irq_228_231_pr : register_<0x4e4, uint32_t> {};
            struct irq_232_235_pr : register_<0x4e8, uint32_t> {};
            struct irq_236_239_pr : register_<0x4ec, uint32_t> {};
            struct irq_240_243_pr : register_<0x4f0, uint32_t> {};
            struct cpuidbr : register_<0xd00, uint32_t> {};
            struct icsr : register_<0xd04, uint32_t> {};
            struct vtor : register_<0xd08, uint32_t> {};
            struct aircr : register_<0xd0c, uint32_t> {};
            struct scr : register_<0xd10, uint32_t> {};
            struct ccr : register_<0xd14, uint32_t> {};
            struct sh_4_7_pr : register_<0xd18, uint32_t> {};
            struct sh_8_11_pr : register_<0xd1c, uint32_t> {};
            struct sh_12_15_pr : register_<0xd20, uint32_t> {};
            struct shcsr : register_<0xd24, uint32_t> {};
            struct cfsr : register_<0xd28, uint32_t> {};
            struct hfsr : register_<0xd2c, uint32_t> {};
            struct dfsr : register_<0xd30, uint32_t> {};
            struct mmar : register_<0xd34, uint32_t> {};
            struct bfar : register_<0xd38, uint32_t> {};
            struct afsr : register_<0xd3c, uint32_t> {};
            struct pfr0 : register_<0xd40, uint32_t> {};
            struct pfr1 : register_<0xd44, uint32_t> {};
            struct dfr0 : register_<0xd48, uint32_t> {};
            struct afr0 : register_<0xd4c, uint32_t> {};
            struct mmfr0 : register_<0xd50, uint32_t> {};
            struct mmfr1 : register_<0xd54, uint32_t> {};
            struct mmfr2 : register_<0xd58, uint32_t> {};
            struct mmfr3 : register_<0xd5c, uint32_t> {};
            struct isar0 : register_<0xd60, uint32_t> {};
            struct isar1 : register_<0xd64, uint32_t> {};
            struct isar2 : register_<0xd68, uint32_t> {};
            struct isar3 : register_<0xd6c, uint32_t> {};
            struct isar4 : register_<0xd70, uint32_t> {};
            struct stir : register_<0xf00, uint32_t> {};
            struct pid4 : register_<0xfd0, uint32_t> {};
            struct pid5 : register_<0xfd4, uint32_t> {};
            struct pid6 : register_<0xfd8, uint32_t> {};
            struct pid7 : register_<0xfdc, uint32_t> {};
            struct pid0 : register_<0xfe0, uint32_t> {};
            struct pid1 : register_<0xfe4, uint32_t> {};
            struct pid2 : register_<0xfe8, uint32_t> {};
            struct pid3 : register_<0xfec, uint32_t> {};
            struct cid0 : register_<0xff0, uint32_t> {};
            struct cid1 : register_<0xff4, uint32_t> {};
            struct cid2 : register_<0xff8, uint32_t> {};
            struct cid3 : register_<0xffc, uint32_t> {};
        };
    } // namespace descriptor

    using nvic = descriptor::nvic<0xe000e000>;

    namespace interrupts {
        namespace detail {
            template <int v_register_index, int v_table_offset, class t_set_enable_register = void,
                      class t_clear_enable_register = void, class t_set_pending_register = void,
                      class t_clear_pending_register = void, class t_active_register = void>
            struct interrupt {
                using set_enable_register = t_set_enable_register;
                using clear_enable_register = t_clear_enable_register;
                using set_pending_register = t_set_pending_register;
                using clear_pending_register = t_clear_pending_register;
                using active_register = t_active_register;

                constexpr static auto register_index = v_register_index;
                constexpr static auto table_offset = v_table_offset;
            };
        } // namespace detail

        using nmi = detail::interrupt<-1, 2>;
        using hard_fault = detail::interrupt<-1, 3>;
        using mem_manage = detail::interrupt<-1, 4>;
        using bus_fault = detail::interrupt<-1, 5>;
        using usage_fault = detail::interrupt<-1, 6>;
        using svc = detail::interrupt<-1, 11>;
        using debug_mon = detail::interrupt<-1, 12>;
        using pend_sv = detail::interrupt<-1, 14>;
        using sys_tick = detail::interrupt<-1, 15>;
        using wwdg = detail::interrupt<0, 16, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                       nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using pvd = detail::interrupt<1, 17, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                      nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using tamper = detail::interrupt<2, 18, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                         nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using rtc = detail::interrupt<3, 19, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                      nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using flash = detail::interrupt<4, 20, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                        nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using rcc = detail::interrupt<5, 21, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                      nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using exti0 = detail::interrupt<6, 22, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                        nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using exti1 = detail::interrupt<7, 23, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                        nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using exti2 = detail::interrupt<8, 24, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                        nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using exti3 = detail::interrupt<9, 25, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                        nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using exti4 = detail::interrupt<10, 26, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                        nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using dma1_channel1 = detail::interrupt<11, 27, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                                nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using dma1_channel2 = detail::interrupt<12, 28, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                                nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using dma1_channel3 = detail::interrupt<13, 29, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                                nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using dma1_channel4 = detail::interrupt<14, 30, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                                nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using dma1_channel5 = detail::interrupt<15, 31, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                                nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using dma1_channel6 = detail::interrupt<16, 32, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                                nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using dma1_channel7 = detail::interrupt<17, 33, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                                nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using adc1_2 = detail::interrupt<18, 34, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                         nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using usb_hp_can_tx = detail::interrupt<19, 35, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                                nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using usb_lp_can_rx0 = detail::interrupt<20, 36, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                                 nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using can_rx1 = detail::interrupt<21, 37, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                          nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using can_sce = detail::interrupt<22, 38, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                          nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using exti9_5 = detail::interrupt<23, 39, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                          nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using tim1_brk = detail::interrupt<24, 40, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                           nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using tim1_up = detail::interrupt<25, 41, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                          nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using tim1_trg_com = detail::interrupt<26, 42, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                               nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using tim1_cc = detail::interrupt<27, 43, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                          nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using tim2 = detail::interrupt<28, 44, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                       nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using tim3 = detail::interrupt<29, 45, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                       nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using tim4 = detail::interrupt<30, 46, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                       nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using i2c1_ev = detail::interrupt<31, 47, nvic::irq_0_31_ser, nvic::irq_0_31_cer, nvic::irq_0_31_spr,
                                          nvic::irq_0_31_cpr, nvic::irq_0_31_abr>;
        using i2c1_er = detail::interrupt<0, 48, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                          nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using i2c2_ev = detail::interrupt<1, 49, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                          nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using i2c2_er = detail::interrupt<2, 50, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                          nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using spi1 = detail::interrupt<3, 51, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                       nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using spi2 = detail::interrupt<4, 52, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                       nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using usart1 = detail::interrupt<5, 53, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                         nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using usart2 = detail::interrupt<6, 54, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                         nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using usart3 = detail::interrupt<7, 55, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                         nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using exti15_10 = detail::interrupt<8, 56, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                            nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using rtc_alarm = detail::interrupt<9, 57, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                            nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using usb_wkup = detail::interrupt<10, 58, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                           nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using tim8_brk = detail::interrupt<11, 59, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                           nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using tim8_up = detail::interrupt<12, 60, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                          nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using tim8_trg_com = detail::interrupt<13, 61, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                               nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using tim8_cc = detail::interrupt<14, 62, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                          nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using adc3 = detail::interrupt<15, 63, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                       nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using fsmc = detail::interrupt<16, 64, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                       nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using sdio = detail::interrupt<17, 65, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                       nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using tim5 = detail::interrupt<18, 66, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                       nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using spi3 = detail::interrupt<19, 67, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                       nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using uart4 = detail::interrupt<20, 68, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                        nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using uart5 = detail::interrupt<21, 69, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                        nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using tim6 = detail::interrupt<22, 70, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                       nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using tim7 = detail::interrupt<23, 71, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                       nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using dma2_channel1 = detail::interrupt<24, 72, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                                nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using dma2_channel2 = detail::interrupt<25, 73, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                                nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using dma2_channel3 = detail::interrupt<26, 74, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                                nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
        using dma2_channel4_5 = detail::interrupt<27, 75, nvic::irq_32_63_ser, nvic::irq_32_63_cer, nvic::irq_32_63_spr,
                                                  nvic::irq_32_63_cpr, nvic::irq_32_63_abr>;
    } // namespace interrupts
} // namespace mtl::hw
