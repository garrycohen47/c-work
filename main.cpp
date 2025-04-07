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
    constexpr auto x = (u16{1} + u16{1}) * u16{2};

    constexpr auto p = point{1, 2, 3};

    const auto& [a, b, c] = p;

    std::println("{}, {}, {}", a, b, c);

    std::cout << p << std::endl;
    std::println("{}", p);
    std::println("{}", point{3, 4, 5});
    std::println("{}", x);
}
