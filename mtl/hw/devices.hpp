#pragma once

#include <cstdint>

namespace mtl::hw {
    template <class t_device, class t_signal = void> struct device_signal {
        using device = t_device;
        using signal = t_signal;
    };

    template <class t_port, uint8_t v_index> struct io {
        using port = t_port;
        constexpr static uint8_t index = v_index;
    };

    template <class t_device_signal, class t_io> struct link {
        using device_signal = t_device_signal;
        using io = t_io;
    };
} // namespace mtl::hw
