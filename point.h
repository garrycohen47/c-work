#ifndef POINT_H_
#define POINT_H_

#include <utility>

namespace localstd
{
    template<typename T>
        requires std::integral<T> || std::floating_point<T>
    struct point {
        using value_type = T;

        constexpr explicit point(
            T x = T(),
            T y = T(),
            T z = T()) noexcept :
            x_v(x),
            y_v(y),
            z_v(z) {}

        constexpr point(const point& p) noexcept = default;

        constexpr auto operator<=>(const point&) const = default;


        // Need to duplicate until deducing this is available
        template<size_t I>
        auto& get() {
            static_assert(I <= std::tuple_size_v<point>);

            if constexpr (I == 0) {
                return x_v;
            }

            if constexpr (I == 1) {
                return y_v;
            }

            if constexpr (I == 2) {
                return z_v;
            }
        }

        template<size_t I>
        const auto& get() const {
            static_assert(I <= std::tuple_size_v<point>);

            if constexpr (I == 0) {
                return x_v;
            }

            if constexpr (I == 1) {
                return y_v;
            }

            if constexpr (I == 2) {
                return z_v;
            }
        }

        [[nodiscard]]
        constexpr auto x() const noexcept {
            return x_v;
        }

        [[nodiscard]]
        constexpr auto y() const noexcept {
            return y_v;
        }

        [[nodiscard]]
        constexpr auto z() const noexcept {
            return z_v;
        }

        template<typename CharT, typename Traits = std::char_traits<CharT>>
        friend std::basic_ostream<CharT, Traits>& operator<<(
            std::basic_ostream<CharT, Traits>& os,
            const point& p) noexcept {
            os << '(' << p.x() << ',' << ' ' << p.y() << ',' << ' ' << p.z() << ')';
            return os;
        }

    private:
        value_type x_v;
        value_type y_v;
        value_type z_v;
    };

    template<std::integral U, typename T>
    constexpr auto operator+(
        const point<T>& lhs,
        const point<U>& rhs) noexcept
        -> point<T> {
        return point<T>(
            lhs.x() + rhs.x(),
            lhs.y() + rhs.y(),
            lhs.z() + rhs.z());
    }

    template<std::floating_point U, typename T>
    constexpr auto operator+(
        const point<T>& lhs,
        const point<U>& rhs) noexcept
        -> point<U> {
        return point<U>(
            lhs.x() + rhs.x(),
            lhs.y() + rhs.y(),
            lhs.z() + rhs.z());
    }

    template<std::integral U, typename T>
    constexpr auto operator-(
        const point<T>& lhs,
        const point<U>& rhs) noexcept
        -> point<std::make_signed_t<U>> {
        return point<std::make_signed_t<U>>(
            lhs.x() - rhs.x(),
            lhs.y() - rhs.y(),
            lhs.z() - rhs.z());
    }

    template<std::integral U, std::floating_point T>
    constexpr auto operator-(
        const point<T>& lhs,
        const point<U>& rhs) noexcept
        -> point<T> {
        return point<T>(
            lhs.x() - rhs.x(),
            lhs.y() - rhs.y(),
            lhs.z() - rhs.z());
    }

    template<std::floating_point U, typename T>
    constexpr auto operator-(
        const point<T>& lhs,
        const point<U>& rhs) noexcept
        -> point<U> {
        return point<U>(
            lhs.x() - rhs.x(),
            lhs.y() - rhs.y(),
            lhs.z() - rhs.z());
    }

    template<std::integral U, typename T>
    constexpr auto operator*(
        const point<T>& lhs,
        U scale) noexcept
        -> point<T> {
        return point<T>(
            lhs.x() * scale,
            lhs.y() * scale,
            lhs.z() * scale);
    }

    template<std::floating_point U, typename T>
    constexpr auto operator*(
        const point<T>& lhs,
        U scale) noexcept
        -> point<U> {
        return point<U>(
            lhs.x() * scale,
            lhs.y() * scale,
            lhs.z() * scale);
    }

    template<std::integral U>
    constexpr auto operator+(
        const point<U>& p) noexcept
        -> point<std::make_unsigned_t<U>> {
        using S = std::make_unsigned_t<U>;
        return point<S>(
            +S(p.x()),
            +S(p.y()),
            +S(p.z()));
    }

    template<std::integral U>
    constexpr auto operator-(
        const point<U>& p) noexcept
        -> point<std::make_signed_t<U>> {
        using S = std::make_signed_t<U>;
        return point<S>(
            -S(p.x()),
            -S(p.y()),
            -S(p.z()));
    }
}

template<typename T>
struct std::tuple_size<::localstd::point<T>> :
    std::integral_constant<size_t, 3> {};

template<size_t Index, typename T>
struct std::tuple_element<Index, ::localstd::point<T>> :
    std::tuple_element<Index, std::tuple<T, T, T>> {};

constexpr auto operator""_x(unsigned long long int x) noexcept {
    using S = unsigned long long int;
    return ::localstd::point<S>(static_cast<S>(x), 0, 0);
}

constexpr auto operator""_x(long double x) noexcept {
    using S = long double;
    return ::localstd::point<S>(static_cast<S>(x), 0, 0);
}

constexpr auto operator""_y(unsigned long long int y) noexcept {
    using S = unsigned long long int;
    return ::localstd::point<S>(0, static_cast<S>(y), 0);
}

constexpr auto operator""_y(long double y) noexcept {
    using S = long double;
    return ::localstd::point<S>(0, static_cast<S>(y), 0);
}

constexpr auto operator""_z(unsigned long long int z) noexcept {
    using S = unsigned long long int;
    return ::localstd::point<S>(0, 0, static_cast<S>(z));
}

constexpr auto operator""_z(long double z) noexcept {
    using S = long double;
    return ::localstd::point<S>(0, 0, static_cast<S>(z));
}

#endif
