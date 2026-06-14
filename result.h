#ifndef RESULT_H
#define RESULT_H

#include <exception>
#include <variant>
#include <optional>
#include <functional>
#include <format>
#include <type_traits>
#include <utility>

namespace localstd {
    namespace detail {
        template<typename T>
        concept is_not_cvref = !std::is_const_v<std::remove_reference_t<T>> && !std::is_reference_v<T> && !std::is_volatile_v<T>;

        template<typename In, typename Out>
        using forward_const = std::conditional_t<std::is_const_v<std::remove_reference_t<In>>, const Out, Out>;

        template<typename In, typename T>
        using const_propagating_ref = std::reference_wrapper<forward_const<In, T>>;

        template<typename... T>
        struct Overloaded : T... {using T::operator()...;};
    }

    template<typename T, typename E>
        requires (!std::is_same_v<T, E>)
    class [[nodiscard]] Result {
        std::variant<T, E> value;
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
            if (std::forward<Self>(self).is_err()) {
                return std::nullopt;
            }

            return std::get<T>(std::forward<Self>(self).value);
        }

        template<typename Self>
        [[nodiscard]]
        constexpr auto err(this Self&& self) noexcept
            -> std::optional<E> {
            if (std::forward<Self>(self).is_ok()) {
                return std::nullopt;
            }

            return std::get<E>(std::forward<Self>(self).value);
        }

        template<typename Self>
        constexpr auto as_ref(this Self&& self) noexcept
            -> Result<detail::const_propagating_ref<Self, T>, detail::const_propagating_ref<Self, E>> {
            using OkRef = detail::const_propagating_ref<Self, T>;
            using ErrRef = detail::const_propagating_ref<Self, E>;

            if (std::forward<Self>(self).is_ok()) {
                return OkRef{std::get<T>(std::forward<Self>(self).value)};
            }

            return ErrRef{std::get<E>(std::forward<Self>(self).value)};
        }

        template<typename Self, typename F>
        constexpr auto map(this Self&& self, F&& f) noexcept
            -> Result<std::invoke_result_t<F, T>, E> {
            if (std::forward<Self>(self).is_err()) {
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
        constexpr auto map_err(this Self&& self, F&& f) noexcept
            -> Result<T, std::invoke_result_t<F, E>> {
            static_assert(!std::is_void_v<std::invoke_result_t<F, E>>);

            if (std::forward<Self>(self).is_ok()) {
                return std::get<T>(std::forward<Self>(self).value);
            }

            return std::invoke(
                std::forward<F>(f),
                std::get<E>(std::forward<Self>(self).value));
        }

        template<typename Self, typename U>
        constexpr auto And(this Self&& self, Result<U, E> other) noexcept
            -> Result<U, E> {
            if (std::forward<Self>(self).is_ok()) {
                return other;
            }

            return std::get<E>(std::forward<Self>(self).value);
        }

        template<typename Self, typename F>
        constexpr auto and_then(this Self&& self, F&& f) noexcept
            -> Result<typename std::invoke_result_t<F, T>::value_type, E> {

            return std::forward<Self>(self)
                .And(std::invoke(
                    std::forward<F>(f),
                    std::get<T>(std::forward<Self>(self).value)));
        }

        template<typename Self, typename U>
        constexpr auto Or(this Self&& self, Result<T, U> other) noexcept
            -> Result<T, U>{
            if (std::forward<Self>(self).is_err()) {
                return other;
            }

            return std::get<T>(std::forward<Self>(self).value);
        }

        template<typename Self, typename F>
        constexpr auto or_else(this Self&& self, F&& f) noexcept
            -> Result<T, typename std::invoke_result_t<F, E>::error_type> {
            if (std::forward<Self>(self).is_ok()) {
                return std::get<T>(std::forward<Self>(self).value);
            }

            return std::forward<Self>(self)
                .Or(std::invoke(
                    std::forward<F>(f),
                    std::get<E>(std::forward<Self>(self).value)));
        }

        template<typename Self, typename F, typename U>
        [[nodiscard]]
        constexpr auto map_or_else(this Self&& self, F&& f, U&& u) noexcept {
            static_assert(std::is_same_v<std::invoke_result_t<F, T>, std::invoke_result_t<U, E>>);
            return std::visit(
                detail::Overloaded{
                    std::forward<F>(f),
                    std::forward<U>(u)
                },
                std::forward<Self>(self).value);
        }
    };

    template<typename E>
    class [[nodiscard]] Result<void, E> {
        std::optional<E> value;
    public:
        using value_type = void;
        using error_type = E;

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
        constexpr auto as_ref(this Self&& self) noexcept
            -> Result<void, detail::const_propagating_ref<Self, E>> {
            using ErrRef = detail::const_propagating_ref<Self, E>;
            if (std::forward<Self>(self).is_ok()) {
                return {};
            }

            return ErrRef{std::forward<Self>(self).value.value()};
        }

        template<typename Self, typename F>
        constexpr auto map(this Self&& self, F&& f) noexcept
            -> Result<std::invoke_result_t<F>, E> {
            static_assert(!std::is_void_v<std::invoke_result_t<F>>);

            if (std::forward<Self>(self).is_err()) {
                return std::forward<Self>(self).value.value();
            }

            return std::invoke(std::forward<F>(f));
        }

        template<typename Self, typename F>
        constexpr auto map_err(this Self&& self, F&& f) noexcept
            -> Result<void, std::invoke_result_t<F, E>> {
            if (std::forward<Self>(self).is_ok()) {
                return {};
            }

            return std::invoke(
                std::forward<F>(f),
                std::forward<Self>(self).value.value());
        }

        template<typename Self, typename U>
        constexpr auto And(this Self&& self, Result<U, E> other) noexcept
            -> Result<U, E> {
            if (std::forward<Self>(self).is_ok()) {
                return other;
            }

            return std::get<E>(std::forward<Self>(self).value);
        }

        template<typename Self, typename F>
        constexpr auto and_then(this Self&& self, F&& f) noexcept
            -> Result<typename std::invoke_result_t<F>::value_type, E> {

            return std::forward<Self>(self)
                .And(std::invoke(
                    std::forward<F>(f)));
        }

        template<typename Self, typename U>
        constexpr auto Or(this Self&& self, Result<void, U> other) noexcept
            -> Result<void, U> {
            if (std::forward<Self>(self).is_err()) {
                return other;
            }

            return {};
        }

        template<typename Self, typename F>
        constexpr auto or_else(this Self&& self, F&& f) noexcept
            -> Result<void, typename std::invoke_result_t<F, E>::error_type> {
            return std::forward<Self>(self)
                .Or(std::invoke(
                    std::forward<F>(f),
                    std::forward<Self>(self).value.value()));
        }

        template<typename Self, typename F, typename U>
        [[nodiscard]]
        constexpr auto map_or_else(this Self&& self, F&& f, U&& u) noexcept {
            static_assert(std::is_same_v<std::invoke_result_t<F>, std::invoke_result_t<U, E>>);
            if (std::forward<Self>(self).is_ok()) {
                return std::invoke(std::forward<F>(f));
            }

            return std::invoke(
                std::forward<U>(u),
                std::forward<Self>(self).value.value());
        }
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
        if constexpr (std::is_void_v<T>) {
            return value.map_or_else(
                [&]() {
                    return ctx.out();
                },
                [&](const E e) {
                    return std::format_to(
                        ctx.out(),
                        "{}",
                        e);
                });
        }
        else {
            return value.map_or_else(
                [&](const T t) {
                    return std::format_to(
                        ctx.out(),
                        "{}",
                        t);
                },
                [&](const E e) {
                    return std::format_to(
                        ctx.out(),
                        "{}",
                        e);
                });
        }
    }
};

#endif
