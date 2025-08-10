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

TEST(result_tests, OkOkConstRef) {
    const auto test = Result<int, std::string>{1};
    const auto op_ref = test.ok_ref();
    ASSERT_TRUE(op_ref.has_value());
    [[maybe_unused]]
    const auto& ref = op_ref->get();
    using test_type = decltype(ref);
    static_assert(std::is_reference_v<test_type>);
    static_assert(std::is_const_v<std::remove_reference_t<test_type>>);
    ASSERT_EQ(ref, 1);
}

TEST(result_tests, OkOkRef) {
    auto test = Result<int, std::string>{1};
    const auto op_ref = test.ok_ref();
    ASSERT_TRUE(op_ref.has_value());
    [[maybe_unused]]
    auto& ref = op_ref->get();
    ASSERT_EQ(ref, 1);
    ref = 5;
    ASSERT_EQ(ref, 5);
    using test_type = decltype(ref);
    static_assert(std::is_reference_v<test_type>);
    static_assert(!std::is_const_v<std::remove_reference_t<test_type>>);
}

TEST(result_tests, ErrErrConstRef) {
    const auto test = Result<int, std::string>{"1234567890"};
    const auto op_ref = test.err_ref();
    ASSERT_TRUE(op_ref.has_value());
    [[maybe_unused]]
    const auto& ref = op_ref->get();
    using test_type = decltype(ref);
    static_assert(std::is_reference_v<test_type>);
    static_assert(std::is_const_v<std::remove_reference_t<test_type>>);
    ASSERT_EQ(ref, "1234567890");
}

TEST(result_tests, ErrErrRef) {
    auto test = Result<int, std::string>{"1234567890"};
    const auto op_ref = test.err_ref();
    ASSERT_TRUE(op_ref.has_value());
    [[maybe_unused]]
    auto& ref = op_ref->get();
    ASSERT_EQ(ref, "1234567890");
    ref = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    ASSERT_EQ(ref, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    using test_type = decltype(ref);
    static_assert(std::is_reference_v<test_type>);
    static_assert(!std::is_const_v<std::remove_reference_t<test_type>>);
}

TEST(result_tests, OkErrRef) {
    const auto test = Result<int, std::string>{1};
    const auto op_ref = test.err_ref();
    ASSERT_FALSE(op_ref.has_value());
}

TEST(result_tests, ErrOkRef) {
    const auto test = Result<int, std::string>{"1234567890"};
    const auto op_ref = test.ok_ref();
    ASSERT_FALSE(op_ref.has_value());
}
