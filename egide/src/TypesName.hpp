/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_TYPESNAME_HPP
#define EGIDE_TYPESNAME_HPP

# include "String.hpp"

# ifndef FUNCTION_DETAILS
#  include <typeinfo>
# endif

namespace Types
{
# ifndef FUNCTION_DETAILS
	template <typename T>
	String QualifierName()
	{
		String	ret;
		if constexpr (Types::IsConst<T>)
			ret += "const ";
		else if constexpr (Types::IsVolatile<T>)
			ret += "volatile ";
		return (ret);
	}

	template <typename T>
	String	RawName()
	{
		if constexpr (Types::IsNative<T>)
		{
			if constexpr (Types::IsSame<T, char>)
				return ("char");
			else if constexpr (Types::IsSame<T, short>)
				return ("short");
			else if constexpr (Types::IsSame<T, int>)
				return ("int");
			else if constexpr (Types::IsSame<T, long>)
				return ("long");
			else if constexpr (Types::IsSame<T, long long>)
				return ("long long");
			else if constexpr (Types::IsSame<T, float>)
				return ("float");
			else if constexpr (Types::IsSame<T, double>)
				return ("double");
		}
		else
			return (typeid(T).name());
	}

	template <typename T>
	String	MemoryZoneName()
	{
		String ret;
		if constexpr (Types::IsPtr<T>)
		{
			ret += "*";
			if constexpr (Types::IsConst<T>)
				ret += " const";
			else if constexpr (Types::IsVolatile<T>)
				ret += " volatile";
		}
		else if constexpr (Types::IsArray<T>)
			ret += "[]";
		return (ret);
	}

	// Allows to know the precise type
	// Less precise on compilers other than GNU (GCC/clang/...)
	template <typename T>
	String	Name()
	{
		String	ret;
		ret += Types::QualifierName<RemovePtr<T>>();
		ret += Types::RawName<RawType<T>>();
		ret += Types::MemoryZoneName<T>();
		return (ret);
	}
# else
	// Allows to know the precise type
	// Less precise on compilers other than GNU (GCC/clang/...)
	template <typename T>
	String	Name()
	{
		String	ret = FUNCTION_DETAILS; //Todo: à modifier lorsqu'il y aura String.Find()
		for (ulong i = 0 ; i < ret.Size() ; i++)
			if (ret[i] == '=')
				ret = &ret[i + 2];
		for (ulong i = 0 ; i < ret.Size() ; i++)
			if (ret[i] == ']')
				ret.Erase(i);
		return (ret);
	}
# endif
}

#endif
