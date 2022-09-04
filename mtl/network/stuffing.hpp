#pragma once

#include <cstddef>
#include <cstdint>

namespace mtl::network {
    template <class t_device, std::byte v_start_byte, std::byte v_stop_byte, std::byte v_escape_byte>
    class byte_stuffing {
    public:
        using device = t_device;
        constexpr static std::byte start_byte = v_start_byte;
        constexpr static std::byte stop_byte = v_stop_byte;
        constexpr static std::byte escape_byte = v_escape_byte;

        struct read_result {
            bool full_frame;
            bool frame_size;
        }

        byte_stuffing() { m_device.open(); }

        void configure(uint8_t protocol) {

        }

        uint16_t write(std::byte *data, uint16_t length) {
            std::byte *start = data;
            std::byte *end = data;

            // Write start frame

            while (end <= data + length) {
                bool is_start_byte = *end == start_byte;
                bool is_stop_byte = *end == stop_byte;
                bool is_escape_byte = *end == escape_byte;
                bool is_end_byte = end == data + length;

                ++end;

                if (is_start_byte | is_end_byte | is_escape_byte | is_end_byte) {
                    m_device.write(start, static_cast<uint16_t>(end - start));
                    m_device.write(is_start_byte ? start_byte_replacement
                                                 : (is_stop_byte ? stop_byte_replacement : escape_byte_replacement),
                                   sizeof(escape_byte_replacement));
                    start = end = end + 1;
                    source = start_byte_replacement;
                    bytes_to_write = sizeof(start_byte_replacement);
                }
            }

            return length;
        }

        read_result read(std::byte *data, uint16_t length, bool is_new_frame = true) { 
            std::byte symbol;
            uint16_t total_bytes_read = 0;
            while (read_bytes < length) {
                auto bytes_read = m_device.read(&symbol, 1);
                if (bytes_read) {
                    
                }
            }
            return 0; 
        }

    private:
        uint8_t m_protocol = 0;
        device m_device;

        constexpr static std::byte start_byte_replacement[2] = {escape_byte, ~start_byte};
        constexpr static std::byte stop_byte_replacement[2] = {escape_byte, ~stop_byte};
        constexpr static std::byte escape_byte_replacement[2] = {escape_byte, ~escape_byte};
        static_assert(sizeof(start_byte_replacement) == sizeof(stop_byte_replacement)
                          && sizeof(stop_byte_replacement) == sizeof(escape_byte_replacement),
                      "All escape sequences must be of the same length!");
    };
} // namespace mtl::network
