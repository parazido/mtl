#pragma once

#include <atomic>
#include <cstdint>

namespace mtl {
    struct event {
        uint8_t m_routine;
        std::atomic<bool> m_flag = false;
    };
} // namespace mtl
