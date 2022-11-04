#pragma once

namespace mtl::control {
    class foc {
    public:
        void update() {
            // Get current speed, position and currents.
            m_speed = m_rotation_sensor.speed();
            m_position = m_rotation_sensor.position();
            m_current[0] = m_current_sensor.current();
            m_current[1] = m_current_sensor.current();

            // Current Clarke transform.
            // Current Park transform.

            // PID speed controller.

            // PI Id(0) controller.
            // PI Iq controller.

            // Inverse Park transform.
            // Inverse Clarke transform.

            // SVPWM.
        }

    private:
        float m_update_frequency;
        float m_current[2];
        float m_speed;
        float m_position;

        rotation_sensor m_rotation_sensor;
        current_sensor m_current_sensor;
    };
} // namespace mtl::control
