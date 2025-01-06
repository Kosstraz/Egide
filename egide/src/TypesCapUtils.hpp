/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_TYPESCAPUTILS_HPP
#define EGIDE_TYPESCAPUTILS_HPP

# include "../egide_platform.h"

/************/
/*	PRIVATE	*/
/************/

namespace private_RemoveRef
{
	template <typename T>
	struct RemoveRefStruct
	{
		typedef	T	Type;
	};

	template <typename T>
	struct RemoveRefStruct<T&>
	{
		typedef	T	Type;
	};

	template <typename T>
	struct RemoveRefStruct<T&&>
	{
		typedef	T	Type;
	};

	template <typename T>
	struct RemoveRefStruct<const T&>
	{
		typedef	const T	Type;
	};
}

namespace private_RemovePtr
{
	template <typename T>
	struct RemovePtrStruct
	{
		typedef	T	Type;
	};

	template <typename T>
	struct RemovePtrStruct<T*>
	{
		typedef	T	Type;
	};

	template <typename T>
	struct RemovePtrStruct<const T*>
	{
		typedef	const T	Type;
	};

	template <typename T>
	struct RemovePtrStruct<T* const>
	{
		typedef T	Type;
	};

	template <typename T>
	struct RemovePtrStruct<T* volatile>
	{
		typedef T	Type;
	};
}

namespace private_RemoveConst
{
	template <typename T>
	struct RemoveConstStruct
	{
		typedef	T	Type;
	};

	template <typename T>
	struct RemoveConstStruct<const T>
	{
		typedef	T	Type;
	};

	template <typename T>
	struct RemoveConstStruct<const T&>
	{
		typedef	T&	Type;
	};

	template <typename T>
	struct RemoveConstStruct<T* const>
	{
		typedef	T*	Type;
	};
}

namespace private_RemoveVolatile
{
	template <typename T>
	struct RemoveVolatileStruct
	{
		typedef T	Type;
	};

	template <typename T>
	struct RemoveVolatileStruct<volatile T>
	{
		typedef T	Type;
	};

	template <typename T>
	struct RemoveVolatileStruct<T* volatile>
	{
		typedef T*	Type;
	};

	template <typename T>
	struct RemoveVolatileStruct<volatile T&>
	{
		typedef T&	Type;
	};
}

namespace private_RemoveArray
{
	template <typename T>
	struct RemoveArrayStruct
	{
		typedef T	Type;
	};

	template <typename T>
	struct RemoveArrayStruct<T[]>
	{
		typedef T	Type;
	};

	template <typename T, unsigned long N>
	struct RemoveArrayStruct<T[N]>
	{
		typedef T	Type;
	};
}

namespace private_EnableIf
{
	template <typename T, const bool BCondition>
	struct EnableIFStruct
	{
		typedef T	Type;
	};
	template <typename T>
	struct EnableIFStruct<T, false>
	{
	};
}

namespace private_Conditional
{
	template <typename TTrue, typename TFalse, const bool BCondition>
	struct ConditionalStruct
	{
		typedef TTrue	Type;
	};

	template <typename TTrue, typename TFalse>
	struct ConditionalStruct<TTrue, TFalse, false>
	{
		typedef TFalse	Type;
	};
}

namespace private_IsArray
{
	template <typename T>
	struct IsArrayStruct
	{
		inline static constexpr bool	val = false;
	};

	template <typename T>
	struct IsArrayStruct<T[]>
	{
		inline static constexpr bool	val = true;
	};

	template <typename T, unsigned long N>
	struct IsArrayStruct<T[N]>
	{
		inline static constexpr bool	val = true;
	};
}

namespace private_IsVolatile
{
	template <typename T>
	struct IsVolatileStruct
	{
		inline static constexpr bool	val = false;
	};

	template <typename T>
	struct IsVolatileStruct<volatile T>
	{
		inline static constexpr bool	val = true;
	};
}

namespace private_IsConst
{
	template <typename T>
	struct IsConstStruct
	{
		inline static constexpr bool	val = false;
	};

	template <typename T>
	struct IsConstStruct<const T>
	{
		inline static constexpr bool	val = true;
	};
}

namespace private_IsRef
{
	template <typename T>
	struct IsRefStruct
	{
		inline static constexpr bool	val = false;
	};

	template <typename T>
	struct IsRefStruct<T&>
	{
		inline static constexpr bool	val = true;
	};
}

namespace private_IsRValue
{
	template <typename T>
	struct IsRValueStruct
	{
		inline static constexpr bool	val = false;
	};

	template <typename T>
	struct IsRValueStruct<T&&>
	{
		inline static constexpr bool	val = true;
	};
}

namespace private_IsPtr
{
	template <typename T>
	struct IsPtrStruct
	{
		inline static constexpr bool	val = false;
	};

	template <typename T>
	struct IsPtrStruct<T*>
	{
		inline static constexpr bool	val = true;
	};

	template <typename T>
	struct IsPtrStruct<T* const>
	{
		inline static constexpr bool	val = true;
	};

	template <typename T>
	struct IsPtrStruct<T* volatile>
	{
		inline static constexpr bool	val = true;
	};
}

namespace private_Decay
{
	template <typename T>
	struct DecayStruct
	{
	private:
		template <typename U>
		using _RemoveVolatile	= typename private_RemoveVolatile::RemoveVolatileStruct<U>::Type;
		template <typename U>
		using _RemoveRef		= typename private_RemoveRef::RemoveRefStruct<U>::Type;
		template <typename U>
		using _RemoveConst		= typename private_RemoveConst::RemoveConstStruct<U>::Type;
		template <typename U>
		using _RemoveArray		= typename private_RemoveArray::RemoveArrayStruct<U>::Type;
		template <typename TTrue, typename TFalse, const bool BCondition>
		using _Conditional		= typename private_Conditional::ConditionalStruct<TTrue, TFalse, BCondition>::Type;
		template <typename U>
		inline constexpr static bool	_IsArray = private_IsArray::IsArrayStruct<U>::val;
		template <typename U>
		using _RawType = _RemoveConst<_RemoveRef<_RemoveVolatile<U>>>;

	public:
		typedef _RawType<
					_Conditional<
						_RemoveArray<T>*, T, _IsArray<T>
					>
				>	Type;
	};
}

/************/
/*	PUBLIC	*/
/************/

/********************/
/*	REMOVE TYPES	*/
/********************/


template <typename T>
using RemoveVolatile = typename private_RemoveVolatile::RemoveVolatileStruct<T>::Type;

template <typename T>
using RemoveRef = typename private_RemoveRef::RemoveRefStruct<T>::Type;

template <typename T>
using RemovePtr = typename private_RemovePtr::RemovePtrStruct<T>::Type;

template <typename T>
using RemoveConst = typename private_RemoveConst::RemoveConstStruct<T>::Type;

template <typename T>
using RemoveArray = typename private_RemoveArray::RemoveArrayStruct<T>::Type;

template <typename T>
using Decay = typename private_Decay::DecayStruct<T>::Type;

template <typename T>
using RawType = RemoveConst<
					RemoveVolatile<
						RemoveRef<
							RemovePtr<
								RemoveArray<
									T
								>
							>
						>
					>
				>;

/************/
/*	TYPES	*/
/************/

// Capabilities of types
//
// Everything is calculated at compile time
namespace Types
{

template <typename T, const bool BCondition>
using EnableIF = typename private_EnableIf::EnableIFStruct<T, BCondition>::Type;

template <typename TTrue, typename TFalse, const bool BCondition>
using Conditional = typename private_Conditional::ConditionalStruct<TTrue, TFalse, BCondition>::Type;

template <typename T>
inline constexpr bool	IsVolatile = private_IsVolatile::IsVolatileStruct<T>::val;

// Knowing if two types are the same
template <typename T, typename U>
inline constexpr bool	IsSame = false;
// Knowing if two types are the same
template <typename T>
inline constexpr bool	IsSame<T, T> = true;

/*// Savoir si deux types BRUTS sont les mêmes
template <typename T, typename U>
inline constexpr bool	IsRawSame = false;
// Savoir si deux types BRUTS sont les mêmes
template <typename T>
inline constexpr bool	IsRawSame<RawType<T>, RawType<T>> = true;*/

template <typename T>
inline constexpr bool	IsVoid = IsSame<T, void>;

template <typename T>
inline constexpr bool	IsUnsigned =
	(
		IsSame<RawType<T>, unsigned char>
			||
		IsSame<RawType<T>, unsigned short>
			||
		IsSame<RawType<T>, unsigned int>
			||
		IsSame<RawType<T>, unsigned long>
			||
		IsSame<RawType<T>, unsigned long long>
	);

template <typename T>
inline constexpr bool	IsIntegral =
	(
		IsSame<RawType<T>, char>
			||
		IsSame<RawType<T>, short>
			||
		IsSame<RawType<T>, int>
			||
		IsSame<RawType<T>, long>
			||
		IsSame<RawType<T>, long long>
			||
		IsSame<RawType<T>, bool>
			||
		IsUnsigned<T>
	);

template <typename T>
inline constexpr bool	IsSigned =
	(
		!IsUnsigned<T>
			&&
		IsIntegral<T>
	);

template <typename T>
inline constexpr bool	IsFloatingPoint =
	(
		IsSame<RawType<T>, float>
			||
		IsSame<RawType<T>, double>
			||
		IsSame<RawType<T>, long double>
	);

template <typename T>
inline constexpr bool	IsNative =
	(
		IsFloatingPoint<T>
			||
		IsIntegral<T>
			||
		IsVoid<T>
	);

template <typename T>
inline constexpr bool	IsObject =
	(
		!IsNative<T>
			&&
		!IsVoid<T>
	);

template <typename T>
inline constexpr bool	IsAnyNumberType =
	(
		IsFloatingPoint<T>
			||
		IsIntegral<T>
	);

template <typename T>
inline constexpr unsigned long	SizeMax =
	(
		IsSigned<T>
			*
		static_cast<long>((1UL << ((sizeof(T) * 8) - 1)) - 1UL)
			+
		IsUnsigned<T>
			*
		static_cast<long>((1UL << (sizeof(T) * 8)) - 1UL)
			+
		IsObject<T>
			*
		sizeof(T)
	);

template <typename T>
inline constexpr unsigned long	SizeMin =
	(
		IsSigned<T>
			*
		-SizeMax<T> - (1UL - IsUnsigned<T>)
			+
		IsUnsigned<T>
			*
		0UL
			+
		IsObject<T>
			*
		sizeof(T)
	);

template <typename NumberType, NumberType N>
requires IsAnyNumberType<NumberType>
inline constexpr bool	IsPositive =
	(
		N >= 0
	);

template <typename NumberType, NumberType N>
requires IsAnyNumberType<NumberType>
inline constexpr bool	IsNegative =
	(
		N < 0
	);

template <typename NumberType, NumberType N>
requires IsAnyNumberType<NumberType>
inline constexpr bool	IsZero =
	(
		N == 0
	);

template <typename T>
inline constexpr bool	IsArray =
	(
		private_IsArray::IsArrayStruct<T>::val
	);

template <typename T>
inline constexpr bool	IsConst =
	(
		private_IsConst::IsConstStruct<T>::val
	);

template <typename T>
inline constexpr bool	IsRef =
	(
		private_IsRef::IsRefStruct<T>::val
	);

template <typename T>
inline constexpr bool	IsRValue =
	(
		private_IsRValue::IsRValueStruct<T>::val
	);

template <typename T>
inline constexpr bool	IsPtr =
	(
		private_IsPtr::IsPtrStruct<T>::val
	);

}

/****************/
/*	TYPES DATA	*/
/****************/

//? Types::Name() in --> TypesName.hpp

#endif
