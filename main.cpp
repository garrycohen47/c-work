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
#include <map>
#include <random>
#include <ranges>
#include <future>
#include <thread>
#include <condition_variable>
#include <mutex>

#include "cache.h"
#include "fileutils.h"
#include "point.h"
#include "split.h"
#include "explicit_sized.h"
#include "result.h"

#include "Readable.h"
#include "Writable.h"

using namespace localstd;
using namespace readwrite;

using namespace std::literals;
using namespace std::chrono;

namespace fs = std::filesystem;

int main() {
    std::println("Hi!");
}
