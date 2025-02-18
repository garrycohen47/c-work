
#include <type_traits>

#include <gtest/gtest.h>

#include "point.h"

using namespace localstd;

TEST(point_tests, structured_binding_simple) {
    constexpr auto test_point = point<int>{1, 2, -3};
    const auto [x, y, z] = test_point;
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 2);
    EXPECT_EQ(z, -3);
}

TEST(point_tests, structured_binding_mod_ref) {
    auto test_point = point<int>{1, 2, -3};
    auto& [x, y, z] = test_point;
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, 2);
    EXPECT_EQ(z, -3);

    x = 5;

    EXPECT_EQ(x, 5);
}
