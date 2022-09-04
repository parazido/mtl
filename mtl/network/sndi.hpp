#pragma once

#include <atomic>
#include <cstddef>
#include <cstdint>

#include <mtl/containers/tuple.hpp>

// Simple network device interface protocol description.
// SNDI is master/slave protocol.
// Slave node specifies set of registers.
// Each register has 8-bit address. Each register can be uniquely identified by its address.
// Each register can be read/write, read or write only.
// Commands:
// - 0x01/register address (8-bits)/data (4 bytes): write to slave register.
// - 0x02/number of registers to write (n)/register address (8-bits)...(n)/data (4 bytes)...(n): write to the specified
// registers.
// - 0x03/register address (8-bits): read from the specified slave register.
// - 0x04/number of registers to read (n)/register address (8-bits)...(n): read from the specified slave registers.
// - 0x05: read full set of slave registers.
// Responses:
// - 0x43/register address (8-bits)/data (4 bytes): response to the 0x03 command.
// - 0x44/number of registers (n)/device address (8-bits)...(n)/data (4 bytes)...(n): response to the 0x04 command.
// - 0x45/data (4 bytes)...: response to the 0x05 command.

namespace mtl::network {

    namespace sndi_ {
        enum class state : uint8_t { ok = 0, error = 1 };

        enum class access_type : uint8_t {
            rw = 0,
            read_only = 1,
            write_only = 2,
        };

        // Register.
        template <class t_type, access_type v_access_type = access_type::rw,
                  t_type v_default_value = static_cast<t_type>(0)>
        class register_ {
        public:
            using type = t_type;
            constexpr static access_type access = v_access_type;
            constexpr static type default_value = v_default_value;

        private:
            type m_value = default_value;
        };

        // Registers.
        template <class... t_registers> class registers {
        public:
            using table = mtl::traits::list<t_registers...>;
            constexpr static uint8_t number_of_registers = sizeof...(t_registers);

            void write(uint8_t address, std::byte value[4]) {
                if (address < number_of_registers) {
                    auto access = m_access_types[address];
                    if (access == access_type::rw || access == access_type::write_only) {
                        m_table[address] = value;
                    }
                }
            }

            template <uint8_t v_address, typename std::enable_if<(v_address < number_of_registers), int>::type = 0>
            void write(const typename mtl::traits::find_by_index<v_address, table>::type::type &value) {
                auto access = m_access_types[v_address];
                if (access == access_type::rw || access == access_type::write_only) {
                    m_table[v_address] = reinterpret_cast<std::byte[4]>(value);
                }
            }

            uint32_t read(uint8_t address) {
                if (address < number_of_registers) {
                    auto access = m_access_types[address];
                    if (access == access_type::rw || access == access_type::read_only) {
                        return m_table[address];
                    }
                }
                return {0x00};
            }

            template <uint8_t v_address, typename std::enable_if<(v_address < number_of_registers), int>::type = 0>
            uint32_t read() const {
                auto access = m_access_types[v_address];
                if (access == access_type::rw || access == access_type::read_only) {
                    return reinterpret_cast<typename mtl::traits::find_by_index<v_address, table>::type::type>(
                        m_table[v_address]);
                }
                reinterpret_cast<typename mtl::traits::find_by_index<v_address, table>::type::type>(0);
            }

        private:
            std::atomic<uint32_t> m_table[number_of_registers] = {t_registers::default_value...};
            constexpr static access_type m_access_types[number_of_registers] = {t_registers::access_type...};
        };
    } // namespace sndi_

    namespace detail {
        // struct header

        namespace master {
            template <class t_communication_interface, class t_descriptor> class sndi {
            public:
                using communication_interface = t_communication_interface;
                using descriptor = t_descriptor;
                using registers = typename descriptor::registers;
                constexpr static bool is_master = true;

                sndi() {
                    // Open communication interface.
                    m_ci.open();
                }

                // Check current state.
                bool ok() const { return m_state == sndi_::state::ok; }

                // Read value from register.
                template <uint8_t v_register_id> auto read() const { return m_registers.read<v_register_id>(); }

                // Write value to register.
                template <uint8_t v_register_id>
                auto write_register(const typename mtl::traits::find_by_index<v_register_id, registers>::type &value) {
                    std::byte data[2 + sizeof(uint32_t)];
                    data[0] = 0x01;
                    data[1] = v_register_id;
                    uint32_t value = m_registers.read<v_register_id>();
                    for (uint8_t i = 0; i < sizeof(uint32_t); ++i) {
                        data[2 + i] = value[i];
                    }
                    m_ci.write(data);
                }

                // Send synchronization request.
                void sync() {
                    std::byte data[] = {0x05};
                    m_ci.write(data);
                }

                void process() {
                    std::byte cmd;
                    m_ci.read(&cmd, 1);

                    switch (cmd) {
                    case 0x43:
                    case 0x44:
                    case 0x45:
                    default:
                        return;
                    }

                    std::byte data[4];
                    uint16_t bytes_read = 0;
                    while (bytes_read = m_ci.read()) {
                    }
                    for (;;) {
                        auto bytes_read = m_ci.read();
                        if (bytes_read) {
                        }
                    }
                }

            private:
                communication_interface m_ci;
                registers m_registers;
                sndi_::state m_state = sndi_::state::ok;
            };
        } // namespace master
    }     // namespace detail

    template <class t_communication_interface, class t_descriptor, bool v_is_master = false> class sndi {
    public:
        using communication_interface = t_communication_interface;
        using descriptor = t_descriptor;
        using devices = typename descriptor::devices;
        constexpr static bool is_master = v_is_master;

        sndi() {
            // Open communication interface.
            m_ci.open();
        }

        bool ok() const { return m_state == sndi_::state::ok; }

        template <uint8_t v_device_id, uint8_t v_register_id> auto read() const {
            return mtl::get<v_register_id>(mtl::get<v_device_id>(m_devices)).load();
        }

        template <uint8_t v_device_id, uint8_t v_register_id, class t_type> auto write(const t_type &value) {
            if constexpr (is_master) {
                using value_type = typename mtl::traits::find_by_index<
                    v_register_id, typename mtl::traits::find_by_index<v_device_id, devices::types>::type>::type;
                static_assert(std::is_same<value_type, t_type>::value, "Value type must match register type.");
                std::byte data[3 + sizeof(value_type)];
                data[0] = 0x01;
                data[1] = v_device_id;
                data[2] = v_register_id;
                for (uint8_t i = 0; i < sizeof(value_type); ++i) {
                    data[3 + i] = reinterpret_cast<const std::byte *>(&value)[i];
                }
                m_ci.write(0x01, data);
            }

            return mtl::get<v_register_index>(mtl::get<v_device_id>(m_devices)).exchange(value);
        }

        void sync() {
            if constexpr (is_master) {
                std::byte data[] = {0x05, 0x00};
                m_ci.write(0x01, data);
            } else {
                std::byte data[2 + sizeof(devices)] =
            }
        }

        void loop() {
            for (;;) {
                auto bytes_read = m_ci.read();
                if (bytes_read) {
                }
            }
        }

    private:
        communication_interface m_ci;
        devices m_devices;
        sndi_::state m_state = sndi_::state::ok;
    };
} // namespace mtl::network
