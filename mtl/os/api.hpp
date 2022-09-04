#pragma once

#include <mtl/os/event.hpp>

namespace mtl {
    class api {
    public:
        api() = delete;
        api(api &) = delete;
        api(api &&) = delete;

        inline static void wait(mtl::event &e) noexcept { reinterpret_cast<void (*)(mtl::event &)>(entries[0])(e); }

        inline static void set(mtl::event &e) noexcept { reinterpret_cast<void (*)(mtl::event &)>(entries[1])(e); }

        inline static void register_entries(void (*wait_entry)(mtl::event &), void (*set_entry)(mtl::event &)) {
            entries[0] = reinterpret_cast<uint32_t>(wait_entry);
            entries[1] = reinterpret_cast<uint32_t>(set_entry);
        }

    private:
        inline static uint32_t entries[2];
    };
} // namespace mtl
