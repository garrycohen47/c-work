#ifndef WRITABLE_H_
#define WRITABLE_H_

#include <string>
#include <array>

#include "result.h"

namespace readwrite {
    using namespace localstd;

    struct Writable {
        enum class Error {
            Closed,
        };

        virtual ~Writable() = default;

        virtual auto Write(const char* data, size_t length) -> Result<void, Error> = 0;

        template<size_t N>
        auto Write(const std::array<char, N>& data) -> Result<void, Error> {
            return Write(data.data(), data.size());
        }

        auto Write(const std::string& data) -> Result<void, Error> {
            return Write(data.data(), data.size());
        }

        auto Write(const std::string_view data) -> Result<void, Error> {
            return Write(data.data(), data.size());
        }
    };

    template<typename T>
    using WriteResult = Result<T, Writable::Error>;
}

#endif