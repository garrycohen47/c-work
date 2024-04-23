#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#include <concepts>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace localstd
{
	template <typename Iterator>
	bool save(const fs::path& file, Iterator first, Iterator last)
	{
		fs::create_directories(file.parent_path());

		constexpr auto settings = std::ios_base::out | std::ios_base::binary | std::ios_base::trunc;
		std::ofstream stream(file, settings);

		if (!stream)
		{
			return false;
		}

		std::for_each(
			first, last, [&stream](const auto& val)
			{
				stream << val;
			}
		);

		return true;
	}

	template <typename Container>
	bool save(const fs::path& file, const Container& cont)
	{
		// TODO: Have this be an overload for contiguous data
		return false;
	}

	template <typename Iterator>
	Iterator read(const fs::path& path, Iterator out)
	{
		constexpr auto settings = std::ios_base::in | std::ios_base::binary;
		std::ifstream stream(path, settings);

		// TODO: Decide how to implement Output Iterators for this function
		// How would this work out?

		return out;
	}
}// namespace localstd

#endif
