/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_FUNCTION_INL
#define NSL_FUNCTION_INL

# include "../Function.hpp"

template <typename TRet, typename ... TArgs>
Function<TRet(TArgs...)>::Function() noexcept
										: fun(nullptr)
{
}

template <typename TRet, typename ... TArgs>
Function<TRet(TArgs...)>::Function(Function::FUNTYPE f) noexcept : fun(f)
{
}

template <typename TRet, typename ... TArgs>
Function<TRet(TArgs...)>::FUNTYPE
Function<TRet(TArgs...)>::Get() const noexcept
{
	return (this->fun);
}

template <typename TRet, typename ... TArgs>
TRet
Function<TRet(TArgs...)>::Play(TArgs... args) const noexcept
{
	return (this->fun(Meta::Forward<TArgs>(args)...));
}

template <typename TRet, typename ... TArgs>
void
Function<TRet(TArgs...)>::Replace(FUNTYPE fun) noexcept
{
	this->fun = fun;
}

#endif
