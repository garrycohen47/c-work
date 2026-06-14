#ifndef READABLE_H_
#define READABLE_H_

#include <type_traits>

#include <string>
#include <array>

#include <cstdint>

#include "result.h"

namespace readwrite {
    using namespace localstd;
    struct Readable {
        enum class Error {
            Closed,
        };

        virtual ~Readable() = default;

        virtual auto Read(char* data, size_t length) -> Result<void, Error> = 0;

        template<size_t N>
        auto Read() -> Result<std::array<char, N>, Error> {
            auto result = std::array<char, N>{};
            return Read(result.data(), result.size())
                .map(
                    [&] {
                        return result;
                    });
        }

        auto Read(const size_t length) -> Result<std::string, Error> {
            auto result = std::string(length, '\0');
            return Read(result.data(), result.size())
                .map(
                    [&result] {
                        return result;
                    });
        }
    };

    template<typename T>
    using ReadResult = Result<T, Readable::Error>;

    namespace detail {
        template<typename T, size_t... I>
        auto FromNetworkBytes(const std::array<char, sizeof(T)>& bytes, std::index_sequence<I...>) -> T {
            T result = 0;

            ((result |= (static_cast<T>(static_cast<uint8_t>(bytes[I])) << (8 * (sizeof(T) - I - 1 )))), ...);

            return result;
        }
    }

    template<typename T>
    auto FromNetworkBytes(const std::array<char, sizeof(T)>& bytes) -> T {
        return detail::FromNetworkBytes<T>(bytes, std::make_index_sequence<sizeof(T)>{});
    }

    template<typename T, typename = void>
    struct Reader;

    template<typename T, typename... Args>
    auto Read(Readable& readable, Args&&... args) {
        return Reader<T>::Read(readable, std::forward<Args>(args)...);
    }

    template<typename T>
    struct Reader<T, std::enable_if_t<std::is_integral_v<T>>> {
        static auto Read(Readable& readable) -> ReadResult<T> {
            return readable.Read<sizeof(T)>().map(FromNetworkBytes<T>);
        }
    };

    template<>
    struct Reader<std::string> {
        static auto Read(Readable& readable, const size_t length) -> ReadResult<std::string> {
            return readable.Read(length);
        }
    };

    template<typename T, size_t N>
    struct Reader<std::array<T, N>> {
        static auto Read(Readable& readable) -> ReadResult<std::array<T, N>> {
            auto result = std::array<T, N>{};

            for (auto i = size_t{0}; i < N; ++i) {
                const auto element = readwrite::Read<T>(readable);

                if (element.is_err()) {
                    return element.err().value();
                }

                result[i] = element.ok().value();
            }

            return result;
        }
    };

    template<size_t N>
    struct Reader<std::array<char, N>> {
        static auto Read(Readable& readable) -> ReadResult<std::array<char, N>> {
            return readable.Read<N>();
        }
    };

    template<typename T>
    struct Reader<std::vector<T>> {
        static auto Read(Readable& readable, const size_t length) -> ReadResult<std::vector<T>> {
            // TODO:
        }
    };
}

#endif