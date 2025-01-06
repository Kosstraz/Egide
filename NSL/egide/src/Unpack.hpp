/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_UNPACK_HPP
#define EGIDE_UNPACK_HPP

# include "Package.hpp"
# include "Meta.hpp"

struct Unpack
{
private:
	template <typename TRet, typename TFun, class TObject, typename Pack, typename... TRestArgs>
	FORCEINLINE
	static constexpr TRet
	ApplyRest(TFun&& fun, TObject* instance, const Pack& pack, TRestArgs&&... args)
	{
		if constexpr (pack.last)
			return ((instance->*fun)(Meta::Move(args)..., Meta::Move(pack.value)));
		else
			return (Unpack::ApplyRest<TRet>(fun, instance, pack.rest, Meta::Move(args)..., Meta::Move(pack.value)));
	}

	template <typename TRet, typename TFun, typename Pack, typename... TRestArgs>
	FORCEINLINE
	static constexpr TRet
	ApplyRest(TFun&& fun, const Pack& pack, TRestArgs&&... args)
	{
		if constexpr (pack.last)
			return (fun(Meta::Move(args)..., Meta::Move(pack.value)));
		else
			return (Unpack::ApplyRest<TRet>(fun, pack.rest, Meta::Move(args)..., Meta::Move(pack.value)));
	}

public:
	template <typename TRet, class TObject, typename... TArgs>
	FORCEINLINE
	static constexpr TRet
	Apply(TRet (TObject::*fun)(TArgs...), TObject* instance, const Package<TArgs...>& pack)
	{
		if constexpr (pack.last)
			return ((instance->*fun)(Meta::Move(pack.value)));
		else
			return (Unpack::ApplyRest<TRet>(fun, instance, pack.rest, Meta::Move(pack.value)));
	}

	template <typename TRet, typename... TArgs>
	FORCEINLINE
	static constexpr TRet
	Apply(TRet (*fun)(TArgs...), const Package<TArgs...> pack)
	{
		if constexpr (pack.last)
			return (fun(Meta::Move(pack.value)));
		else
			return (Unpack::ApplyRest<TRet>(fun, pack.rest, Meta::Move(pack.value)));
	}
};

#endif
