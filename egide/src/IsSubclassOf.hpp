/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_ISSUBCLASSOF_HPP
#define EGIDE_ISSUBCLASSOF_HPP

# include "TypesCapUtils.hpp"

namespace private_IsSubclassOf
{
	template <typename T>
	inline constexpr char	issubclass_function(T*)  {return (1);}
	template <typename T>
	inline constexpr char	issubclass_function(...) {return (0);}
}

namespace Types
{

template <typename T, typename U>
inline constexpr bool	IsSubclassOf =
	(
		private_IsSubclassOf::issubclass_function<RawType<T>>(static_cast<RawType<U>*>(nullptr))
			&&
		!IsSame<T, U>
	);

template <typename T, typename U>
inline constexpr bool	IsDerivedFrom =
	(
		IsSubclassOf<T, U>
	);

template <typename T, typename U>
inline constexpr bool	IsSubclassOrSame =
	(
		private_IsSubclassOf::issubclass_function<RawType<T>>(static_cast<RawType<U>*>(nullptr))
	);

template <typename Parent, typename Child>
inline constexpr bool	IsParentOf =
	(
		IsSubclassOf<Parent, Child>
	);

}

#endif
