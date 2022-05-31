#include <cstdint>
#include <type_traits>
#include <catch2/catch.hpp>
#include <mtl/traits/types.hpp>


TEST_CASE("Valid underlying types are picked for unsigned fixed.") {
    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<false, 1>>::type,
        uint8_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<false, 4>>::type,
        uint8_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<false, 8>>::type,
        uint8_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<false, 9>>::type,
        uint16_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<false, 12>>::type,
        uint16_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<false, 16>>::type,
        uint16_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<false, 17>>::type,
        uint32_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<false, 24>>::type,
        uint32_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<false, 32>>::type,
        uint32_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<false, 33>>::type,
        uint64_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<false, 48>>::type,
        uint64_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<false, 64>>::type,
        uint64_t
    >::value);
}

TEST_CASE("Valid underlying types are picked for signed fixed.") {
    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<true, 1>>::type,
        int8_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<true, 4>>::type,
        int8_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<true, 8>>::type,
        int8_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<true, 9>>::type,
        int16_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<true, 12>>::type,
        int16_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<true, 16>>::type,
        int16_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<true, 17>>::type,
        int32_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<true, 24>>::type,
        int32_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<true, 32>>::type,
        int32_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<true, 33>>::type,
        int64_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<true, 48>>::type,
        int64_t
    >::value);

    CHECK(std::is_same<
        mtl::traits::types::pick<mtl::traits::typesp::min_integral<true, 64>>::type,
        int64_t
    >::value);
}