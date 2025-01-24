#ifndef POINT_H_
#define POINT_H_

#include <utility>
#include <type_traits>

namespace localstd {
    template<typename T>
        requires std::integral<T> || std::floating_point<T>
    struct point {
        using type = T;

        constexpr explicit point(
            type x = {},
            type y = {},
            type z = {})
            noexcept :
            _x(x),
            _y(y),
            _z(z) {
            //
        }

        constexpr point(const point&) noexcept = default;

        constexpr point(point&&) noexcept = default;

        constexpr auto operator<=>(const point&) const noexcept = default;

        constexpr auto operator+(
            const point& p) const
            noexcept
            -> point<T> {
            return point(
                _x + p._x,
                _y + p._y,
                _z + p._z);
        }

        constexpr auto operator+() const
            noexcept
            -> point<T> {
            return *this;
        }

        constexpr auto operator-(
            const point& p) const
            noexcept
            -> point<T> {
            return point(
                _x - p._x,
                _y - p._y,
                _z - p._z);
        }

        constexpr auto operator-() const noexcept {
            return point(
                -_x,
                -_y,
                -_z);
        }

        template<typename U>
            requires std::same_as<T, U>
        constexpr auto operator*(
            const U scale) const
            noexcept
            -> point<T> {
            return point(
                _x * scale,
                _y * scale,
                _z * scale);
        }

        template<typename U>
            requires std::integral<U> || std::floating_point<U>
        [[nodiscard]]
        constexpr auto to() const
            noexcept(noexcept(std::is_nothrow_convertible_v<T, U>))
            -> point<U> {
            static_assert(std::is_convertible_v<T, U>);
            return point<U>(
                static_cast<U>(x()),
                static_cast<U>(y()),
                static_cast<U>(z()));
        }

        template<size_t I>
        [[nodiscard]]
        auto get() const {
            static_assert(I <= std::tuple_size_v<point>);

            if constexpr (I == 0) {
                return _x;
            }

            if constexpr (I == 1) {
                return _y;
            }

            if constexpr (I == 2) {
                return _z;
            }
        }

        [[nodiscard]]
        constexpr auto x() const noexcept
            -> const type& {
            return _x;
        }

        [[nodiscard]]
        constexpr auto y() const noexcept
            -> const type& {
            return _y;
        }

        [[nodiscard]]
        constexpr auto z() const noexcept
            -> const type& {
            return _z;
        }

        // TODO: reconsider

        constexpr auto x() noexcept
            -> type& {
            return _x;
        }

        constexpr auto y() noexcept
            -> type& {
            return _y;
        }

        constexpr auto z() noexcept
            -> type& {
            return _z;
        }

        // Should work with std::ostream and std::wostream's
        template<typename CharT, typename Traits = std::char_traits<CharT>>
        friend auto operator<<(
            std::basic_ostream<CharT, Traits>& os,
            const point& p) noexcept
            -> std::basic_ostream<CharT, Traits>& {
            constexpr auto start = CharT{'('};
            constexpr auto comma = CharT{','};
            constexpr auto space = CharT{' '};
            constexpr auto end = CharT{')'};

            os << start
                << p.x() << comma << space
                << p.y() << comma << space
                << p.z() << end;

            return os;
        }

    private:
        type _x;
        type _y;
        type _z;
    };
}

template<typename T>
struct std::formatter<::localstd::point<T>> {
    // TODO: work for std::format functionality
};

template<typename T>
struct std::tuple_size<::localstd::point<T>> :
    std::integral_constant<size_t, 3> {};

template<size_t Index, typename T>
struct std::tuple_element<Index, ::localstd::point<T>> :
    std::tuple_element<Index, std::tuple<T, T, T>> {};

constexpr auto operator""_xi(const unsigned long long int x) noexcept {
    using S = int;
    return ::localstd::point<S>(static_cast<S>(x), 0, 0);
}

constexpr auto operator""_xd(const long double x) noexcept {
    using S = double;
    return ::localstd::point<S>(static_cast<S>(x), 0, 0);
}

constexpr auto operator""_yi(const unsigned long long int y) noexcept {
    using S = int;
    return ::localstd::point<S>(0, static_cast<S>(y), 0);
}

constexpr auto operator""_yd(const long double y) noexcept {
    using S = double;
    return ::localstd::point<S>(0, static_cast<S>(y), 0);
}

constexpr auto operator""_zi(const unsigned long long int z) noexcept {
    using S = int;
    return ::localstd::point<S>(0, 0, static_cast<S>(z));
}

constexpr auto operator""_zd(const long double z) noexcept {
    using S = double;
    return ::localstd::point<S>(0, 0, static_cast<S>(z));
}

#endif
