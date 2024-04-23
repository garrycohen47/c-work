#include "cache.h"
#include <gtest/gtest.h>
#include <optional>

using namespace localstd;

TEST(cache_tests, empty_cache)
{
	cache<int, 5> test_cache {};
	cache<int, 5> equality_cache {};
	EXPECT_EQ(test_cache, equality_cache);
}

TEST(cache_tests, filled_cache)
{
	cache<std::optional<int>, 5> test_cache {};
	cache<std::optional<int>, 5> out_cache {2, 3, 1, 0};

	test_cache.push(0);
	test_cache.push(1);
	test_cache.push(2);
	test_cache.push(3);
	test_cache.push(2);

	EXPECT_EQ(test_cache, out_cache);
}

TEST(cache_tests, bracket_test)
{
	cache<std::optional<int>, 5> test_cache {};
	cache<std::optional<int>, 5> out_cache {1, 2, 3, 4, 5};

	test_cache[0] = 1;
	test_cache[1] = 2;
	test_cache[2] = 3;
	test_cache[3] = 4;
	test_cache[4] = 5;

	EXPECT_EQ(test_cache, out_cache);
}

TEST(cache_tests, insertion_operator)
{
	cache<std::optional<int>, 5> test_cache {};
	cache<std::optional<int>, 5> out_cache {10, 0, 5};

	test_cache << 5 << 0 << 10;

	EXPECT_EQ(test_cache, out_cache);
}

TEST(cache_tests, const_initializer_list_test)
{
	// TODO:
}