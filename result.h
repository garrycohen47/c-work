#ifndef RESULT_H
#define RESULT_H

#include <variant>
#include <optional>
#include <functional>
#include <format>

namespace localstd {
    namespace detail {
        template<typename T>
        concept is_not_cvref = !std::is_const_v<std::remove_reference_t<T>> && !std::is_reference_v<T> && !std::is_volatile_v<T>;

        template<typename In, typename Out>
        using to_const = std::conditional_t<std::is_const_v<std::remove_reference_t<In>>, const Out, Out>;
    }

    template<typename T, typename E>
        requires detail::is_not_cvref<T> && detail::is_not_cvref<E> && (!std::is_same_v<T, E>)
    class Result {
    public:
        using value_type = T;
        using error_type = E;

        Result(T t) noexcept : value(std::move(t)) {}
        Result(E e) noexcept : value(std::move(e)) {}

        template<typename Self>
        [[nodiscard]]
        auto is_ok(this Self&& self) noexcept -> bool {
            return std::holds_alternative<T>(std::forward<Self>(self).value);
        }

        template<typename Self>
        [[nodiscard]]
        auto is_err(this Self&& self) noexcept -> bool {
            return std::holds_alternative<E>(std::forward<Self>(self).value);
        }

        template<typename Self>
        [[nodiscard]]
        auto ok(this Self&& self) noexcept
            -> std::optional<T> {
            if (self.is_err()) {
                return std::nullopt;
            }

            return std::get<T>(std::forward<Self>(self).value);
        }

        template<typename Self>
        [[nodiscard]]
        auto ok_ref(this Self&& self) noexcept
            -> std::optional<std::reference_wrapper<detail::to_const<Self, T>>> {
            if (self.is_err()) {
                return std::nullopt;
            }

            return std::get<T>(std::forward<Self>(self).value);
        }

        template<typename Self>
        [[nodiscard]]
        auto err(this Self&& self) noexcept
            -> std::optional<E> {
            if (self.is_ok()) {
                return std::nullopt;
            }

            return std::get<E>(std::forward<Self>(self).value);
        }

        template<typename Self>
        [[nodiscard]]
        auto err_ref(this Self&& self) noexcept
            -> std::optional<std::reference_wrapper<detail::to_const<Self, E>>> {
            if (self.is_ok()) {
                return std::nullopt;
            }

            return std::get<E>(std::forward<Self>(self).value);
        }

        template<typename Self, typename F>
        [[nodiscard]]
        auto map(this Self&& self, F&& f) noexcept
            -> Result<typename std::invoke_result_t<F, T>::value_type, E> {
            if (self.is_err()) {
                return std::get<E>(std::forward<Self>(self).value);
            }

            return std::invoke(
                std::forward<F>(f),
                std::get<T>(std::forward<Self>(self).value));
        }

        template<typename Self, typename F>
        [[nodiscard]]
        auto map_err(this Self&& self, F&& f) noexcept
            -> Result<T, typename std::invoke_result_t<F, E>::error_type> {
            if (self.is_ok()) {
                return std::get<T>(std::forward<Self>(self).value);
            }

            return std::invoke(
                std::forward<F>(f),
                std::get<E>(std::forward<Self>(self).value));
        }

    private:
        std::variant<T, E> value;
    };
}

template<typename T, typename E>
struct std::formatter<::localstd::Result<T, E>> {
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(
        const ::localstd::Result<T, E>& value,
        FormatContext& ctx) const {
        if (value.is_ok()) {
            return std::format_to(
                ctx.out(),
                "{}",
                *value.ok());
        }

        return std::format_to(
            ctx.out(),
            "{}",
            *value.err());
    }
};

#endif
