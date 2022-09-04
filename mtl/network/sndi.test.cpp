#include <mtl/network/sndi.hpp>
#include <mtl/testing/simple_serial_device.hpp>

#include <catch2/catch.hpp>

using sndi_registers = mtl::network::sndi_::registers<
    mtl::network::sndi_::register_<uint8_t>,
    mtl::network::sndi_::register_<uint16_t, mtl::network::sndi_::access_type::read_only, 0x0ff0>,
    mtl::network::sndi_::register_<float, mtl::network::sndi_::access_type::write_only>>;

using sndi_device = mtl::testing::simple_serial_device;

TEST_CASE("Initial register values match predefined ones.") {
    mtl::network::sndi<sndi_device, sndi_registers> interface();
    CHECK(interface.read<0>() == 0);
    CHECK(interface.read<1>() == 0x0ff0);
    CHECK(interface.read<2>() == 0x0ff0);
}

TEST_CASE("Writing to registers generates valid serial sequence.") {
    mtl::network::sndi<sndi_device, sndi_registers> interface();
    
    SECTION("Writing using static addressing (0)") {
        interface.write_register<0>(0x05);
        const std::byte serial_data[] = {0x01, 0x00, 0x05, 0x00, 0x00, 0x00};
        CHECK(interface.is_write_buffer_same(serial_data, sizeof(serial_data)));
    }
    
    SECTION("Writing to read only register using static addressing (1)") {
        interface.write_register<1>(0x0205);
        const std::byte serial_data[] = {};
        CHECK(interface.is_write_buffer_same(serial_data, sizeof(serial_data)));
    }

    SECTION("Writing to write only register using static addressing (2)") {
        interface.write_register<1>(0x0205);
        const std::byte serial_data[] = {};
        CHECK(interface.is_write_buffer_same(serial_data, sizeof(serial_data)));
    }
}
