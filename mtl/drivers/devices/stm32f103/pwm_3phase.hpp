#pragma once

#include <mtl/common/parameters.hpp>
#include <mtl/drivers/common.hpp>
#include <mtl/hw/afio.hpp>
#include <mtl/hw/timer.hpp>
#include <mtl/units/units.hpp>

namespace mtl::drivers {
    namespace pwm_3phase_ {
        template <class t_phase_a, class t_phase_a_n, class t_phase_b, class t_phase_b_n, class t_phase_c,
                  class t_phase_c_n>
        struct io {
            using phase_a = t_phase_a;
            using phase_a_n = t_phase_a_n;
            using phase_b = t_phase_b;
            using phase_b_n = t_phase_b_n;
            using phase_c = t_phase_c;
            using phase_c_n = t_phase_c_n;
        };
    } // namespace pwm_3phase_

    template <class... t_parameters> class pwm_3phase {
    public:
        using sys = typename mtl::parameters<t_parameters...>::find_type<mtl::sys>::type;
        using device_id = typename mtl::parameters<t_parameters...>::find_type<mtl::drivers::device_id>::type::type;
        using device = mtl::hw::timer<device_id>;
        using io = typename mtl::parameters<t_parameters...>::find_type<pwm_3phase_::io>::type;

        constexpr static uint16_t arr = 8000;

        bool open(float frequency) {
            // Initialize IOs.
            m_io_a.open();
            m_io_a_n.open();
            m_io_b.open();
            m_io_b_n.open();
            m_io_c.open();
            m_io_c_n.open();

            // Power timer up.
            sys::template enable<device_id>();

            // Initialize basic configuration.
            float in_frequency = sys::template frequency<device_id>();
            float floating_divider = in_frequency / frequency;
            uint16_t divider = static_cast<uint16_t>(floating_divider);
            device::cnt::write(0);
            device::psc::write(0);
            device::arr::write(arr);
            device::cr1::write(device::cr1::ckd::nomul, device::cr1::arpe::enabled, device::cr1::cms::edge,
                               device::cr1::dir::upcount, device::cr1::opm::disabled, device::cr1::urs::any,
                               device::cr1::udis::uev_enabled);

            device::cr2::write(0);
            device::smcr::write(0);
            // device::dier::write(0);
            device::ccr1::write(0);
            device::ccr2::write(0);
            device::ccr3::write(0);

            device::ccer::write(device::ccer::cc1e::disabled, device::ccer::cc1p::non_inverted, device::ccer::cc1ne::disabled,
                                device::ccer::cc1np::non_inverted, device::ccer::cc2e::disabled, device::ccer::cc2p::non_inverted,
                                device::ccer::cc2ne::disabled, device::ccer::cc2np::non_inverted, device::ccer::cc3e::disabled,
                                device::ccer::cc3p::non_inverted, device::ccer::cc3ne::disabled, device::ccer::cc3np::non_inverted);

            device::rcr::write(0);
            device::bdtr::write(7);
            device::bdtr::moe::set(device::bdtr::moe::enabled);
            // device::dcr::write(0);
            // device::dmar::write(0);

            // Enable timer.
            device::cr1::cen::set(device::cr1::cen::enabled);
            return true;
        }

        inline void update_duty(float duty) {
            m_duty = static_cast<uint16_t>(duty * arr + 0.5);
            device::ccr1::write(m_duty);
            device::ccr2::write(m_duty);
            device::ccr3::write(m_duty);
        }

        inline void update_position(uint8_t index) {
            if (m_index != index) {
                m_index = index;
                update_bridge_configuration();
            }
        }

    private:
        void update_bridge_configuration() {
            // uint16_t newhallpos = ((GPIO_ReadInputData(GPIOD) & 0x7000) >> 12);
            bool bh1 = bldc_bridge_state_table[m_index][0];
            bool bl1 = bldc_bridge_state_table[m_index][1];
            bool bh2 = bldc_bridge_state_table[m_index][2];
            bool bl2 = bldc_bridge_state_table[m_index][3];
            bool bh3 = bldc_bridge_state_table[m_index][4];
            bool bl3 = bldc_bridge_state_table[m_index][5];

            if (bh1) {
                device::ccmr1::oc1m::set(device::ccmr1::oc1m::pwm1);
                device::ccer::cc1e::set(device::ccer::cc1e::enabled);
                device::ccer::cc1ne::set(device::ccer::cc1ne::enabled);
            } else {
                device::ccer::cc1e::set(device::ccer::cc1e::disabled);
                if (bl1) {
                    device::ccmr1::oc1m::set(device::ccmr1::oc1m::force_active);
                    device::ccer::cc1ne::set(device::ccer::cc1ne::enabled);
                } else {
                    device::ccer::cc1ne::set(device::ccer::cc1ne::disabled);
                }
            }

            if (bh2) {
                device::ccmr1::oc2m::set(device::ccmr1::oc2m::pwm1);
                device::ccer::cc2e::set(device::ccer::cc2e::enabled);
                device::ccer::cc2ne::set(device::ccer::cc2ne::enabled);
            } else {
                device::ccer::cc2e::set(device::ccer::cc2e::disabled);
                if (bl2) {
                    device::ccmr1::oc2m::set(device::ccmr1::oc2m::force_active);
                    device::ccer::cc2ne::set(device::ccer::cc2ne::enabled);
                } else {
                    device::ccer::cc2ne::set(device::ccer::cc2ne::disabled);
                }
            }

            if (bh3) {
                device::ccmr2::oc3m::set(device::ccmr2::oc3m::pwm1);
                device::ccer::cc3e::set(device::ccer::cc3e::enabled);
                device::ccer::cc3ne::set(device::ccer::cc3ne::enabled);
            } else {
                device::ccer::cc3e::set(device::ccer::cc3e::disabled);
                if (bl3) {
                    device::ccmr2::oc3m::set(device::ccmr2::oc3m::force_active);
                    device::ccer::cc3ne::set(device::ccer::cc3ne::enabled);
                } else {
                    device::ccer::cc3ne::set(device::ccer::cc3ne::disabled);
                }
            }
        }

    private:
        uint16_t m_index = 0;
        uint16_t m_duty = 0;

        mtl::drivers::gpio<
            sys, mtl::hw::link<mtl::hw::device_signal<device_id, mtl::hw::signal::ch1_oc>, typename io::phase_a>>
            m_io_a;
        mtl::drivers::gpio<
            sys, mtl::hw::link<mtl::hw::device_signal<device_id, mtl::hw::signal::ch1n_oc>, typename io::phase_a_n>>
            m_io_a_n;
        mtl::drivers::gpio<
            sys, mtl::hw::link<mtl::hw::device_signal<device_id, mtl::hw::signal::ch2_oc>, typename io::phase_b>>
            m_io_b;
        mtl::drivers::gpio<
            sys, mtl::hw::link<mtl::hw::device_signal<device_id, mtl::hw::signal::ch2n_oc>, typename io::phase_b_n>>
            m_io_b_n;
        mtl::drivers::gpio<
            sys, mtl::hw::link<mtl::hw::device_signal<device_id, mtl::hw::signal::ch3_oc>, typename io::phase_c>>
            m_io_c;
        mtl::drivers::gpio<
            sys, mtl::hw::link<mtl::hw::device_signal<device_id, mtl::hw::signal::ch3n_oc>, typename io::phase_c_n>>
            m_io_c_n;

        constexpr static bool bldc_bridge_state_table[8][6] = {
            {false, false, false, false, false, false}, // 0
            {false, true, true, false, false, false},   // 2
            {false, false, false, true, true, false},   // 4
            {false, true, false, false, true, false},   // 3
            {true, false, false, false, false, true},   // 6
            {false, false, true, false, false, true},   // 1
            {true, false, false, true, false, false},   // 5
            {false, false, false, false, false, false}, // 0
        };
    };
} // namespace mtl::drivers

#if 0
void configMotorBridgeTimer(void) {

// Chopper Frequency (PWM for the FETs)
// 18kHz was good in empiric tests
// ARR = SystemCoreClock / ChopperFreq
// ARR defines also the resolution of the Chopper PWM
#define BLDC_CHOPPER_PERIOD ((uint16_t)4000)



    

    // activate preloading the CCR register
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

    /* automatic output enable, break off, dead time ca. 200ns and

    // no lock of configuration */

    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;

    // DeadTime value n=1 bis 31: from 14ns to 1,7us
    // DeadTime value n=129 bis 159: from 1,7µs to 3,5ms
    // DeadTime value 7 => 98ns
    // ... see programmers reference manual

    // DeadTime[ns] = value * (1/SystemCoreFreq) (on 72MHz: 7 is 98ns)
    TIM_BDTRInitStructure.TIM_DeadTime = 7; // 98ns

    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;

    // enabel this if you use emergency stop signal
    // TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
    // TIM_BDTRInitStructure.TIM_BreakPolarity = MOTOR_TMC603_EMSTOP_POLARITY;

    TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;

    TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

    // preload ARR register
    TIM_CCPreloadControl(TIM1, ENABLE);

    // activate COM (Commutation) Event from Slave (HallSensor timer)
    // through TRGI
    enableHallCommutateSignal();

    // Internal connection from Hall/Enc Timer to Motor Timer
    // eg. TIM1 (BLDC Motor Timer) is Slave of TIM3 (Hall Timer)
    // Internal connection from Hall/Enc Timer to Motor Timer

    // Choose carefully from the following possible combination
    // check programmers reference manual
    // TIM_SelectInputTrigger(TIM1, TIM_TS_ITR0);
    // MotorTimer = TIM1, HallTimer = TIM5
    // TIM_SelectInputTrigger(TIM1, TIM_TS_ITR1);
    // MotorTimer = TIM1, HallTimer = TIM2
    // TIM_SelectInputTrigger(TIM1, TIM_TS_ITR2);
    // MotorTimer = TIM1, HallTimer = TIM3
    TIM_SelectInputTrigger(TIM1, TIM_TS_ITR3);
    // MotorTimer = TIM1, HallTimer = TIM4
    // TIM_SelectInputTrigger(TIM8, TIM_TS_ITR0);
    // MotorTimer = TIM8, HallTimer = TIM1
    // TIM_SelectInputTrigger(TIM8, TIM_TS_ITR1);
    // MotorTimer = TIM8, HallTimer = TIM2
    // TIM_SelectInputTrigger(TIM8, TIM_TS_ITR2);
    // MotorTimer = TIM8, HallTimer = TIM4
    // TIM_SelectInputTrigger(TIM8, TIM_TS_ITR3);
    // MotorTimer = TIM8, HallTimer = TIM5

    // Enable interrupt, motor commutation has high piority and has
    // a higher subpriority then the hall sensor
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_IRQn;

    // highest priority
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;

    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    // highest priority
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);

    // Interrupt for hardwired EmergencyStop
    (if needed)
        // Timer 1 Motor Emergency Break Input
        // NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_IRQn;
        // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
        // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        // NVIC_Init(&NVIC_InitStructure);

        // --------- activate the bldc bridge ctrl. ----------
        // in a project this will be done late after complete
        // configuration of other peripherie

        // enable COM (commutation) IRQ
        TIM_ITConfig(TIM1, TIM_IT_COM, ENABLE);

    // enable motor timer
    TIM_Cmd(TIM1, ENABLE);

    // enable motor timer main output (the bridge signals)
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

// enable the connection between HallTimer and MotorTimer
void enableHallCommutateSignal() { TIM_SelectCOM(TIM1, ENABLE); }

// disable the connection between HallTimer and MotorTimer
void disableHallCommutateSignal() { TIM_SelectCOM(TIM1, DISABLE); }


// This function handles motor timer trigger and commutation interrupts
// can be used for calculation...
void TIM1_TRG_COM_IRQHandler(void) {
    TIM_ClearITPendingBit(TIM1, TIM_IT_COM);
    // commutationCount++;
}

#endif