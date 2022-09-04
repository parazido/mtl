#pragma once

#include <cstdint>

namespace mtl {
    struct context {
        struct hardware_stack_frame {
            uint32_t r0;
            uint32_t r1;
            uint32_t r2;
            uint32_t r3;
            uint32_t r12;
            uint32_t lr;
            uint32_t pc;
            uint32_t psr;
        };

        struct software_stack_frame {
            uint32_t r4;
            uint32_t r5;
            uint32_t r6;
            uint32_t r7;
            uint32_t r8;
            uint32_t r9;
            uint32_t r10;
            uint32_t r11;
        };

        [[gnu::always_inline]] inline static void save() noexcept {
            asm volatile("mrs		r0, psp");
            asm volatile("stmdb	r0!, {r4-r11}");
            asm volatile("msr		psp, r0");
        }

        [[gnu::always_inline]] inline static void load() noexcept {
            asm volatile("mrs		r0, psp");
            asm volatile("ldmfd	r0!, {r4-r11}");
            asm volatile("msr		psp, r0");
        }

        [[gnu::always_inline]] inline static uint32_t read_system_stack_pointer() noexcept {
            uint32_t result;
            asm volatile("mrs %0, msp" : "=r"(result));
            return result;
        }

        [[gnu::always_inline]] inline static uint32_t read_routine_stack_pointer() noexcept {
            uint32_t result;
            asm volatile("mrs %0, psp" : "=r"(result));
            return result;
        }

        [[gnu::always_inline]] inline static void write_routine_stack_pointer(uint32_t stack_pointer) noexcept {
            asm volatile("msr psp, %0" : : "r"(stack_pointer));
        }

        constexpr static uint32_t hardware_stack_frame_size = sizeof(hardware_stack_frame);
        constexpr static uint32_t software_stack_frame_size = sizeof(software_stack_frame);
        constexpr static uint32_t stack_frame_size = hardware_stack_frame_size + software_stack_frame_size;
    };
} // namespace mtl
