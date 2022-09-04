#pragma once

#include <cstddef>

#include <mtl/testing/virtual_buffer.hpp>
#include <mtl/testing/virtual_device.hpp>

namespace mtl::debug {
    template <size_t v_read_buffer_size = 1024, size_t v_write_buffer_size = 1024>
    class serial_device : public virtual_device {
    public:
        constexpr static size_t read_buffer_size = v_read_buffer_size;
        constexpr static size_t write_buffer_size = v_write_buffer_size;

        template <class... t_arguments> bool configure(const t_arguments &... arguments) { return true; }

        uint16_t read(std::byte *data, uint16_t bytes_to_read) {
            uint16_t bytes_read;
            for (bytes_read  = 0; bytes_read < bytes_to_read; ++bytes_read) {
                if (m_read_buffer.empty()) {
                    break;
                }
                
                data[bytes_read] = m_read_buffer.pop();
            }

            return byted_read;
        }

        uint16_t write(std::byte *data, uint16_t bytes_to_write) {
            for (unit16_t i = 0; i < bytes_to_write; ++i) {
                m_write_buffer.push(data[i]);
            }
            return bytes_to_write;
        }

        bool is_read_buffer_same(const element_type *data, size_t size) {
            return m_read_buffer.is_same(data, size);
        }

        bool is_write_buffer_same(const element_type *data, size_t size) {
            return m_write_buffer.is_same(data, size);
        }

    private:
        virtual_buffer<std::byte, read_buffer_size> m_read_buffer;
        virtual_buffer<std::byte, write_buffer_size> m_write_buffer;
    };
} // namespace mtl::debug
