#include <type_traits>
#include <catch2/catch.hpp>
#include <mtl/algorithm/bitmask.hpp>


TEST_CASE("Default mask is empty.") {
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint8_t>>::value == 0);
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint16_t>>::value == 0);
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint32_t>>::value == 0);
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint64_t>>::value == 0);
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int8_t>>::value == 0);
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int16_t>>::value == 0);
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int32_t>>::value == 0);
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int64_t>>::value == 0);
}

TEST_CASE("Initialized mask is equal to the `raw` value.") {
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint8_t>, mtl::bmp::raw<0xa5>>::value == static_cast<uint8_t>(0xa5));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint16_t>, mtl::bmp::raw<0xa5a5>>::value == static_cast<uint16_t>(0xa5a5));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint32_t>, mtl::bmp::raw<0xa5a5a5a5>>::value == static_cast<uint32_t>(0xa5a5a5a5));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint64_t>, mtl::bmp::raw<0xa5a5a5a5a5a5a5a5>>::value == static_cast<uint64_t>(0xa5a5a5a5a5a5a5a5));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int8_t>, mtl::bmp::raw<0xa5>>::value == static_cast<int8_t>(0xa5));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int16_t>, mtl::bmp::raw<0xa5a5>>::value == static_cast<int16_t>(0xa5a5));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int32_t>, mtl::bmp::raw<0xa5a5a5a5>>::value == static_cast<int32_t>(0xa5a5a5a5));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int64_t>, mtl::bmp::raw<0xa5a5a5a5a5a5a5a5>>::value == static_cast<int64_t>(0xa5a5a5a5a5a5a5a5));
}

TEST_CASE("Operator `set` modifies mask properly.") {
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint8_t>, mtl::bmp::modify<mtl::bmp::operators::set>>::value == static_cast<uint8_t>(0xff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint16_t>, mtl::bmp::modify<mtl::bmp::operators::set>>::value == static_cast<uint16_t>(0xffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint32_t>, mtl::bmp::modify<mtl::bmp::operators::set>>::value == static_cast<uint32_t>(0xffffffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint64_t>, mtl::bmp::modify<mtl::bmp::operators::set>>::value == static_cast<uint64_t>(0xffffffffffffffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int8_t>, mtl::bmp::modify<mtl::bmp::operators::set>>::value == static_cast<int8_t>(0xff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int16_t>, mtl::bmp::modify<mtl::bmp::operators::set>>::value == static_cast<int16_t>(0xffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int32_t>, mtl::bmp::modify<mtl::bmp::operators::set>>::value == static_cast<int32_t>(0xffffffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int64_t>, mtl::bmp::modify<mtl::bmp::operators::set>>::value == static_cast<int64_t>(0xffffffffffffffff));
}

TEST_CASE("Operator `set_from` modifies mask properly.") {
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint8_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<0>>>::value == static_cast<uint8_t>(0xff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint8_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<4>>>::value == static_cast<uint8_t>(0xf0));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint8_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<8>>>::value == static_cast<uint8_t>(0x00));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint16_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<0>>>::value == static_cast<uint16_t>(0xffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint16_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<8>>>::value == static_cast<uint16_t>(0xff00));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint16_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<16>>>::value == static_cast<uint16_t>(0x0000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint32_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<0>>>::value == static_cast<uint32_t>(0xffffffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint32_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<16>>>::value == static_cast<uint32_t>(0xffff0000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint32_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<32>>>::value == static_cast<uint32_t>(0x00000000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint64_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<0>>>::value == static_cast<uint64_t>(0xffffffffffffffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint64_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<32>>>::value == static_cast<uint64_t>(0xffffffff00000000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint64_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<64>>>::value == static_cast<uint64_t>(0x0000000000000000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int8_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<0>>>::value == static_cast<int8_t>(0xff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int8_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<4>>>::value == static_cast<int8_t>(0xf0));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int8_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<8>>>::value == static_cast<int8_t>(0x00));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int16_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<0>>>::value == static_cast<int16_t>(0xffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int16_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<8>>>::value == static_cast<int16_t>(0xff00));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int16_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<16>>>::value == static_cast<int16_t>(0x0000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int32_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<0>>>::value == static_cast<int32_t>(0xffffffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int32_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<16>>>::value == static_cast<int32_t>(0xffff0000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int32_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<32>>>::value == static_cast<int32_t>(0x00000000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int64_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<0>>>::value == static_cast<int64_t>(0xffffffffffffffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int64_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<32>>>::value == static_cast<int64_t>(0xffffffff00000000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int64_t>, mtl::bmp::modify<mtl::bmp::operators::set_from<64>>>::value == static_cast<int64_t>(0x0000000000000000));
}

TEST_CASE("Operator `set_to` modifies mask properly.") {
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint8_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<0>>>::value == static_cast<uint8_t>(0x00));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint8_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<4>>>::value == static_cast<uint8_t>(0x0f));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint8_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<8>>>::value == static_cast<uint8_t>(0xff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint16_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<0>>>::value == static_cast<uint16_t>(0x0000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint16_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<8>>>::value == static_cast<uint16_t>(0x00ff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint16_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<16>>>::value == static_cast<uint16_t>(0xffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint32_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<0>>>::value == static_cast<uint32_t>(0x00000000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint32_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<16>>>::value == static_cast<uint32_t>(0x0000ffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint32_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<32>>>::value == static_cast<uint32_t>(0xffffffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint64_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<0>>>::value == static_cast<uint64_t>(0x0000000000000000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint64_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<32>>>::value == static_cast<uint64_t>(0x00000000ffffffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<uint64_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<64>>>::value == static_cast<uint64_t>(0xffffffffffffffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int8_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<0>>>::value == static_cast<int8_t>(0x00));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int8_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<4>>>::value == static_cast<int8_t>(0x0f));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int8_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<8>>>::value == static_cast<int8_t>(0xff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int16_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<0>>>::value == static_cast<int16_t>(0x0000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int16_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<8>>>::value == static_cast<int16_t>(0x00ff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int16_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<16>>>::value == static_cast<int16_t>(0xffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int32_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<0>>>::value == static_cast<int32_t>(0x00000000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int32_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<16>>>::value == static_cast<int32_t>(0x0000ffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int32_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<32>>>::value == static_cast<int32_t>(0xffffffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int64_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<0>>>::value == static_cast<int64_t>(0x0000000000000000));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int64_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<32>>>::value == static_cast<int64_t>(0x00000000ffffffff));
    CHECK(mtl::bitmask<mtl::bmp::underlying_type<int64_t>, mtl::bmp::modify<mtl::bmp::operators::set_to<64>>>::value == static_cast<int64_t>(0xffffffffffffffff));
}