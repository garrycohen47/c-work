#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include <concepts>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>

namespace fs = std::filesystem;

namespace localstd
{
    namespace detail {
        auto save_stream(
            std::ofstream& s,
            std::input_iterator auto first,
            std::input_iterator auto last) {
            std::for_each(
                first,
                last,
                [&s](const auto& i) {
                    s << i;
                });
        }

        auto save_stream(
            std::ofstream& s,
            std::contiguous_iterator auto first,
            std::contiguous_iterator auto last) {
            s.write(
                static_cast<const char*>(std::to_address(first)),
                static_cast<std::streamsize>(std::distance(first, last)));
        }
    } // namespace detail

    auto save(
        const fs::path& file,
        std::input_iterator auto first,
        std::input_iterator auto last,
        const std::ios::openmode settings) noexcept {
        fs::create_directories(file.parent_path());

        std::ofstream stream(
            file,
            settings);

        if (!stream) {
            return false;
        }

        detail::save_stream(
            stream,
            first,
            last);

        return true;
    }

    auto read(
        const fs::path& file,
        auto out) noexcept {
        // TODO:
    }
} // namespace localstd

#endif
