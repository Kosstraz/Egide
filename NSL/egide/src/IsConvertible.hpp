/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_ISCONVERTIBLE_HPP
#define EGIDE_ISCONVERTIBLE_HPP

# include "IsSubclassOf.hpp"

namespace private_isconvertible
{
	template <typename A>
	inline constexpr char	function_isconvertible(A) {return (1);}
	template <typename A>
	inline constexpr char	function_isconvertible(...) {return (0);}
	template <typename A>
	inline constexpr A		function_maker() {return ((A)0);}
}

namespace Types
{

template <typename From, typename To>
inline constexpr bool	IsConvertible	=
	(
		IsSubclassOf<To, From>
			||
		(
			!IsObject<From>
				&&
			!IsObject<To>
				&&
			private_isconvertible::function_isconvertible<From>(private_isconvertible::function_maker<From>())
				==
			private_isconvertible::function_isconvertible<From>(private_isconvertible::function_maker<To>())
		)
	);
template <typename T>
inline constexpr bool	IsConvertible<T, T> = true;

}

#endif
