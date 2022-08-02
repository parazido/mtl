#pragma once

#include <cstddef>

#include <mtl/buffers/common.hpp>
#include <mtl/traits/types.hpp>

namespace mtl::buffers {
    template <class t_element_type, size_t v_buffer_size> class pp_buffer {
    public:
        constexpr static size_t buffer_size = v_buffer_size;
        using element_type = t_element_type;
        using size_type =
            typename mtl::traits::types::pick<mtl::traits::typesp::min_integral_for_value<buffer_size>>::type;
        using memory_area = mtl::memory_area<element_type, size_type>;

        memory_area dma_read_area() {
            return memory_area(reinterpret_cast<element_type *>(&m_data[m_active_index]), buffer_size);
        }

        memory_area dma_write_area() { return {&m_data[(m_active_index + 1) & 0x01], buffer_size}; }

        void switch_buffers() { m_active_index = (m_active_index + 1) & 0x01; }

    private:
        uint8_t m_active_index = 0;
        element_type m_data[2][buffer_size];
    };
} // namespace mtl::buffers
