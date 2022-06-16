#include <mtl/containers/tuple.hpp>
#include <mtl/traits/list.hpp>
#include <type_traits>
#include <catch2/catch.hpp>

TEST_CASE("Tuple type is `mtl::list`.") {
    CHECK(std::is_same<typename mtl::tuple<int, float, char>::types, mtl::traits::list<int, float, char>>::value);
}

TEST_CASE("Basic chacks are passed.") {
    mtl::tuple<int, float, char> tuple{1, 2.5, 'a'};
    CHECK(mtl::get<0>(tuple) == 1);
    CHECK(mtl::get<1>(tuple) == 2.5);
    CHECK(mtl::get<2>(tuple) == 'a');
}
