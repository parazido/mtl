

TEMPLATE_LIST_TEST_CASE("`min` value for an unsigned fixed is always 0.", "", unsigned_fixed_set) {
    constexpr auto value = TestType::min;
    REQUIRE(value.integral() == 0);
    REQUIRE(value.floating() == 0);
}


TEMPLATE_LIST_TEST_CASE("`min` value for a signed fixed is equal to the min integral value of the same width.", "", signed_fixed_set) {
    using underlying_type = typename TestType::underlying_type;
    constexpr auto value = TestType::min;
    REQUIRE(value.integral() == static_cast<underlying_type>(std::bitset<sizeof(underlying_type) * 8>().set(TestType::integral_bits - 1).flip().to_ullong()) + 1);
    REQUIRE(value.floating() == 0);
}