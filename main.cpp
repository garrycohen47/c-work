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

struct error {
    // TODO: define later
};

template<typename T>
struct explicit_sized {
    using value_type = T;

    constexpr explicit explicit_sized(
        const value_type v)
        noexcept :
        v(v) {
        //
    };

    template<typename U>
    [[nodiscard]]
    constexpr auto as() const noexcept {
        using to = typename U::value_type;
        // check if the conversion will go out of bounds
        if (std::numeric_limits<to>::max() < v) {
            // TODO: figure out what to do here
            throw std::exception{};
        }

        return explicit_sized<to>(static_cast<to>(v));
    }

private
:
    value_type v;
};

using u8 = explicit_sized<uint8_t>;
using u16 = explicit_sized<uint16_t>;
using u32 = explicit_sized<uint32_t>;

using i8 = explicit_sized<int8_t>;
using i16 = explicit_sized<int16_t>;
using i32 = explicit_sized<int32_t>;

using namespace localstd;

int main() {
    constexpr auto x = u16{1}.as<u8>();
    // TODO:
}
