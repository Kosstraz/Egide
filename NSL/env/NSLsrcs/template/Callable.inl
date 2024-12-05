#ifndef NSL_CALLABLE_INL
#define NSL_CALLABLE_INL

# include "../Callable.hpp"

template <typename TRet, typename... TArgs>
Callable<TRet(TArgs...)>::Callable(Callable::FUNTYPE fun, TArgs... args)
:	fun(fun),
	args(Package<TArgs...>(Meta::Move(args)...))
{
}

template <typename TRet, typename... TArgs>
Callable<TRet(TArgs...)>::Callable(Function<TRet(TArgs...)> fun, TArgs... args)
:	fun(fun),
	args(Package<TArgs...>(Meta::Move(args)...))
{
}

template <typename TRet, typename... TArgs>
TRet
Callable<TRet(TArgs...)>::operator()()
{
	return (Unpack::Apply(this->fun, this->args));
}

template <typename TRet, typename... TArgs>
Function<TRet(TArgs...)>
Callable<TRet(TArgs...)>::GetFun() const noexcept
{
	return (this->fun);
}

template <typename TRet, typename... TArgs>
Package<TArgs...>
Callable<TRet(TArgs...)>::GetArgsPackaged() const noexcept
{
	return (this->args);
}

#endif
