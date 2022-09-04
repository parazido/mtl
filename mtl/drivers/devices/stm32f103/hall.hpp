#pragma once

#include <mtl/common/parameters.hpp>
#include <mtl/drivers/common.hpp>
#include <mtl/hw/afio.hpp>
#include <mtl/hw/descriptor.hpp>
#include <mtl/hw/timer.hpp>

namespace mtl::drivers {
    namespace hall_ {
        template <class t_phase_a, class t_phase_b, class t_phase_c> struct io {
            using phase_a = t_phase_a;
            using phase_b = t_phase_b;
            using phase_c = t_phase_c;
        };
    } // namespace hall_

    template <class... t_parameters> class hall {
    public:
        using sys = typename mtl::parameters<t_parameters...>::find_type<mtl::sys>::type;
        using device_id = typename mtl::parameters<t_parameters...>::find_type<mtl::drivers::device_id>::type::type;
        using device = mtl::hw::timer<device_id>;
        using io = typename mtl::parameters<t_parameters...>::find_type<hall_::io>::type;

        bool open(void (*change_handler)()) {
            // Remap IOs.
            sys::template enable<mtl::hw::ids::afio>();
            mtl::hw::afio::mapr::tim3_remap::set(mtl::hw::afio::mapr::tim3_remap::partial);
            // Initialize IOs.
            m_io_a.open();
            m_io_b.open();
            m_io_c.open();

            // Power timer up.
            sys::template enable<device_id>();

            // Initialize basic configuration.
            device::cnt::write(0);
            device::psc::write(2340);
            device::arr::write(0xffff);
            device::cr1::write(device::cr1::ckd::nomul, device::cr1::arpe::enabled, device::cr1::cms::edge,
                               device::cr1::dir::upcount, device::cr1::opm::disabled, device::cr1::urs::any,
                               device::cr1::udis::uev_enabled);

            // Configure measurement channel (channel 1).
            // Configure input capture in XOR (Hall sensor mode).
            device::cr2::ti1s::set(device::cr2::ti1s::ch1_2_3);
            // Congifure slave mode to update values on TIF_ED (channel 1 xor channel 2 xor channel 3) is changed.
            device::smcr::write(device::smcr::sms::reset, device::smcr::ts::ti1f_ed, device::smcr::msm::no,
                                device::smcr::etf::div32_n8, device::smcr::etps::nodiv, device::smcr::ece::disabled,
                                device::smcr::etp::non_inverted);
            // Configure channel 1 in IC mode.
            device::ccmr1::write(device::ccmr1::cc1s::input_trc, device::ccmr1::ic1psc::no, device::ccmr1::ic1f::no);
            device::ccer::write(device::ccer::cc1e::enabled, device::ccer::cc1p::non_inverted);

            // Enable interrupts.
            sys::interrupts::template enable<mtl::hw::interrupts::tim3>();
            sys::interrupts::template set_handler<mtl::hw::interrupts::tim3>(&handler);
            m_handler = change_handler;
            //device::

            // Enable timer.
            device::cr1::cen::set(device::cr1::cen::enabled);
            return true;
        }

        float read() { return 0.f; }

        [[gnu::always_inline]] inline uint8_t position_index() const {
            return (m_io_a.test()?1:0) | (m_io_b.test()?2:0) | (m_io_c.test()?4:0);
        }

    private:
        static void handler() {
            //if ()
            m_handler();
        }

    private:
        mtl::drivers::gpio<
            sys, mtl::hw::link<mtl::hw::device_signal<device_id, mtl::hw::signal::ch1_ic>, typename io::phase_a>>
            m_io_a;
        mtl::drivers::gpio<
            sys, mtl::hw::link<mtl::hw::device_signal<device_id, mtl::hw::signal::ch2_ic>, typename io::phase_b>>
            m_io_b;
        mtl::drivers::gpio<
            sys, mtl::hw::link<mtl::hw::device_signal<device_id, mtl::hw::signal::ch3_ic>, typename io::phase_c>>
            m_io_c;
        uint16_t m_value = 0;
        inline static void (*m_handler)();
    };
} // namespace mtl::drivers

// void configHallSensorTimer(void) {

//     // Timer 3 decodes the 3 HallSensor input lines
//     // see referenze manual page 305

//     // define timer clock
//     // between two changes on the hall sensor lines on the lowest rotation
//     // speed (eg. 1/100 from max. speed)  the timer must not overflow
//     // define timer counter clock appropriate

//     // enable port pins for hall inputs
//     RCC_APB2PeriphClockCmd(...);
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_...;
//     GPIO_InitStructure.GPIO_Mode = ... GPIO_Init(..., &GPIO_InitStructure);

//     RCC_APB1PeriphClockCmd(TIM4_CLK, ENABLE);

//     // timer base configuration
//     // 126 => 3,5s till overflow ; 285,714kHz TimerClock [36MHz/Prescaler]
//     TIM_TimeBaseStructure.TIM_Prescaler = 126;
//     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//     TIM_TimeBaseStructure.TIM_Period = 65535;
//     TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//     TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
//     TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

//     // enable hall sensor
//     // T1F_ED will be connected to  HallSensoren Imputs
//     // TIM4_CH1,TIM4_CH2,TIM4_CH3
//     TIM_SelectHallSensor(TIM4, ENABLE);

//     //  TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
//     //  uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity)

//     // HallSensor event is delivered with singnal TI1F_ED
//     // (this is XOR of the three hall sensor lines)
//     // Signal TI1F_ED: falling and rising ddge of the inputs is used
//     TIM_SelectInputTrigger(TIM4, TIM_TS_TI1F_ED);

//     // On every TI1F_ED event the counter is resetted and update is tiggered
//     TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);

//     // Channel 1 in input capture mode
//     // on every TCR edge (build from TI1F_ED which is a HallSensor edge)
//     // the timervalue is copied into ccr register and a CCR1 Interrupt
//     // TIM_IT_CC1 is fired

//     TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
//     TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
//     // listen to T1, the  HallSensorEvent
//     TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_TRC;
//     // Div:1, every edge
//     TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//     // noise filter: 1111 => 72000kHz / factor (==1) / 32 / 8 -> 281kHz
//     // input noise filter (reference manual page 322)
//     TIM_ICInitStructure.TIM_ICFilter = 0xF;
//     TIM_ICInit(TIM4, &TIM_ICInitStructure);

//     // channel 2 can be use for commution delay between hallsensor edge
//     // and switching the FET into the next step. if this delay time is
//     // over the channel 2 generates the commutation signal to the motor timer
//     TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
//     TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//     TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//     TIM_OCInitStructure.TIM_Pulse = 1; // 1 is no delay; 2000 = 7ms
//     TIM_OC2Init(TIM4, &TIM_OCInitStructure);

//     // clear interrupt flag
//     TIM_ClearFlag(TIM4, TIM_FLAG_CC2);

//     // TIM_SelectMasterSlaveMode(TIM4, TIM_MasterSlaveMode_Enable);
//     // TIM_SelectOutputTrigger(TIM4, TIM_TRGOSource_OC1);
//     // timer2 output compate signal is connected to TRIGO
//     TIM_SelectOutputTrigger(TIM4, TIM_TRGOSource_OC2Ref);

//     // Enable channel 2 compate interrupt request
//     // TIM_IT_CC1 | TIM_IT_CC2
//     TIM_ITConfig(TIM4, TIM_IT_CC1 | TIM_IT_CC2, ENABLE);

//     // Enable output compare preload
//     // TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

//     // Enable ARR preload
//     // TIM_ARRPreloadConfig(TIM4, ENABLE);

//     // Enable update event
//     // TIM_ClearFlag(TIM4, TIM_FLAG_Update);
//     // TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE);

//     // we use preemption interrupts here,  BLDC Bridge switching and
//     // Hall has highest priority
//     NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
//     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
//     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//     NVIC_Init(&NVIC_InitStructure);

//     // -------------------
//     // HallSensor is now configured, if BLDC Timer is also configured
//     // after enabling timer 4
//     // the motor will start after next overflow of the hall timer because
//     // this generates the first startup motor cummutation event
//     TIM_Cmd(TIM4, ENABLE);
// }

// //void incCommutationDelay(void) { TIM4->CCR2 = (TIM4->CCR2) + 1; }

// //void decCommutationDelay(void) { TIM4->CCR2 = (TIM4->CCR2) - 1; }

// // ------------- HallSensor interrupt handler -----------------

// // this handles TIM4 irqs (from HallSensor)
// void TIM4_IRQHandler(void) {
//     if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET) {
//         TIM_ClearITPendingBit(MOTOR_TMC603_HALLENC_TIM, TIM_IT_CC1);
//         // calculate motor  speed or else with CCR1 values
//         hallccr1 = TIM4->CCR1;
//         ...
//     } else if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET) {
//         TIM_ClearITPendingBit(MOTOR_TMC603_HALLENC_TIM, TIM_IT_CC2);
//         // this interrupt handler is called AFTER the motor commutaton event
//         // is done
//         // after commutation the next motor step must be prepared
//         // use inline functions in irq handlers static __INLINE funct(..) {..}
//         BLDCMotorPrepareCommutation();
//     } else {
//         ; // this should not happen
//     }
// }