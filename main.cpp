#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <tuple>
#include <string_view>
#include <vector>
#include <chrono>
#include <numeric>
#include <cstring>
#include <limits>
#include <complex>
#include <print>
#include <expected>
#include <random>

#include "cache.h"
#include "fileutils.h"
#include "point.h"
#include "split.h"
#include "explicit_sized.h"
#include "result.h"

using namespace localstd;

using namespace std::literals;

int main() {
    auto test = Result<int, std::string>{1}
        .map(
            [](const int) -> std::tuple<> {
                return {};
            });

    std::println("{}", test);
}
