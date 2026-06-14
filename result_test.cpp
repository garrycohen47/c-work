#include "result.h"
#include <gtest/gtest.h>

using namespace localstd;

TEST(result_tests, OkIsOk) {
    const auto test = Result<int, std::string>{1};
    ASSERT_TRUE(test.is_ok());
}

TEST(result_tests, OkIsErr) {
    const auto test = Result<int, std::string>{1};
    ASSERT_FALSE(test.is_err());
}

TEST(result_tests, ErrIsOk) {
    const auto test = Result<int, std::string>{"123456"};
    ASSERT_FALSE(test.is_ok());
}

TEST(result_tests, ErrIsErr) {
    const auto test = Result<int, std::string>{"123456"};
    ASSERT_TRUE(test.is_err());
}

TEST(result_tests, OkOk) {
    const auto test = Result<int, std::string>{1};
    ASSERT_EQ(test.ok(), 1);
}

TEST(result_tests, ErrOk) {
    const auto test = Result<int, std::string>{"123456"};
    ASSERT_EQ(test.ok(), std::nullopt);
}
