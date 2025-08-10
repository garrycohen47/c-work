#ifndef EXPLICIT_SIZED_H
#define EXPLICIT_SIZED_H

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace localstd::detail {
#if DEBUG_ENABLED == 1
    constexpr auto is_debug = true;
#else
    constexpr auto is_debug = false;
#endif
}

namespace localstd {
    template<typename T>
    struct explicit_sized {
        using value_type = std::remove_cvref_t<T>;

        constexpr explicit explicit_sized(
            const value_type v)
            noexcept :
            v(v) {
            //
        }

        constexpr auto operator<=>(
            const explicit_sized&) const
            noexcept = default;

        constexpr explicit operator value_type() const noexcept {
            return v;
        }

        template<typename U>
            requires (std::is_signed_v<T> && std::is_signed_v<U>) ||
                     (std::is_unsigned_v<T> && std::is_unsigned_v<U>)
        constexpr explicit operator explicit_sized<U>() const noexcept {
            return explicit_sized<U>{static_cast<U>(v)};
        }

        template<typename U>
            requires (std::is_unsigned_v<T> && std::is_signed_v<U>) ||
                     (std::is_unsigned_v<U> && std::is_signed_v<T>)
        constexpr explicit operator explicit_sized<U>()
            const noexcept(!detail::is_debug) {
            if constexpr (detail::is_debug) {
                // TODO:
            }

            return explicit_sized<U>{static_cast<U>(v)};
        }

    private:
        value_type v;
    };

    template<typename T>
    [[nodiscard]]
    constexpr auto operator|(
        const explicit_sized<T> lhs,
        const explicit_sized<T> rhs)
        noexcept
        -> explicit_sized<T> {
        return explicit_sized<T>{static_cast<T>(static_cast<T>(lhs) | static_cast<T>(rhs))};
    }

    template<typename T>
    [[nodiscard]]
    constexpr auto operator&(
        const explicit_sized<T> lhs,
        const explicit_sized<T> rhs)
        noexcept
        -> explicit_sized<T> {
        return explicit_sized<T>{static_cast<T>(static_cast<T>(lhs) & static_cast<T>(rhs))};
    }

    template<typename T>
    [[nodiscard]]
    constexpr auto operator+(
        const explicit_sized<T> lhs,
        const explicit_sized<T> rhs)
        noexcept(!detail::is_debug) {
        if constexpr (detail::is_debug) {
            // TODO: Debug specific flag, bounds checking should be performed
        }

        return explicit_sized<T>(static_cast<T>(static_cast<T>(lhs) + static_cast<T>(rhs)));
    }

    template<typename T>
    [[nodiscard]]
    constexpr auto operator-(
        const explicit_sized<T> lhs,
        const explicit_sized<T> rhs)
        noexcept(!detail::is_debug) {
        if constexpr (detail::is_debug) {
            // TODO: Debug specific flag, bounds checking should be performed
        }

        return explicit_sized<T>(static_cast<T>(static_cast<T>(lhs) - static_cast<T>(rhs)));
    }

    template<typename T>
    [[nodiscard]]
    constexpr auto operator*(
        const explicit_sized<T> lhs,
        const explicit_sized<T> rhs)
        noexcept(!detail::is_debug) {
        if constexpr (detail::is_debug) {
            // TODO: Debug specific flag, bounds checking should be performed
        }

        return explicit_sized<T>(static_cast<T>(static_cast<T>(lhs) * static_cast<T>(rhs)));
    }

    using u8 = explicit_sized<uint8_t>;
    using u16 = explicit_sized<uint16_t>;
    using u32 = explicit_sized<uint32_t>;
    using u64 = explicit_sized<uint64_t>;

    using i8 = explicit_sized<int8_t>;
    using i16 = explicit_sized<int16_t>;
    using i32 = explicit_sized<int32_t>;
    using i64 = explicit_sized<int64_t>;
}

template<typename T>
struct std::formatter<::localstd::explicit_sized<T>> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(
        const ::localstd::explicit_sized<T> t,
        FormatContext& ctx) const {
        return std::format_to(
            ctx.out(),
            "{}",
            static_cast<T>(t));
    }
};

#endif
