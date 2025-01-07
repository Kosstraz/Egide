/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_FUNCTION_INL
#define EGIDE_FUNCTION_INL

# include "../Function.hpp"

template <typename TRet, typename ... TArgs>
Function<TRet(TArgs...)>::Function() noexcept
										: fun(nullptr)
{
}

template <typename TRet, typename ... TArgs>
Function<TRet(TArgs...)>::Function(typename Function<TRet(TArgs...)>::FUNTYPE pFun) noexcept : fun(pFun)
{
}

template <typename TRet, typename ... TArgs>
typename Function<TRet(TArgs...)>::FUNTYPE
Function<TRet(TArgs...)>::Get() const noexcept
{
	return (this->fun);
}

template <typename TRet, typename ... TArgs>
TRet
Function<TRet(TArgs...)>::Play(TArgs... pArgs) const noexcept
{
	return (this->fun(Meta::Forward<TArgs>(pArgs)...));
}

template <typename TRet, typename ... TArgs>
void
Function<TRet(TArgs...)>::Replace(FUNTYPE pFun) noexcept
{
	this->fun = pFun;
}

#endif
