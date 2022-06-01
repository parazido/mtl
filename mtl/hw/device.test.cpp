#include <type_traits>

#include <mtl/hw/device.hpp>

#include <catch2/catch.hpp>

struct d {
    constexpr static uint32_t base_address = 0x80000000;

    template <uint32_t v_offset, class t_type> using register_ = mtl::hw::register_<base_address, v_offset, t_type>;

    struct r : register_<0x80, uint32_t> {
        struct f : mtl::hw::field<r, 2, 2> {
            using option = mtl::hw::option<f>;
            constexpr static option o0 = 0;
            constexpr static option o1 = 1;
            constexpr static option o2 = 2;
            constexpr static option o3 = 3;
        };
    };
};

TEST_CASE("Types are valid.") {
    CHECK(std::is_same<d::r::type, uint32_t>::value);
    CHECK(std::is_same<d::r::f::type, uint32_t>::value);
    CHECK(std::is_same<d::r::f::option::type, uint32_t>::value);
}

TEST_CASE("Addresses are valid.") {
    CHECK(d::r::address == 0x80000080);
    CHECK(d::r::f::address == 0x80000080);
    CHECK(d::r::f::option::address == 0x80000080);
}

TEST_CASE("Masks are valid.") {
    CHECK(d::r::f::mask == 0x0000000c);
    CHECK(d::r::f::option::mask == 0x0000000c);
}

TEST_CASE("Values are valid after type casting.") {
    CHECK(static_cast<uint32_t>(d::r::f::o0) == 0x00000000);
    CHECK(static_cast<uint32_t>(d::r::f::o1) == 0x00000001);
    CHECK(static_cast<uint32_t>(d::r::f::o2) == 0x00000002);
    CHECK(static_cast<uint32_t>(d::r::f::o3) == 0x00000003);
}

TEST_CASE("Values are valid.") {
    CHECK(d::r::f::o0.value() == 0x00000000);
    CHECK(d::r::f::o1.value() == 0x00000004);
    CHECK(d::r::f::o2.value() == 0x00000008);
    CHECK(d::r::f::o3.value() == 0x0000000c);
}
