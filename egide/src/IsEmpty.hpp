/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_ISEMPTY_HPP
#define EGIDE_ISEMPTY_HPP

# include "TypesCapUtils.hpp"

namespace private_IsEmpty
{
	template <typename T>
	inline constexpr int	IsEmpty_function(T)		{ return (0); }

	template <typename T>
	inline constexpr int	IsEmpty_function(...)	{ return (1); }
}

namespace Types
{

template <typename T>
inline constexpr bool	IsEmpty =
						(
							private_IsEmpty::IsEmpty_function(static_cast<T*>(nullptr))
						);

}

#endif
