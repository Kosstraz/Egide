/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_TRIO_HPP
#define EGIDE_TRIO_HPP

# include "../egide_platform.h"
# include "TypesCap.hpp"

// A structure containing 3 elements
//
// If you want less elements, check the Pair struct
// If you want more elements, check the Package struct
template <typename T1, typename T2, typename T3>
struct Trio
{
private:
	typedef Decay<T1>	_T1;
	typedef Decay<T2>	_T2;
	typedef Decay<T3>	_T3;

public:
	constexpr	Trio() noexcept : a(), b(), c()
	{
	}

	constexpr	Trio(const T1& pA, const T2& pB, const T3& pC) noexcept : a(_T1(pA)), b(_T2(pB)), c(_T3(pC))
	{
	}

	constexpr	Trio(T1&& pA, T2&& pB, T3&& pC) noexcept : a(Meta::Forward<T1>(pA)), b(Meta::Forward<T2>(pB)), c(Meta::Forward<T3>(pC))
	{
	}

	virtual FORCEINLINE	~Trio()
	{
	}

	_T1	a;
	_T2	b;
	_T3	c;
};


#endif
