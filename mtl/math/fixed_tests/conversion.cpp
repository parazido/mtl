#include <math.hpp>
#include <catch2/catch.hpp>



TEST_CASE("Unsigned fixed of 1 to 8 bits in size uses uint8_t as underlying type.") {
    // Unsigned:1:0.
    REQUIRE(std::is_same<uint8_t, mtl::math::fixed<false, 1, 0>::underlying_type>::value);
    // Unsigned:0:1.
    REQUIRE(std::is_same<uint8_t, mtl::math::fixed<false, 0, 1>::underlying_type>::value);
    // Unsigned:8:0.
    REQUIRE(std::is_same<uint8_t, mtl::math::fixed<false, 8, 0>::underlying_type>::value);
    // Unsigned:0:8.
    REQUIRE(std::is_same<uint8_t, mtl::math::fixed<false, 0, 8>::underlying_type>::value);
}


TEST_CASE("Unsigned fixed of 9 to 16 bits in size uses uint16_t as underlying type.") {
    // Unsigned:9:0.
    REQUIRE(std::is_same<uint16_t, mtl::math::fixed<false, 9, 0>::underlying_type>::value);
    // Unsigned:0:9.
    REQUIRE(std::is_same<uint16_t, mtl::math::fixed<false, 0, 9>::underlying_type>::value);
    // Unsigned:16:0.
    REQUIRE(std::is_same<uint16_t, mtl::math::fixed<false, 16, 0>::underlying_type>::value);
    // Unsigned:0:16.
    REQUIRE(std::is_same<uint16_t, mtl::math::fixed<false, 0, 16>::underlying_type>::value);
}


TEST_CASE("Unsigned fixed of 17 to 32 bits in size uses uint32_t as underlying type.") {
    // Unsigned:17:0.
    REQUIRE(std::is_same<uint32_t, mtl::math::fixed<false, 17, 0>::underlying_type>::value);
    // Unsigned:0:17.
    REQUIRE(std::is_same<uint32_t, mtl::math::fixed<false, 0, 17>::underlying_type>::value);
    // Unsigned:32:0.
    REQUIRE(std::is_same<uint32_t, mtl::math::fixed<false, 32, 0>::underlying_type>::value);
    // Unsigned:0:32.
    REQUIRE(std::is_same<uint32_t, mtl::math::fixed<false, 0, 32>::underlying_type>::value);
}


TEST_CASE("Unsigned fixed of 33 to 64 bits in size uses uint64_t as underlying type.") {
    // Unsigned:33:0.
    REQUIRE(std::is_same<uint64_t, mtl::math::fixed<false, 33, 0>::underlying_type>::value);
    // Unsigned:0:33.
    REQUIRE(std::is_same<uint64_t, mtl::math::fixed<false, 0, 33>::underlying_type>::value);
    // Unsigned:64:0.
    REQUIRE(std::is_same<uint64_t, mtl::math::fixed<false, 64, 0>::underlying_type>::value);
    // Unsigned:0:64.
    REQUIRE(std::is_same<uint64_t, mtl::math::fixed<false, 0, 64>::underlying_type>::value);
}

TEST_CASE("Signed fixed of 1 to 8 bits in size (including sign) uses int8_t as underlying type.") {
    // Signed:1:0.
    REQUIRE(std::is_same<int8_t, mtl::math::fixed<true, 1, 0>::underlying_type>::value);
    // Signed:0:1.
    REQUIRE(std::is_same<int8_t, mtl::math::fixed<true, 0, 1>::underlying_type>::value);
    // Signed:7:0.
    REQUIRE(std::is_same<int8_t, mtl::math::fixed<true, 7, 0>::underlying_type>::value);
    // Signed:0:7.
    REQUIRE(std::is_same<int8_t, mtl::math::fixed<true, 0, 7>::underlying_type>::value);
}


TEST_CASE("Signed fixed of 9 to 16 bits in size (including sign) uses int16_t as underlying type.") {
    // Signed:8:0.
    REQUIRE(std::is_same<int16_t, mtl::math::fixed<true, 8, 0>::underlying_type>::value);
    // Signed:0:8.
    REQUIRE(std::is_same<int16_t, mtl::math::fixed<true, 0, 8>::underlying_type>::value);
    // Signed:15:0.
    REQUIRE(std::is_same<int16_t, mtl::math::fixed<true, 15, 0>::underlying_type>::value);
    // Signed:0:15.
    REQUIRE(std::is_same<int16_t, mtl::math::fixed<true, 0, 15>::underlying_type>::value);
}


TEST_CASE("Signed fixed of 17 to 32 bits in size (including sign) uses int32_t as underlying type.") {
    // Signed:16:0.
    REQUIRE(std::is_same<int32_t, mtl::math::fixed<true, 16, 0>::underlying_type>::value);
    // Signed:0:16.
    REQUIRE(std::is_same<int32_t, mtl::math::fixed<true, 0, 16>::underlying_type>::value);
    // Signed:31:0.
    REQUIRE(std::is_same<int32_t, mtl::math::fixed<true, 31, 0>::underlying_type>::value);
    // Signed:0:31.
    REQUIRE(std::is_same<int32_t, mtl::math::fixed<true, 0, 31>::underlying_type>::value);
}


TEST_CASE("Signed fixed of 33 to 64 bits in size (including sign) uses int64_t as underlying type.") {
    // Signed:32:0.
    REQUIRE(std::is_same<int64_t, mtl::math::fixed<true, 32, 0>::underlying_type>::value);
    // Signed:0:32.
    REQUIRE(std::is_same<int64_t, mtl::math::fixed<true, 0, 32>::underlying_type>::value);
    // Signed:63:0.
    REQUIRE(std::is_same<int64_t, mtl::math::fixed<true, 63, 0>::underlying_type>::value);
    // Signed:0:63.
    REQUIRE(std::is_same<int64_t, mtl::math::fixed<true, 0, 63>::underlying_type>::value);
}


TEST_CASE("Minimum valie of unsigned fix is 0.") {
    // Signed:32:0.
    REQUIRE(std::is_same<int64_t, mtl::math::fixed<true, 32, 0>::underlying_type>::value);
    // Signed:0:32.
    REQUIRE(std::is_same<int64_t, mtl::math::fixed<true, 0, 32>::underlying_type>::value);
    // Signed:63:0.
    REQUIRE(std::is_same<int64_t, mtl::math::fixed<true, 63, 0>::underlying_type>::value);
    // Signed:0:63.
    REQUIRE(std::is_same<int64_t, mtl::math::fixed<true, 0, 63>::underlying_type>::value);
}
