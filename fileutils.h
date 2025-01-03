#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include <concepts>
#include <filesystem>
#include <fstream>
#include <iterator>

namespace fs = std::filesystem;

namespace localstd
{
    namespace detail {
        auto save_stream(std::ofstream& s, auto first, auto last) {
            std::for_each(first, last, [&s](const auto& i) {
                s << i;
            });
        }

        auto save_stream(
            std::ofstream& s,
            std::contiguous_iterator auto first,
            std::contiguous_iterator auto last) {
            s.write(
                static_cast<char*>(std::to_address(first)),
                static_cast<std::streamsize>(std::distance(first, last)));
        }
    } // namespace detail

    auto save(const fs::path& file, auto first, auto last) noexcept {
        fs::create_directories(file.parent_path());

        constexpr auto settings = std::ios_base::out | std::ios_base::binary | std::ios_base::trunc;
        std::ofstream stream(file, settings);

        if (!stream) {
            return false;
        }

        detail::save_stream(stream, first, last);

        return true;
    }

    auto read(const fs::path& file, auto out) noexcept {
        // TODO:
    }
} // namespace localstd

#endif
