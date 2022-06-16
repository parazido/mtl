#pragma once

#include <type_traits>

namespace mtl::units {
    // Duration.
    class duration {
    public:
        using underlying_type = unsigned long long;

        constexpr duration() : m_value(0) {}
        constexpr duration(underlying_type value) : m_value(value) {}
        constexpr duration(long double value) : m_value(static_cast<underlying_type>(value * 1000000000.0)) {}

        constexpr bool operator==(const duration &other) const { return m_value == other.m_value; }

        constexpr bool operator<(const duration &other) const { return m_value < other.m_value; }

        constexpr bool operator<=(const duration &other) const { return m_value <= other.m_value; }

        constexpr bool operator>(const duration &other) const { return m_value > other.m_value; }

        constexpr bool operator>=(const duration &other) const { return m_value >= other.m_value; }

        constexpr bool operator!=(const duration &other) const { return m_value != other.m_value; }

        constexpr duration operator+(const duration &other) const { return duration(m_value + other.m_value); }

        constexpr duration operator-(const duration &other) const { return duration(m_value - other.m_value); }

        constexpr duration operator*(double factor) const {
            return duration(static_cast<underlying_type>(static_cast<double>(m_value) * factor));
        }

        template <class t_type,
                  typename std::enable_if<std::is_integral<t_type>::value && std::is_unsigned<t_type>::value, int>::type
                  = 0>
        constexpr duration operator*(t_type factor) const {
            return duration(m_value * factor);
        }

        constexpr duration operator/(double factor) const {
            return duration(static_cast<underlying_type>(static_cast<double>(m_value) / factor));
        }

        template <class t_type,
                  typename std::enable_if<std::is_integral<t_type>::value && std::is_unsigned<t_type>::value, int>::type
                  = 0>
        constexpr duration operator/(t_type factor) const {
            return duration(m_value / factor);
        }

    private:
        underlying_type m_value;
    };

    namespace literals {
        constexpr mtl::units::duration operator""_ns(mtl::units::duration::underlying_type value) {
            return mtl::units::duration(value);
        }

        constexpr mtl::units::duration operator""_ns(long double value) {
            return mtl::units::duration(static_cast<mtl::units::duration::underlying_type>(value));
        }

        constexpr mtl::units::duration operator""_us(mtl::units::duration::underlying_type value) {
            return mtl::units::duration(value * 1000);
        }

        constexpr mtl::units::duration operator""_us(long double value) {
            return mtl::units::duration(static_cast<mtl::units::duration::underlying_type>(value * 1000.0));
        }

        constexpr mtl::units::duration operator""_ms(mtl::units::duration::underlying_type value) {
            return mtl::units::duration(value * 1000000);
        }

        constexpr mtl::units::duration operator""_ms(long double value) {
            return mtl::units::duration(static_cast<mtl::units::duration::underlying_type>(value * 1000000.0));
        }

        constexpr mtl::units::duration operator""_s(mtl::units::duration::underlying_type value) {
            return mtl::units::duration(value * 1000000000);
        }

        constexpr mtl::units::duration operator""_s(long double value) {
            return mtl::units::duration(static_cast<mtl::units::duration::underlying_type>(value * 1000000000.0));
        }

        constexpr mtl::units::duration operator""_m(mtl::units::duration::underlying_type value) {
            return mtl::units::duration(value * 1000000000 * 60);
        }

        constexpr mtl::units::duration operator""_m(long double value) {
            return mtl::units::duration(
                static_cast<mtl::units::duration::underlying_type>(value * 1000000000.0 * 60.0));
        }

        constexpr mtl::units::duration operator""_h(mtl::units::duration::underlying_type value) {
            return mtl::units::duration(value * 1000000000 * 60 * 60);
        }

        constexpr mtl::units::duration operator""_h(long double value) {
            return mtl::units::duration(
                static_cast<mtl::units::duration::underlying_type>(value * 1000000000.0 * 60.0 * 60.0));
        }
    } // namespace literals

    class frequency {
    public:
        using underlying_type = unsigned long long;

        constexpr frequency() : m_value(0) {}
        constexpr frequency(underlying_type value) : m_value(value) {}
        constexpr frequency(long double value) : m_value(static_cast<underlying_type>(value * 1000000000.0)) {}

        constexpr bool operator==(const frequency &other) const { return m_value == other.m_value; }

        constexpr bool operator<(const frequency &other) const { return m_value < other.m_value; }

        constexpr bool operator<=(const frequency &other) const { return m_value <= other.m_value; }

        constexpr bool operator>(const frequency &other) const { return m_value > other.m_value; }

        constexpr bool operator>=(const frequency &other) const { return m_value >= other.m_value; }

        constexpr bool operator!=(const frequency &other) const { return m_value != other.m_value; }

        constexpr frequency operator+(const frequency &other) const { return frequency(m_value + other.m_value); }

        constexpr frequency operator-(const frequency &other) const { return frequency(m_value - other.m_value); }

        constexpr frequency operator*(double factor) const {
            return frequency(static_cast<underlying_type>(static_cast<double>(m_value) * factor));
        }

        template <class t_type,
                  typename std::enable_if<std::is_integral<t_type>::value && std::is_unsigned<t_type>::value, int>::type
                  = 0>
        constexpr frequency operator*(t_type factor) const {
            return frequency(m_value * factor);
        }

        constexpr frequency operator/(double factor) const {
            return frequency(static_cast<underlying_type>(static_cast<double>(m_value) / factor));
        }

        template <class t_type,
                  typename std::enable_if<std::is_integral<t_type>::value && std::is_unsigned<t_type>::value, int>::type
                  = 0>
        constexpr frequency operator/(t_type factor) const {
            return frequency(m_value / factor);
        }

    private:
        underlying_type m_value;
    };

    namespace literals {
        constexpr mtl::units::frequency operator""_nHz(mtl::units::frequency::underlying_type value) {
            return mtl::units::frequency(value);
        }

        constexpr mtl::units::frequency operator""_nHz(long double value) {
            return mtl::units::frequency(static_cast<mtl::units::frequency::underlying_type>(value));
        }

        constexpr mtl::units::frequency operator""_uHz(mtl::units::frequency::underlying_type value) {
            return mtl::units::frequency(value * 1000);
        }

        constexpr mtl::units::frequency operator""_uHz(long double value) {
            return mtl::units::frequency(static_cast<mtl::units::frequency::underlying_type>(value * 1000.0));
        }

        constexpr mtl::units::frequency operator""_mHz(mtl::units::frequency::underlying_type value) {
            return mtl::units::frequency(value * 1000000);
        }

        constexpr mtl::units::frequency operator""_mHz(long double value) {
            return mtl::units::frequency(static_cast<mtl::units::frequency::underlying_type>(value * 1000000.0));
        }

        constexpr mtl::units::frequency operator""_Hz(mtl::units::frequency::underlying_type value) {
            return mtl::units::frequency(value * 1000000000);
        }

        constexpr mtl::units::frequency operator""_Hz(long double value) {
            return mtl::units::frequency(static_cast<mtl::units::frequency::underlying_type>(value * 1000000000.0));
        }

        constexpr mtl::units::frequency operator""_kHz(mtl::units::frequency::underlying_type value) {
            return mtl::units::frequency(value * 1000000000000);
        }

        constexpr mtl::units::frequency operator""_kHz(long double value) {
            return mtl::units::frequency(static_cast<mtl::units::frequency::underlying_type>(value * 1000000000000.0));
        }

        constexpr mtl::units::frequency operator""_MHz(mtl::units::frequency::underlying_type value) {
            return mtl::units::frequency(value * 1000000000000000);
        }

        constexpr mtl::units::frequency operator""_MHz(long double value) {
            return mtl::units::frequency(
                static_cast<mtl::units::frequency::underlying_type>(value * 1000000000000000.0));
        }

        constexpr mtl::units::frequency operator""_GHz(mtl::units::frequency::underlying_type value) {
            return mtl::units::frequency(value * 1000000000000000000);
        }

        constexpr mtl::units::frequency operator""_GHz(long double value) {
            return mtl::units::frequency(
                static_cast<mtl::units::frequency::underlying_type>(value * 1000000000000000000.0));
        }
    } // namespace literals
} // namespace mtl::units

using namespace mtl::units::literals;
