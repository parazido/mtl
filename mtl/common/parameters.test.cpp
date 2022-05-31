#include <type_traits>
#include <catch2/catch.hpp>
#include <mtl/common/parameters.hpp>



template<auto> struct value_template_1 {};
template<auto> struct value_template_2 {};
template<auto...> struct value_template_3 {};
template<class> struct type_template_1 {};
template<class> struct type_template_2 {};
template<class...> struct type_template_3 {};


TEST_CASE("Both `find` and `find_value` are initialized with `void` type for an empty set of parameters.") {
    REQUIRE(
        std::is_same<mtl::parameters<>::template find<value_template_1>::type,
        void
    >::value);
    
    REQUIRE(
        std::is_same<mtl::parameters<>::template find_type<type_template_1>::type,
        void
    >::value);    
}

TEST_CASE("Both `find` and `find_value` are initialized with default type for an empty set of parameters if specified.") {
    REQUIRE(
        std::is_same<mtl::parameters<>::template find<value_template_1, value_template_1<0>>::type,
        value_template_1<0>
    >::value);
    
    REQUIRE(
        std::is_same<mtl::parameters<>::template find_type<type_template_1, type_template_1<void>>::type,
        type_template_1<void>
    >::value);
}

TEST_CASE("Both `find` and `find_value` are initialized with `void` if no matching parameter is found in a single parameter set.") {
    CHECK(std::is_same<
        mtl::parameters<type_template_1<void>>::template find<value_template_1>::type,
        void
    >::value);

    CHECK(std::is_same<
        mtl::parameters<value_template_1<0>>::template find<value_template_2>::type,
        void
    >::value);

    CHECK(std::is_same<
        mtl::parameters<value_template_1<0>>::template find_type<type_template_1>::type,
        void
    >::value);

    CHECK(std::is_same<
        mtl::parameters<type_template_1<void>>::template find_type<type_template_2>::type,
        void
    >::value);
}

TEST_CASE("Both `find` and `find_value` are initialized with appropriate type if matching parameter is found in a single parameter set.") {
    CHECK(std::is_same<
        mtl::parameters<value_template_1<0>>::template find<value_template_1>::type,
        value_template_1<0>
    >::value);

    CHECK(std::is_same<
        mtl::parameters<type_template_1<void>>::template find_type<type_template_1>::type,
        type_template_1<void>
    >::value);
}

TEST_CASE("Both `find` and `find_value` are initialized with the first matching type.") {
    CHECK(std::is_same<
        mtl::parameters<value_template_1<0>, value_template_1<1>>::template find<value_template_1>::type,
        value_template_1<0>
    >::value);

    CHECK(std::is_same<
        mtl::parameters<type_template_1<void>, type_template_1<int>>::template find_type<type_template_1>::type,
        type_template_1<void>
    >::value);
}


TEST_CASE("Both `find` and `find_value` are initialized with the matching type in a mixed parameter set.") {
    CHECK(std::is_same<
        mtl::parameters<
            value_template_1<0>, type_template_1<void>, type_template_2<void>, value_template_2<0>
        >::template find<value_template_1>::type,
        value_template_1<0>
    >::value);

    CHECK(std::is_same<
        mtl::parameters<
            value_template_1<0>, type_template_1<void>, type_template_2<void>, value_template_2<0>
        >::template find<value_template_2>::type,
        value_template_2<0>
    >::value);

    CHECK(std::is_same<
        mtl::parameters<
            type_template_1<void>, value_template_1<0>, value_template_2<0>, type_template_2<void>
        >::template find_type<type_template_1>::type,
        type_template_1<void>
    >::value);

    CHECK(std::is_same<
        mtl::parameters<
            type_template_1<void>, value_template_1<0>, value_template_2<0>, type_template_2<void>
        >::template find_type<type_template_2>::type,
        type_template_2<void>
    >::value);
}

TEST_CASE("Both `find` and `find_value` are initialized with appropriate type if matching parameter is found (with multiple arguments).") {
    CHECK(std::is_same<
        mtl::parameters<value_template_3<0, 1>, value_template_1<0>>::template find<value_template_3>::type,
        value_template_3<0, 1>
    >::value);

    CHECK(std::is_same<
        mtl::parameters<type_template_3<void, void>, type_template_1<void>>::template find_type<type_template_3>::type,
        type_template_3<void, void>
    >::value);
}
