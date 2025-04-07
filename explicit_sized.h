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
            value_type v)
            noexcept :
            v(std::move_if_noexcept(v)) {
            //
        }

        constexpr auto operator<=>(
            const explicit_sized&) const
            noexcept = default;

        [[nodiscard]]
        constexpr auto operator|(
            const explicit_sized& other) const
            noexcept
            -> explicit_sized {
            return explicit_sized{v | other.v};
        }

        [[nodiscard]]
        constexpr auto operator&(
            const explicit_sized& other) const
            noexcept
            -> explicit_sized {
            return explicit_sized{v & other.v};
        }

        constexpr explicit operator value_type() const noexcept {
            return v;
        }

    private:
        value_type v;
    };

    template<typename T>
    using explicit_sized_v = typename explicit_sized<T>::value_type;

    template<typename T>
        requires std::is_unsigned_v<T>
    [[nodiscard]]
    constexpr auto operator+(
        const explicit_sized<T>& lhs,
        const explicit_sized<T>& rhs)
        noexcept(!detail::is_debug) {
        if constexpr (detail::is_debug) {
            // TODO: Debug specific flag, bounds checking should be performed
        }

        return explicit_sized<T>(static_cast<T>(lhs) + static_cast<T>(rhs));
    }

    template<typename T>
        requires std::is_signed_v<T>
    [[nodiscard]]
    constexpr auto operator+(
        const explicit_sized<T>& lhs,
        const explicit_sized<T>& rhs)
        noexcept(!detail::is_debug) {
        if constexpr (detail::is_debug) {
            // TODO: Debug specific flag, bounds checking should be performed
        }

        return explicit_sized<T>(static_cast<T>(lhs) + static_cast<T>(rhs));
    }

    template<typename T>
        requires std::is_unsigned_v<T>
    [[nodiscard]]
    constexpr auto operator-(
        const explicit_sized<T>& lhs,
        const explicit_sized<T>& rhs)
        noexcept(!detail::is_debug) {
        if constexpr (detail::is_debug) {
            // TODO: Debug specific flag, bounds checking should be performed
        }

        return explicit_sized<T>(static_cast<T>(lhs) - static_cast<T>(rhs));
    }

    template<typename T>
        requires std::is_signed_v<T>
    [[nodiscard]]
    constexpr auto operator-(
        const explicit_sized<T>& lhs,
        const explicit_sized<T>& rhs)
        noexcept(!detail::is_debug) {
        if constexpr (detail::is_debug) {
            // TODO: Debug specific flag, bounds checking should be performed
        }

        return explicit_sized<T>(static_cast<T>(lhs) - static_cast<T>(rhs));
    }

    template<typename T>
        requires std::is_unsigned_v<T>
    [[nodiscard]]
    constexpr auto operator*(
        const explicit_sized<T>& lhs,
        const explicit_sized<T>& rhs)
        noexcept(!detail::is_debug) {
        if constexpr (detail::is_debug) {
            // TODO: Debug specific flag, bounds checking should be performed
        }

        return explicit_sized<T>(static_cast<T>(lhs) * static_cast<T>(rhs));
    }

    template<typename T>
        requires std::is_signed_v<T>
    [[nodiscard]]
    constexpr auto operator*(
        const explicit_sized<T>& lhs,
        const explicit_sized<T>& rhs)
        noexcept(!detail::is_debug) {
        if constexpr (detail::is_debug) {
            // TODO: Debug specific flag, bounds checking should be performed
        }

        return explicit_sized<T>(static_cast<T>(lhs) * static_cast<T>(rhs));
    }

    using u8 = explicit_sized<uint8_t>;
    using u16 = explicit_sized<uint16_t>;
    using u32 = explicit_sized<uint32_t>;
    using usize = explicit_sized<uintmax_t>;

    using i8 = explicit_sized<int8_t>;
    using i16 = explicit_sized<int16_t>;
    using i32 = explicit_sized<int32_t>;
    using isize = explicit_sized<intmax_t>;
}

template<typename T>
struct std::formatter<::localstd::explicit_sized<T>> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(
        const ::localstd::explicit_sized<T>& t,
        FormatContext& ctx) const {
        using namespace ::localstd;
        using to = std::conditional_t<std::is_unsigned_v<T>, usize::value_type, isize::value_type>;

        return std::format_to(
            ctx.out(),
            "{}",
            static_cast<to>(static_cast<T>(t)));
    }
};


#endif
