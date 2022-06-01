#pragma once

#include <cstdint>
#include <type_traits>

#include <mtl/algorithm/bitmask.hpp>

namespace mtl::hw {
    template <auto v_base_address, auto v_offset, class t_type> struct register_ {
        using type = t_type;
        constexpr static auto base_address = v_base_address;
        constexpr static auto offset = v_offset;
        constexpr static auto address = base_address + offset;

        template <class... t_parameters> inline static void write(t_parameters &&... parameters) noexcept {
            if constexpr ((std::is_integral<typename std::decay<t_parameters>::type>::value && ...)) {
                *reinterpret_cast<volatile type *>(address) = (parameters | ...);
            } else {
                *reinterpret_cast<volatile type *>(address) = (parameters.value() | ...);
            }
        }

        inline static void write(type value) noexcept { *reinterpret_cast<volatile type *>(address) = value; }

        inline static type read() noexcept { return *reinterpret_cast<volatile type *>(address); }

        inline static bool test(type value) noexcept { return *reinterpret_cast<volatile type *>(address) & value; }

        inline static void set(type value) noexcept { *reinterpret_cast<volatile type *>(address) |= value; }
    };

    template <class t_register, uint8_t v_start, uint8_t v_width> struct field {
        using register_ = t_register;
        using type = typename register_::type;
        constexpr static auto base_address = register_::base_address;
        constexpr static auto offset = register_::offset;
        constexpr static auto address = base_address + offset;
        constexpr static auto start = v_start;
        constexpr static auto width = v_width;
        constexpr static type mask
            = mtl::bitmask<mtl::bmp::underlying_type<type>,
                           mtl::bmp::modify<mtl::bmp::operators::set_from<start, start + width>>>::value;

        template <class t_parameter> static void set(t_parameter &&value) {
            if constexpr (std::is_integral<std::decay<t_parameter>>::value) {
                *reinterpret_cast<volatile type *>(address)
                    = *reinterpret_cast<volatile type *>(address) & ~mask | value;
            } else {
                *reinterpret_cast<volatile type *>(address)
                    = *reinterpret_cast<volatile type *>(address) & ~mask | value.value();
            }
        }

        static void clear() {
            *reinterpret_cast<volatile type *>(address) = *reinterpret_cast<volatile type *>(address) & ~mask;
        }

        template <class t_parameter> static bool test(t_parameter &&value) {
            if constexpr (std::is_integral<std::decay<t_parameter>>::value) {
                return (*reinterpret_cast<volatile type *>(address) & mask) == value;
            } else {
                return (*reinterpret_cast<volatile type *>(address) & mask) == value.value();
            }
        }

        static type get() { return (*reinterpret_cast<volatile type *>(address) & mask) >> start; }
    };

    template <class t_field> class option {
    public:
        using field = t_field;
        using type = typename field::type;
        constexpr static auto base_address = field::base_address;
        constexpr static auto offset = field::offset;
        constexpr static auto address = base_address + offset;
        constexpr static auto start = field::start;
        constexpr static auto width = field::width;
        constexpr static type mask = field::mask;

        constexpr option(type &&v) : m_value(v) {}

        constexpr operator type() const { return m_value; }

        constexpr type value() const { return m_value << start; }

    private:
        const type m_value;
    };
} // namespace mtl::hw
