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
#include <expected>

#include "cache.h"
#include "fileutils.h"
#include "point.h"
#include "split.h"
#include "explicit_sized.h"

using namespace localstd;

using namespace std::literals;

int main() {
    constexpr auto x = (u8{1} + u8{1}) * u8{2};
    std::println("{}", x);

    constexpr auto p = point{1, 2, 3};

    const auto& [a, b, c] = p;

    std::println("{}, {}, {}", a, b, c);

    std::cout << p << std::endl;
    std::println("{}", p);
    std::println("{}", point{3, 4, 5});

    constexpr auto v1 = u8{1};
    constexpr auto v2 = u8{2};
    std::println("{}", v1 | v2);
    std::println("{}", v1 & v2);

    std::println("{}", static_cast<u32>(v1));
    constexpr auto v3 = i8{-2};
    std::println("{}", static_cast<i32>(v3));
}
