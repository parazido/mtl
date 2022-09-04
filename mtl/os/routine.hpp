#pragma once

#include <cstddef>
#include <cstdint>

//#include <mtl/os/context.hpp>

namespace mtl {
    namespace detail {
        template <class...> struct deduce_signature;

        template <class t_owner> struct deduce_signature<void (t_owner::*)()> { using owner = t_owner; };
    } // namespace detail

    enum class routine_state : uint8_t { active = 1, suspended = 2, terminated = 128 };

    template <auto v_pointer, size_t v_stack_size = 16> class routine {
    public:
        using owner_type = typename detail::deduce_signature<decltype(v_pointer)>::owner;
        constexpr static size_t stack_size = v_stack_size;

        static void call(owner_type *object) { (object->*v_pointer)(); }

        // private:
        // TODO: remove device dependent part.
        alignas(sizeof(uint32_t) * 2) uint32_t m_stack[stack_size + 128]; // mtl::context::stack_frame_size];
    };

    template <class...> struct routines {
        using next = void;
        using type = void;
        constexpr static size_t size = 0;
    };

    template <class t_first, class... t_rest> struct routines<t_first, t_rest...> {
        using next = routines<t_rest...>;
        using type = t_first;
        constexpr static size_t size = routines<t_rest...>::size + 1;

        type routine;
        next next_routines;
    };

    template <class t_last> struct routines<t_last> {
        using next = routines<>;
        using type = t_last;
        constexpr static size_t size = routines<>::size + 1;

        type routine;
    };
} // namespace mtl
