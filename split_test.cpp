// TEST FILE

#include <gtest/gtest.h>
#include <list>
#include "split.h"

using namespace localstd;

TEST(split_tests, splits_list)
{
	std::vector<int> temp_vec {0, 1, 2, 3, 4, 0, 1, 2, 0, 5, 4};
	std::vector<std::vector<int>> expected_out_vector {
		{},
		{1, 2, 3, 4},
		{1, 2},
		{5, 4},
	};

	std::vector<std::vector<int>> out_vector;
	split(
		temp_vec.cbegin(), temp_vec.cend(),
		std::back_inserter(out_vector),
		[](const auto& val)
		{
			return val == 0;
		}
	);

	EXPECT_EQ(out_vector, expected_out_vector);
}

TEST(split_tests, splits_weird_lists)
{
	std::list<char> in_list {'A', 'B', 'A', 'E', 'A', 'A'};
	std::vector<std::string> expected_out_list {
		{},
		{'B'},
		{'E'},
		{},
		{},
	};

	std::vector<std::string> out_list;

	split(
		in_list.cbegin(), in_list.cend(),
		std::back_inserter(out_list),
		[](const auto& val)
		{
			return val == 'A';
		}
	);

	EXPECT_EQ(expected_out_list, out_list);
}

TEST(split_tests, splits_empty_list)
{
	std::list<int> in_list {};
	std::vector<std::vector<int>> expected_out_list {
		{}
	};

	std::vector<std::vector<int>> out_list;

	split(
		in_list.cbegin(), in_list.cend(),
		std::back_inserter(out_list),
		[](const auto& val)
		{
			return val == 'A';
		}
	);

	EXPECT_EQ(expected_out_list, out_list);
}

TEST(split_tests, splits_list_front_inserter)
{
	std::string_view in_list {"Fart in my arse"};

	std::list<std::string_view> expected_out_list {
		{"rse"},
		{"rt in my "},
		{"F"},
	};

	std::list<std::string_view> out_list;

	split(
		in_list.cbegin(), in_list.cend(),
		std::front_inserter(out_list),
		[](const auto& val)
		{
			return val == 'a';
		}
	);

	EXPECT_EQ(expected_out_list, out_list);
}