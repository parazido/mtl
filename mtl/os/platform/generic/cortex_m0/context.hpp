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

        static void save() noexcept {
            asm volatile("mrs	r0, psp");
            asm volatile("sub	r0, #16");
            asm volatile("stmia	r0!, {r4-r7}");
            asm volatile("mov	r4, r8");
            asm volatile("mov	r5, r9");
            asm volatile("mov	r6, r10");
            asm volatile("mov	r7, r11");
            asm volatile("sub	r0, #32");
            asm volatile("stmia	r0!, {r4-r7}");
            asm volatile("sub	r0, #16");
            asm volatile("msr   psp, r0");
        }

        static void load() noexcept {
            asm volatile("mrs   r0, psp");
            asm volatile("ldmia	r0!, {r4-r7}");
            asm volatile("mov	r8, r4");
            asm volatile("mov	r9, r5");
            asm volatile("mov	r10, r6");
            asm volatile("mov	r11, r7");
            asm volatile("ldmia	r0!, {r4-r7}");
            asm volatile("msr	psp, r0");
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
