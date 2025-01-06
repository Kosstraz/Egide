/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_META_HPP
#define EGIDE_META_HPP

# include "TypesCapUtils.hpp"

// Metaprogramation
namespace Meta
{

template <typename T>
FORCEINLINE constexpr RemoveRef<T>&&	Move(T& arg) noexcept
{
	return (static_cast<RemoveRef<T>&&>(arg));
}

template <typename T>
FORCEINLINE constexpr RemoveRef<T>&&	Forward(RemoveRef<T>&& arg) noexcept
{
	return (static_cast<RemoveRef<T>&&>(arg));
}

template <typename T>
FORCEINLINE constexpr RemoveRef<T>&&	Forward(RemoveRef<T>& arg) noexcept
{
	return (static_cast<RemoveRef<T>&&>(arg));
}

template <typename T>
requires Types::IsNative<T>
inline constexpr void	Swap(T& a, T& b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}

template <class T>
requires Types::IsObject<T>
inline constexpr void	Swap(T& a, T& b)
{
	T	temp = Meta::Move(a);
	a = Meta::Move(b);
	b = Meta::Move(temp);
}



template <typename TSignature>
struct ISelectOverloading;

template <typename TRet, typename... TArgs>
struct ISelectOverloading<TRet(TArgs...)>
{
	FORCEINLINE
	constexpr TRet
	static (*Cast(TRet (*f)(TArgs...)))(TArgs...)
	{
		return (f);
	}

	template <class TObject>
	FORCEINLINE
	constexpr TRet
	static (TObject::*Cast(TRet (TObject::*f)(TArgs...)))(TArgs...)
	{
		return (f);
	}
};

}

#endif
