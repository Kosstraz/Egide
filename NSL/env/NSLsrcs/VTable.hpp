#ifndef NSL_VTABLE_HPP
#define NSL_VTABLE_HPP

template <typename... Ts>
struct type_list
{
    template <typename... Us>
    constexpr auto operator+(type_list<Us...>) const noexcept
    {
        return type_list<Ts..., Us...>{};
    }

    template <typename... Us>
    constexpr bool operator==(type_list<Us...>) const noexcept
    {
        return std::is_same_v<type_list<Ts...>, type_list<Us...>>;
    }
};

struct stateful_type_list
{
private:
    template <unsigned long N>
    struct getter
    {
        friend consteval auto flag(getter);
    };

    template <typename T, unsigned long N>
    struct setter
    {
        friend consteval auto flag(getter<N>)
        {
            return type_list<T>{};
        }

        static constexpr unsigned long value = N;
    };

public:
    template <typename T, unsigned long N = 0>
    consteval static unsigned long try_push()
    {
        if constexpr (requires { flag(getter<N>{}); })
        {
            return try_push<T, N + 1>();
        }
        else
        {
            return setter<T, N>::value;
        }
    }

    template <typename Unique, unsigned long N = 0, auto = []{}>
    consteval static auto get()
    {
        if constexpr (requires { flag(getter<N>{}); })
        {
            return flag(getter<N>{}) + get<Unique, N + 1>();
        }
        else
        {
            return type_list<>{};
        }
    }
};



#endif
