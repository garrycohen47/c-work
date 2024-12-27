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
#include <print>

#include "cache.h"
#include "fileutils.h"
#include "point.h"
#include "split.h"

using namespace localstd;

int main() {
    // TODO: see about having the types stay as the larger of the two, i.e. int & long -> long regardless of order
    constexpr auto p_1 = 1_x + 2_y - 3_z;
    constexpr auto p_2 = 1.0_x + 2_y - 3_z;
    constexpr auto p_3 = p_1 + p_2;
    constexpr auto p_4 = p_1 - p_2;
    constexpr auto p_5 = p_1 * 2;
    constexpr auto p_6 = p_1 * 1.9;
    constexpr auto p_7 = p_2 * 2;
    constexpr auto p_8 = p_2 * 1.9;
    constexpr auto p_same_1 = point<int>(1, 0, 0) + point<long>(0, 1, 0);
    constexpr auto p_same_2 = point<long>(1, 0, 0) + point<int>(0, 1, 0);
    std::cout << "p_1 : " << p_1 << std::endl;
    std::cout << "p_2 : " << p_2 << std::endl;
    std::cout << "p_3 : " << p_3 << std::endl;
    std::cout << "p_4 : " << p_4 << std::endl;
    std::cout << "p_5 : " << p_5 << std::endl;
    std::cout << "p_6 : " << p_6 << std::endl;
    std::cout << "p_7 : " << p_7 << std::endl;
    std::cout << "p_8 : " << p_8 << std::endl;
    const auto& [x, y, z] = p_8;
    std::cout << "structured binding: [" << x << ", " << y << ", " << z << "]" << std::endl;
}
