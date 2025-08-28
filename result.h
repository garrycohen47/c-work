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

        constexpr Result(T t) noexcept : value(std::move(t)) {}
        constexpr Result(E e) noexcept : value(std::move(e)) {}

        template<typename Self>
        [[nodiscard]]
        constexpr auto is_ok(this Self&& self) noexcept -> bool {
            return std::holds_alternative<T>(std::forward<Self>(self).value);
        }

        template<typename Self>
        [[nodiscard]]
        constexpr auto is_err(this Self&& self) noexcept -> bool {
            return std::holds_alternative<E>(std::forward<Self>(self).value);
        }

        template<typename Self>
        [[nodiscard]]
        constexpr auto ok(this Self&& self) noexcept
            -> std::optional<T> {
            if (self.is_err()) {
                return std::nullopt;
            }

            return std::get<T>(std::forward<Self>(self).value);
        }

        template<typename Self>
        [[nodiscard]]
        constexpr auto ok_ref(this Self&& self) noexcept
            -> std::optional<std::reference_wrapper<detail::to_const<Self, T>>> {
            if (self.is_err()) {
                return std::nullopt;
            }

            return std::get<T>(std::forward<Self>(self).value);
        }

        template<typename Self>
        [[nodiscard]]
        constexpr auto err(this Self&& self) noexcept
            -> std::optional<E> {
            if (self.is_ok()) {
                return std::nullopt;
            }

            return std::get<E>(std::forward<Self>(self).value);
        }

        template<typename Self>
        [[nodiscard]]
        constexpr auto err_ref(this Self&& self) noexcept
            -> std::optional<std::reference_wrapper<detail::to_const<Self, E>>> {
            if (self.is_ok()) {
                return std::nullopt;
            }

            return std::get<E>(std::forward<Self>(self).value);
        }

        template<typename Self, typename F>
        [[nodiscard]]
        constexpr auto map(this Self&& self, F&& f) noexcept
            -> Result<std::invoke_result_t<F, T>, E> {
            if (self.is_err()) {
                return std::get<E>(std::forward<Self>(self).value);
            }

            if constexpr(std::is_void_v<std::invoke_result_t<F, T>>) {
                std::invoke(
                    std::forward<F>(f),
                    std::get<T>(std::forward<Self>(self).value));
                return {};
            } else {
                return std::invoke(
                    std::forward<F>(f),
                    std::get<T>(std::forward<Self>(self).value));
            }
        }

        template<typename Self, typename F>
        [[nodiscard]]
        constexpr auto map_err(this Self&& self, F&& f) noexcept
            -> Result<T, std::invoke_result_t<F, E>> {
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

    template<typename E>
        requires detail::is_not_cvref<E>
    class Result<void, E> {
    public:
        constexpr Result() noexcept : value(std::nullopt) {}
        constexpr Result(E e) noexcept : value(std::move(e)) {}

        template<typename Self>
        [[nodiscard]]
        constexpr auto is_ok(this Self&& self) noexcept -> bool {
            return !std::forward<Self>(self).value.has_value();
        }

        template<typename Self>
        [[nodiscard]]
        constexpr auto is_err(this Self&& self) noexcept -> bool {
            return std::forward<Self>(self).value.has_value();
        }

        template<typename Self>
        [[nodiscard]]
        constexpr auto err(this Self&& self) noexcept
            -> std::optional<E> {
            return std::forward<Self>(self).value;
        }

        template<typename Self>
        [[nodiscard]]
        constexpr auto err_ref(this Self&& self) noexcept
            -> std::optional<std::reference_wrapper<detail::to_const<Self, E>>> {
            if (self.is_ok()) {
                return std::nullopt;
            }

            return std::forward<Self>(self).value.value();
        }

        template<typename Self, typename F>
        [[nodiscard]]
        constexpr auto map(this Self&& self, F&& f) noexcept
            -> Result<std::invoke_result_t<F>, E> {
            if (self.is_err()) {
                return std::forward<Self>(self).value.value();
            }

            return std::invoke(std::forward<F>(f));
        }

        template<typename Self, typename F>
        [[nodiscard]]
        constexpr auto map_err(this Self&& self, F&& f) noexcept
            -> Result<void, std::invoke_result_t<F, E>> {
            if (self.is_ok()) {
                return {};
            }

            return std::invoke(
                std::forward<F>(f),
                std::forward<Self>(self).value.value());
        }

    private:
        std::optional<E> value;
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
        if (value.is_err()) {
            return std::format_to(
                ctx.out(),
                "{}",
                value.err().value());
        }

        return std::format_to(
            ctx.out(),
            "{}",
            value.ok().value());
    }
};

#endif
