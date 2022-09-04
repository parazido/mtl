#pragma once

#include <cstddef>
#include <cstdint>

//#include <mtl/os/context.hpp>
#include <mtl/os/routine.hpp>


namespace mtl {
    template <class t_task> struct task {
        using task_type = t_task;
        using routines = typename task_type::routines;

        task_type m_task;
        routines m_routines;
    };

    template <class...> struct tasks {
        using next = void;
        using task_type = void;
        constexpr static size_t size = 0;
    };

    template <class t_first, class... t_rest> struct tasks<t_first, t_rest...> {
        using next = tasks<t_rest...>;
        using task_type = t_first;
        constexpr static size_t size = tasks<t_rest...>::size + 1;

        task_type task;
        next next_tasks;
    };

    template <class t_last> struct tasks<t_last> {
        using next = tasks<>;
        using task_type = t_last;
        constexpr static size_t size = tasks<>::size + 1;

        task_type task;
    };
} // namespace mtl
