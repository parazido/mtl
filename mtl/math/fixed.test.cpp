#include <type_traits>
#include <catch2/catch.hpp>
#include <mtl/math/fixed.hpp>



TEST_CASE("Fixed underlying type must match overall width (in bits) and sign.") {
    // 8-bit unsigned fixed types.
    CHECK(std::is_same<typename mtl::math::fixed<false, 0, 1>::underlying_type, uint8_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 1, 0>::underlying_type, uint8_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 4, 4>::underlying_type, uint8_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 0, 8>::underlying_type, uint8_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 8, 0>::underlying_type, uint8_t>::value);
    // 16-bit unsigned fixed types.
    CHECK(std::is_same<typename mtl::math::fixed<false, 0, 9>::underlying_type, uint16_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 9, 0>::underlying_type, uint16_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 8, 8>::underlying_type, uint16_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 0, 16>::underlying_type, uint16_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 16, 0>::underlying_type, uint16_t>::value);
    // 32-bit unsigned fixed types.
    CHECK(std::is_same<typename mtl::math::fixed<false, 0, 17>::underlying_type, uint32_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 17, 0>::underlying_type, uint32_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 16, 16>::underlying_type, uint32_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 0, 32>::underlying_type, uint32_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 32, 0>::underlying_type, uint32_t>::value);
    // 64-bit unsigned fixed types.
    CHECK(std::is_same<typename mtl::math::fixed<false, 0, 33>::underlying_type, uint64_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 33, 0>::underlying_type, uint64_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 32, 32>::underlying_type, uint64_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 0, 64>::underlying_type, uint64_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<false, 64, 0>::underlying_type, uint64_t>::value);
    // 8-bit signed fixed types.
    CHECK(std::is_same<typename mtl::math::fixed<true, 0, 1>::underlying_type, int8_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 1, 0>::underlying_type, int8_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 4, 3>::underlying_type, int8_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 0, 7>::underlying_type, int8_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 7, 0>::underlying_type, int8_t>::value);
    // 16-bit signed fixed types.
    CHECK(std::is_same<typename mtl::math::fixed<true, 0, 8>::underlying_type, int16_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 8, 0>::underlying_type, int16_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 8, 7>::underlying_type, int16_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 0, 15>::underlying_type, int16_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 15, 0>::underlying_type, int16_t>::value);
    // 32-bit signed fixed types.
    CHECK(std::is_same<typename mtl::math::fixed<true, 0, 16>::underlying_type, int32_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 16, 0>::underlying_type, int32_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 16, 15>::underlying_type, int32_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 0, 31>::underlying_type, int32_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 31, 0>::underlying_type, int32_t>::value);
    // 64-bit signed fixed types.
    CHECK(std::is_same<typename mtl::math::fixed<true, 0, 32>::underlying_type, int64_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 32, 0>::underlying_type, int64_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 32, 31>::underlying_type, int64_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 0, 63>::underlying_type, int64_t>::value);
    CHECK(std::is_same<typename mtl::math::fixed<true, 63, 0>::underlying_type, int64_t>::value);
}


TEST_CASE("`min` value for an unsigned fixed is always `0`.") {
    // 8-bit unsigned fixed types.
    CHECK(mtl::math::fixed<false, 0, 1>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 1>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 1, 0>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 1, 0>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 4, 4>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 4, 4>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 0, 8>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 8>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 8, 0>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 8, 0>::min.floating() == 0);
    // 16-bit unsigned fixed types.
    CHECK(mtl::math::fixed<false, 0, 9>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 9>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 9, 0>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 9, 0>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 8, 8>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 8, 8>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 0, 16>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 16>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 16, 0>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 16, 0>::min.floating() == 0);
    // 32-bit unsigned fixed types.
    CHECK(mtl::math::fixed<false, 0, 17>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 17>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 17, 0>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 17, 0>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 16, 16>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 16, 16>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 0, 32>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 32>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 32, 0>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 32, 0>::min.floating() == 0);
    // 64-bit unsigned fixed types.
    CHECK(mtl::math::fixed<false, 0, 33>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 33>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 33, 0>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 33, 0>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 32, 32>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 32, 32>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 0, 64>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 64>::min.floating() == 0);
    CHECK(mtl::math::fixed<false, 64, 0>::min.integral() == 0);
    CHECK(mtl::math::fixed<false, 64, 0>::min.floating() == 0);
}


TEST_CASE("`min` value for a signed fixed matches its size.") {
    // 8-bit signed fixed types.
    CHECK(mtl::math::fixed<true, 0, 1>::min.integral() == -1);
    CHECK(mtl::math::fixed<true, 0, 1>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 1, 0>::min.integral() == -2);
    CHECK(mtl::math::fixed<true, 1, 0>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 4, 3>::min.integral() == -8);
    CHECK(mtl::math::fixed<true, 4, 3>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 0, 7>::min.integral() == -1);
    CHECK(mtl::math::fixed<true, 0, 7>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 7, 0>::min.integral() == -128);
    CHECK(mtl::math::fixed<true, 7, 0>::min.floating() == 0);
    // 16-bit signed fixed types.
    CHECK(mtl::math::fixed<true, 0, 8>::min.integral() == -1);
    CHECK(mtl::math::fixed<true, 0, 8>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 8, 0>::min.integral() == -256);
    CHECK(mtl::math::fixed<true, 8, 0>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 8, 7>::min.integral() == -256);
    CHECK(mtl::math::fixed<true, 8, 7>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 0, 15>::min.integral() == -1);
    CHECK(mtl::math::fixed<true, 0, 15>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 15, 0>::min.integral() == -32768);
    CHECK(mtl::math::fixed<true, 15, 0>::min.floating() == 0);
    // 32-bit signed fixed types.
    CHECK(mtl::math::fixed<true, 0, 16>::min.integral() == -1);
    CHECK(mtl::math::fixed<true, 0, 16>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 16, 0>::min.integral() == -65536);
    CHECK(mtl::math::fixed<true, 16, 0>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 16, 15>::min.integral() == -65536);
    CHECK(mtl::math::fixed<true, 16, 15>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 0, 31>::min.integral() == -1);
    CHECK(mtl::math::fixed<true, 0, 31>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 31, 0>::min.integral() == -2147483648);
    CHECK(mtl::math::fixed<true, 31, 0>::min.floating() == 0);
    // 64-bit signed fixed types.
    CHECK(mtl::math::fixed<true, 0, 32>::min.integral() == -1);
    CHECK(mtl::math::fixed<true, 0, 32>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 32, 0>::min.integral() == -4294967296);
    CHECK(mtl::math::fixed<true, 32, 0>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 32, 31>::min.integral() == -4294967296);
    CHECK(mtl::math::fixed<true, 32, 31>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 0, 63>::min.integral() == -1);
    CHECK(mtl::math::fixed<true, 0, 63>::min.floating() == 0);
    CHECK(mtl::math::fixed<true, 63, 0>::min.integral() == -9223372036854775808);
    CHECK(mtl::math::fixed<true, 63, 0>::min.floating() == 0);
}


TEST_CASE("`max` value for an unsigned fixed matches its size.") {
    // 8-bit unsigned fixed types.
    CHECK(mtl::math::fixed<false, 0, 1>::max.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 1>::max.floating() == 0.5);
    CHECK(mtl::math::fixed<false, 1, 0>::max.integral() == 1);
    CHECK(mtl::math::fixed<false, 1, 0>::max.floating() == 0);
    CHECK(mtl::math::fixed<false, 4, 4>::max.integral() == 15);
    CHECK(mtl::math::fixed<false, 4, 4>::max.floating() == 0.9375);
    CHECK(mtl::math::fixed<false, 0, 8>::max.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 8>::max.floating() == 0.99609375);
    CHECK(mtl::math::fixed<false, 8, 0>::max.integral() == 255);
    CHECK(mtl::math::fixed<false, 8, 0>::max.floating() == 0);
    // 16-bit unsigned fixed types.
    CHECK(mtl::math::fixed<false, 0, 9>::max.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 9>::max.floating() == 0.998046875);
    CHECK(mtl::math::fixed<false, 9, 0>::max.integral() == 511);
    CHECK(mtl::math::fixed<false, 9, 0>::max.floating() == 0);
    CHECK(mtl::math::fixed<false, 8, 8>::max.integral() == 255);
    CHECK(mtl::math::fixed<false, 8, 8>::max.floating() == 0.99609375);
    CHECK(mtl::math::fixed<false, 0, 16>::max.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 16>::max.floating() == 0.9999847412109375);
    CHECK(mtl::math::fixed<false, 16, 0>::max.integral() == 65535);
    CHECK(mtl::math::fixed<false, 16, 0>::max.floating() == 0);
    // 32-bit unsigned fixed types.
    CHECK(mtl::math::fixed<false, 0, 17>::max.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 17>::max.floating() == 0.99999237060546875);
    CHECK(mtl::math::fixed<false, 17, 0>::max.integral() == 131071);
    CHECK(mtl::math::fixed<false, 17, 0>::max.floating() == 0);
    CHECK(mtl::math::fixed<false, 16, 16>::max.integral() == 65535);
    CHECK(mtl::math::fixed<false, 16, 16>::max.floating() == 0.9999847412109375);
    CHECK(mtl::math::fixed<false, 0, 32>::max.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 32>::max.floating() == 0.99999999976716935634613037109375);
    CHECK(mtl::math::fixed<false, 32, 0>::max.integral() == 4294967295);
    CHECK(mtl::math::fixed<false, 32, 0>::max.floating() == 0);
    // 64-bit unsigned fixed types.
    CHECK(mtl::math::fixed<false, 0, 33>::max.integral() == 0);
    CHECK(mtl::math::fixed<false, 0, 33>::max.floating() == 0.999999999883584678173065185546875);
    CHECK(mtl::math::fixed<false, 33, 0>::max.integral() == 8589934591);
    CHECK(mtl::math::fixed<false, 33, 0>::max.floating() == 0);
    CHECK(mtl::math::fixed<false, 32, 32>::max.integral() == 4294967295);
    CHECK(mtl::math::fixed<false, 32, 32>::max.floating() == 0.99999999976716935634613037109375);
    CHECK(mtl::math::fixed<false, 0, 64>::max.integral() == 0);
    // CHECK(mtl::math::fixed<false, 0, 64>::max.floating() == 0);
    CHECK(mtl::math::fixed<false, 64, 0>::max.integral() == 18446744073709551615);
    CHECK(mtl::math::fixed<false, 64, 0>::max.floating() == 0);
}


TEST_CASE("`min` value for a signed fixed is always `0`.") {
    // 8-bit signed fixed types.
    CHECK(mtl::math::fixed<true, 0, 1>::max.integral() == 0);
    CHECK(mtl::math::fixed<true, 0, 1>::max.floating() == 0.5);
    CHECK(mtl::math::fixed<true, 1, 0>::max.integral() == 1);
    CHECK(mtl::math::fixed<true, 1, 0>::max.floating() == 0);
    CHECK(mtl::math::fixed<true, 4, 3>::max.integral() == 15);
    CHECK(mtl::math::fixed<true, 4, 3>::max.floating() == 0.875);
    CHECK(mtl::math::fixed<true, 0, 7>::max.integral() == 0);
    CHECK(mtl::math::fixed<true, 0, 7>::max.floating() == 0.9921875);
    CHECK(mtl::math::fixed<true, 7, 0>::max.integral() == 127);
    CHECK(mtl::math::fixed<true, 7, 0>::max.floating() == 0);
    // 16-bit signed fixed types.
    CHECK(mtl::math::fixed<true, 0, 8>::max.integral() == 0);
    CHECK(mtl::math::fixed<true, 0, 8>::max.floating() == 0.99609375);
    CHECK(mtl::math::fixed<true, 8, 0>::max.integral() == 255);
    CHECK(mtl::math::fixed<true, 8, 0>::max.floating() == 0);
    CHECK(mtl::math::fixed<true, 8, 7>::max.integral() == 255);
    CHECK(mtl::math::fixed<true, 8, 7>::max.floating() == 0.9921875);
    CHECK(mtl::math::fixed<true, 0, 15>::max.integral() == 0);
    CHECK(mtl::math::fixed<true, 0, 15>::max.floating() == 0.999969482421875);
    CHECK(mtl::math::fixed<true, 15, 0>::max.integral() == 32767);
    CHECK(mtl::math::fixed<true, 15, 0>::max.floating() == 0);
    // 32-bit signed fixed types.
    CHECK(mtl::math::fixed<true, 0, 16>::max.integral() == 0);
    CHECK(mtl::math::fixed<true, 0, 16>::max.floating() == 0.9999847412109375);
    CHECK(mtl::math::fixed<true, 16, 0>::max.integral() == 65535);
    CHECK(mtl::math::fixed<true, 16, 0>::max.floating() == 0);
    CHECK(mtl::math::fixed<true, 16, 15>::max.integral() == 65535);
    CHECK(mtl::math::fixed<true, 16, 15>::max.floating() == 0.999969482421875);
    CHECK(mtl::math::fixed<true, 0, 31>::max.integral() == 0);
    CHECK(mtl::math::fixed<true, 0, 31>::max.floating() == 0.9999999995343387126922607421875);
    CHECK(mtl::math::fixed<true, 31, 0>::max.integral() == 2147483647);
    CHECK(mtl::math::fixed<true, 31, 0>::max.floating() == 0);
    // 64-bit signed fixed types.
    CHECK(mtl::math::fixed<true, 0, 32>::max.integral() == 0);
    CHECK(mtl::math::fixed<true, 0, 32>::max.floating() == 0.99999999976716935634613037109375);
    CHECK(mtl::math::fixed<true, 32, 0>::max.integral() == 4294967295);
    CHECK(mtl::math::fixed<true, 32, 0>::max.floating() == 0);
    CHECK(mtl::math::fixed<true, 32, 31>::max.integral() == 4294967295);
    CHECK(mtl::math::fixed<true, 32, 31>::max.floating() == 0.9999999995343387126922607421875);
    CHECK(mtl::math::fixed<true, 0, 63>::max.integral() == 0);
    //CHECK(mtl::math::fixed<true, 0, 63>::max.floating() == 0);
    CHECK(mtl::math::fixed<true, 63, 0>::max.integral() == 9223372036854775807);
    CHECK(mtl::math::fixed<true, 63, 0>::max.floating() == 0);
}
