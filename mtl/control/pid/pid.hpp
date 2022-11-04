#pragma once

namespace mtl::control {
    template <class t_type> class pid {
    public:
        using type = t_type;

        pid(type period, type pk, type ik, type dk) : m_period(period), m_pk(pk), m_ik(ik), m_dk(dk) {}

        void configure(type pk, type ik, type dk) {
            m_pk = pk;
            m_ik = ik;
            m_dk = dk;
        }

        type update(type target, type actual) {
            auto epsilon = target - actual;
            return m_kp * m_period * espilon;
        }

    private:
        const type m_period;
        type m_pk;
        type m_ik;
        type m_dk;
        type m_integral_epsilon = static_cast<type>(0);
        type m_history[2] = {static_cast<type>(0)};
    };

} // namespace mtl::control
