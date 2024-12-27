#ifndef CACHE_H_
#define CACHE_H_

#include <algorithm>
#include <array>
#include <cassert>

namespace localstd
{
	template <typename Item>
	struct least_recently_used
	{
		template <typename Iterator>
		constexpr static void promote(Iterator first, [[maybe_unused]] Iterator last, Iterator it)
		{
			for (auto it_start = first; it_start != it; std::advance(it_start, 1))
			{
				std::iter_swap(it_start, it);
			}
		}

		template <typename Iterator>
		constexpr static void reorder(Iterator first, Iterator last)
		{
			std::rotate(first, last - 1, last);
		}

		template <typename Iterator>
		constexpr static void evict(Iterator first, [[maybe_unused]] Iterator last, const Item& value)
		{
			*first = value;
		}
	};

	/// \brief creates a cache data structure
	/// \tparam Item the type stored within the cache structure
	/// \tparam N the amount of items the cache can store
	/// \tparam EvictionPolicy the type that declares how to evict and promote
	/// items within the list
	///
	/// By default creates a Least Recently Used Eviction Policy within a
	/// standard cache
	template <typename Item, std::size_t N, typename EvictionPolicy = least_recently_used<Item>>
	class cache
	{
		static_assert(N > 0, "Size type for cache must be non-zero");

	public:
		using container = std::array<Item, N>;
		using value_type = typename container::value_type;
		using iterator = typename container::iterator;
		using const_iterator = typename container::const_iterator;
		using reference = typename container::reference;
		using const_reference = typename container::const_reference;
		using size_type = typename container::size_type;

		constexpr cache() = default;

		/// Instantiates a cache structure via the supplied elements
		/// \param l the list of elements to instantiate the cache by
		constexpr cache(std::initializer_list<value_type>&& l)
		{
			auto it = l.size() > N
			          ? std::move(l.begin(), std::next(l.begin(), N), begin())
			          : std::move(l.begin(), l.end(), begin());
			std::fill(it, end(), Item());
		}

//		template <typename Iterator>
//		constexpr cache(Iterator first, Iterator last)
//		{
//			// TODO:
//		}

		constexpr void push(const Item& item)
		{
			if (auto it = std::find(begin(), end(), item); it != end())
			{
				EvictionPolicy::promote(begin(), end(), it);
			}
			else
			{
				EvictionPolicy::reorder(begin(), end());
				EvictionPolicy::evict(begin(), end(), item);
			}
		}

		constexpr cache& operator<<(const Item& item)
		{
			push(item);
			return *this;
		}

		constexpr cache& operator<<(Item&& item)
		{
			push(std::move(item));
			return *this;
		}

		[[nodiscard]] constexpr iterator begin() noexcept
		{
			return values.begin();
		}

		[[nodiscard]] constexpr iterator end() noexcept
		{
			return values.end();
		}

		[[nodiscard]] constexpr const_iterator cbegin() const noexcept
		{
			return values.cbegin();
		}

		[[nodiscard]] constexpr const_iterator cend() const noexcept
		{
			return values.cend();
		}

		constexpr reference operator[](size_type index) noexcept
		{
			assert(index <= N);
			return values[index];
		}

		constexpr const_reference operator[](size_type index) const noexcept
		{
			assert(index <= N);
			return values[index];
		}

		constexpr size_type size() const noexcept
		{
			return values.size();
		}

		[[nodiscard]] constexpr bool empty() const noexcept
		{
			return values.empty();
		}

		constexpr bool operator==(const cache<Item, N>& rhs) const
		{
			return std::equal(cbegin(), cend(), rhs.cbegin());
		}

	private:
		container values;
	};
}// namespace localstd

#endif
