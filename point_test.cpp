
#include <type_traits>

#include <gtest/gtest.h>

#include "point.h"

using namespace localstd;

// Static Asserts for tests to ensure that operations performed on a
// Point return the correct internal representation

constexpr auto test_001 = 1_xi + 2_yi + 3_zi;
static_assert(std::is_same_v<decltype(test_001)::type, int>);

constexpr auto test_002 = test_001 * 2;
static_assert(test_002 == (2_xi + 4_yi + 6_zi));

constexpr auto test_003 = (1_xi + 1100_yi).to<double>();
static_assert(std::is_same_v<decltype(test_003)::type, double>);

static_assert(+(-5_xi) == -5_xi);
static_assert(-(-5_xi) == 5_xi);
static_assert(+(test_001) == test_001);

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
