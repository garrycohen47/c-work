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
    constexpr auto p = point{1, 2, 3};
    std::cout << p << std::endl;
    std::wcout << p << std::endl;

    // std::println("{}", p);
}
