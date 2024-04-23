#ifndef POINT_H_
#define POINT_H_

template <typename T> concept Integral_Like = std::is_integral_v<T>;
template <typename T> concept Float_Like = std::is_floating_point_v<T>;
template <typename T> concept Numeric_Like = Integral_Like<T> || Float_Like<T>;

namespace localstd
{
	template <Numeric_Like T>
	struct point
	{
		using value_type = T;

		constexpr point() : x(T()), y(T()), z(T())
		{
		}

		constexpr point(T x_val, T y_val, T z_val) : x(x_val), y(y_val), z(z_val)
		{
		}

		constexpr point(const point&) = default;

		template <Numeric_Like U>
		constexpr point(const point<U>& p) : x(p.x), y(p.y), z(p.z)
		{
		}

		constexpr point& operator=(const point&) = default;

		template <Integral_Like U>
		constexpr auto operator+(const point<U>& p) const noexcept -> point
		{
			return point(x + p.x, y + p.y, z + p.z);
		}

		template <Float_Like U>
		constexpr auto operator+(const point<U>& p) const noexcept -> point<U>
		{
			return point(x + p.x, y + p.y, z + p.z);
		}

		template <Integral_Like U>
		constexpr auto operator-(const point<U>& p) const noexcept -> point
		{
			return point(x - p.x, y - p.y, z - p.z);
		}

		template <Float_Like U>
		constexpr auto operator-(const point<U>& p) const noexcept -> point<U>
		{
			return point(x - p.x, y - p.y, z - p.z);
		}

		constexpr auto operator-() const noexcept -> point
		{
			return {-x, -y, -z};
		}

		constexpr auto operator*(Integral_Like auto scale) const noexcept
		{
			return point(x * scale, y * scale, z * scale);
		}

		constexpr auto operator*(Float_Like auto scale) const noexcept -> point<decltype(scale)>
		{
			return {x * scale, y * scale, z * scale};
		}

		explicit operator std::string() const
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
		}

		value_type x;
		value_type y;
		value_type z;
	};
}

constexpr auto operator "" _x(unsigned long long int val) -> localstd::point<int>
{
	return {static_cast<int>(val), 0, 0};
}

constexpr auto operator "" _x(long double val) -> localstd::point<double>
{
	return {static_cast<double>(val), 0, 0};
}

constexpr auto operator "" _y(unsigned long long int val) -> localstd::point<int>
{
	return {0, static_cast<int>(val), 0};
}

constexpr auto operator "" _y(long double val) -> localstd::point<double>
{
	return {0, static_cast<double>(val), 0};
}

constexpr auto operator "" _z(unsigned long long int val) -> localstd::point<int>
{
	return {0, 0, static_cast<int>(val)};
}

constexpr auto operator "" _z(long double val) -> localstd::point<double>
{
	return {0, 0, static_cast<double>(val)};
}

#endif