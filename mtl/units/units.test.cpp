#include <cstdint>
#include <type_traits>

#include <mtl/units/units.hpp>

#include <catch2/catch.hpp>

TEST_CASE("Check `duration` underlying type is `unsigned long long`.") {
    CHECK(std::is_same<mtl::units::duration::underlying_type, unsigned long long>::value);
}

TEST_CASE("Check `frequency` underlying type is `unsigned long long`.") {
    CHECK(std::is_same<mtl::units::frequency::underlying_type, unsigned long long>::value);
}

TEST_CASE("Check `duration` literals equivalence.") {
    CHECK(1_us == 1000_ns);
    CHECK(1_ms == 1000_us);
    CHECK(1_s == 1000_ms);
    CHECK(1_m == 60_s);
    CHECK(1_h == 60_m);
    CHECK(1_h == 3600000000000_ns);
}

TEST_CASE("Check `frequency` literals equivalence.") {
    CHECK(1_uHz == 1000_nHz);
    CHECK(1_mHz == 1000_uHz);
    CHECK(1_Hz == 1000_mHz);
    CHECK(1_kHz == 1000_Hz);
    CHECK(1_MHz == 1000_kHz);
    CHECK(1_GHz == 1000_MHz);
    CHECK(1_GHz == 1000000000000000000_nHz);
}

TEST_CASE("Arithmetic operations with `duration` literals are valid.") {
    CHECK(1_ms * 1.5 == 1500_us);
    CHECK(1_s / 2.5 == 400_ms);
    CHECK(1_s + 100_ms == 1100_ms);
    CHECK(100_ms - 10_us == 99990_us);
}

TEST_CASE("Arithmetic operations with `frequency` literals are valid.") {
    CHECK(1_Hz * 1.5 == 1500_mHz);
    CHECK(1.5_kHz / 1500.0 == 1_Hz);
    CHECK(1_MHz + 100_kHz == 1.1_MHz);
    CHECK(1_Hz - 0.1_Hz == 900_mHz);
}
