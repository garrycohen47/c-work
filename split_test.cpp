// TEST FILE

#include "split.h"
#include <gtest/gtest.h>
#include <list>

using namespace localstd;

TEST(split_tests, splits_list)
{
	const std::vector temp_vec{0, 1, 2, 3, 4, 0, 1, 2, 0, 5, 4};
	const std::vector<std::vector<int>> expected_out_vector{
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
	const std::list in_list{'A', 'B', 'A', 'E', 'A', 'A'};
	const std::vector<std::string> expected_out_list{
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

TEST(split_tests, splits_empty_list) {
	const std::list<int> in_list{};
	const std::vector<std::vector<int>> expected_out_list{{}};

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

TEST(split_tests, splits_list_front_inserter) {
	using namespace std::literals;
	constexpr std::string_view in_list{"Sandwhich Whale Cartesian"};

	const std::list expected_out_list{
		"n"sv,
		"rtesi"sv,
		"le C"sv,
		"ndwhich Wh"sv,
		"S"sv,
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

TEST(split_tests, constexpr_test) {
	using namespace std::literals;
	constexpr auto temp_view = "Howdy pardnur, I'm a big cowpoke."sv;
	constexpr std::array expected_values{
		"Howdy"sv,
		"pardnur,"sv,
		"I'm"sv,
		"a"sv,
		"big"sv,
		"cowpoke."sv
	};

	std::array<std::string_view, 6> out_arr{};

	split(
		temp_view.cbegin(),
		temp_view.cend(),
		out_arr.begin(),
		[](const auto val) {
			return val == ' ';
		});

	EXPECT_EQ(out_arr, expected_values);
}
