/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_UNPACK_HPP
#define NSL_UNPACK_HPP

# include "Package.hpp"
# include "Meta.hpp"
# include "Callable.hpp"

template <typename TRet, typename... TArgs>
struct Callable;

// Put a function 'fun' and a Package<...> of many any args, and the Unpack class will depack your args in Package<...> and put them in the function 'fun'
template <typename TRet, typename... TArgsPackaged>
struct Unpack
{
private:
	template <typename TFun>
	FORCEINLINE
	static constexpr TRet	ApplyFinal(TFun fun, TArgsPackaged... args)
	{
		return (fun(Meta::Move(args)...));
	}

	template <typename TFun, class CPackageRest, typename... TArgs>
	FORCEINLINE
	static constexpr TRet	ApplyRest(TFun fun, const CPackageRest& pack, TArgs&&... args)
	{
		if constexpr (pack.last)
			return (ApplyFinal(fun, args..., pack.value));
		else
			return (ApplyRest<decltype(pack.rest), TArgs..., decltype(pack.value)>(fun, pack.rest, Meta::Move(args)..., Meta::Move(pack.value)));
	}

	/*
		NON-STATIC METHOD
	*/
	template <typename TFun, class TObject>
	FORCEINLINE
	static constexpr TRet	ApplyFinal(TFun fun, TObject* obj, TArgsPackaged... args)
	{
		return ((obj->*fun)(Meta::Move(args)...));
	}
	/*
		NON-STATIC METHOD
	*/	
	template <typename TFun, class TObject, class CPackageRest, typename... TArgs>
	FORCEINLINE
	static constexpr TRet	ApplyRest(TFun fun, TObject* obj, const CPackageRest& pack, TArgs&&... args)
	{
		if constexpr (pack.last)
			return (ApplyFinal(fun, obj, args..., pack.value));
		else
			return (ApplyRest<decltype(pack.rest), TObject, TArgs..., decltype(pack.value)>(fun, obj, pack.rest, Meta::Move(args)..., Meta::Move(pack.value)));
	}

public:
	template <typename TFun>
	FORCEINLINE
	static constexpr TRet	Apply(TFun fun, const Package<TArgsPackaged...>& pack)
	{
		if constexpr (pack.last)
			return (ApplyFinal(fun, pack.value));
		else
			return (ApplyRest<TFun, decltype(pack.rest), decltype(pack.value)>(fun, pack.rest, Meta::Move(pack.value)));
	}

	template <typename TFun>
	FORCEINLINE
	static constexpr Callable<TRet(TArgsPackaged...)>	Bind(TFun fun, TArgsPackaged... args)
	{
		return (Callable<TRet(TArgsPackaged...)>(fun, Meta::Move(args)...));
	}

	/*
		NON-STATIC METHOD
	*/
	template <typename TFun, class TObject>
	FORCEINLINE
	static constexpr TRet	Apply(TFun fun, TObject* obj, const Package<TArgsPackaged...>& pack)
	{
		if constexpr (pack.last)
			return (ApplyFinal(fun, obj, pack.value));
		else
			return (ApplyRest(fun, obj, pack.rest, Meta::Move(pack.value)));
	}
};

#endif
