// TEST

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <chrono>
#include <numeric>
#include <cstring>
#include <limits>
#include <complex>

#include "cache.h"
#include "fileutils.h"
#include "split.h"
#include "point.h"

using namespace localstd;

struct U8
{
	constexpr operator auto() const
	{
		return value;
	}
	uint8_t value;
};

int main()
{
	constexpr auto p_1 = 1_x + 2_y + -3_z;
	constexpr auto p_2 = 1.0_x + 2_y + 3_z;
	constexpr auto p_3 = p_1 + p_2;
	constexpr auto p_4 = p_1 - p_2;
	constexpr auto p_5 = p_1 * 2;
	constexpr auto p_6 = p_1 * 1.9;
	constexpr auto p_7 = p_2 * 2;
	constexpr auto p_8 = p_2 * 1.9;
	std::cout << "p_1 : " << std::string(p_1) << std::endl;
	std::cout << "p_2 : " << std::string(p_2) << std::endl;
	std::cout << "p_3 : " << std::string(p_3) << std::endl;
	std::cout << "p_4 : " << std::string(p_4) << std::endl;
	std::cout << "p_5 : " << std::string(p_5) << std::endl;
	std::cout << "p_6 : " << std::string(p_6) << std::endl;
	std::cout << "p_7 : " << std::string(p_7) << std::endl;
	std::cout << "p_8 : " << std::string(p_8) << std::endl;
}

//const fs::path curr_path = fs::current_path().parent_path().parent_path() / "Text.txt";
//
//auto time_now()
//{
//	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
//}
//
//template <typename Item, std::size_t N>
//constexpr auto func()
//{
//	std::array<Item, N> result {};
//	std::iota(result.begin(), result.end(), Item());
//	return result;
//}
//
//constexpr std::size_t amt = 100000;
//
//constexpr auto arr = func<int, amt>();
//
//int main()
//{
//	std::array<int, amt> res {};
//
//	const auto start_mem_copy = time_now();
//	std::copy(arr.cbegin(), arr.cend(), res.begin());
//	const auto end_mem_copy = time_now();
//
//	res.fill(int());
//
//	const auto start_mem_memcopy = time_now();
//	std::memcpy(res.data(), arr.data(), arr.size());
//	const auto end_mem_memcopy = time_now();
//
//	std::cout << "std::copy: " << end_mem_copy - start_mem_copy << std::endl;
//	std::cout << "memcopy: " << end_mem_memcopy - start_mem_memcopy << std::endl;
//}