#include <type_traits>

#include <mtl/traits/list.hpp>

#include <catch2/catch.hpp>

TEST_CASE("List length is the same as number of its elements.") {
    CHECK(mtl::traits::list<>::length == 0);
    CHECK(mtl::traits::list<void>::length == 1);
    CHECK(mtl::traits::list<void, void>::length == 2);
}

TEST_CASE("`contains` is `true` if the specified element is in the list, `false` otherwise.") {
    CHECK_FALSE(mtl::traits::list<>::contains<void>);
    CHECK(mtl::traits::list<void>::contains<void>);
    CHECK_FALSE(mtl::traits::list<void>::contains<int>);
    CHECK(mtl::traits::list<void, int, int>::contains<void>);
    CHECK(mtl::traits::list<int, void, int>::contains<void>);
    CHECK(mtl::traits::list<int, int, void>::contains<void>);
    CHECK_FALSE(mtl::traits::list<int, int, int>::contains<void>);
}

TEST_CASE("`next` contains list with the following set of elements or `void` if last or empty.") {
    CHECK(std::is_same<typename mtl::traits::list<>::next, void>::value);
    CHECK(std::is_same<typename mtl::traits::list<int>::next, void>::value);
    CHECK(std::is_same<typename mtl::traits::list<int, char>::next, mtl::traits::list<char>>::value);
}

TEST_CASE("`type` is of the same type as the first element in the list or `void` if empty.") {
    CHECK(std::is_same<typename mtl::traits::list<>::type, void>::value);
    CHECK(std::is_same<typename mtl::traits::list<int>::type, int>::value);
    CHECK(std::is_same<typename mtl::traits::list<int, char>::type, int>::value);
    CHECK(std::is_same<typename mtl::traits::list<int, char>::next::type, char>::value);
}
