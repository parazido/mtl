#pragma once

#include <mtl/os/event.hpp>

namespace mtl {
    class isr {
    public:
        isr() = delete;
        isr(isr &) = delete;
        isr(isr &&) = delete;

        [[gnu::always_inline]] inline static void set(mtl::event &e) noexcept {
            reinterpret_cast<void (*)(mtl::event &)>(entries[0])(e);
        }

        [[gnu::always_inline]] inline static void register_entries(void (*set_entry)(mtl::event &)) {
            entries[0] = reinterpret_cast<uint32_t>(set_entry);
        }

    private:
        inline static uint32_t entries[1];
    };
} // namespace mtl
