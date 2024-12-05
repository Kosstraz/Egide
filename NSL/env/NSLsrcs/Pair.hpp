#ifndef NSL_PAIR_HPP
#define NSL_PAIR_HPP

# include "../NSLplatform.h"
# include "TypesCap.hpp"

// A structure containing 2 elements
//
// If you want more elements, check the Trio struct (or Package struct)
template <typename T1, typename T2>
struct Pair
{
private:
	typedef Decay<T1>	_T1;
	typedef Decay<T2>	_T2;

public:
	constexpr	Pair() noexcept : a(), b()
	{
	}

	constexpr	Pair(T1&& a, const T2& b) noexcept : a(Meta::Forward<T1>(a)), b(_T2(b))
	{
	}

	constexpr	Pair(const T1& a, T2&& b) noexcept : a(_T1(a)), b(Meta::Forward<T2>(b))
	{
	}

	constexpr	Pair(const T1& a, const T2& b) noexcept : a(_T1(a)), b(_T2(b))
	{
	}

	constexpr	Pair(T1&& a, T2&& b) noexcept : a(Meta::Forward<T1>(a)), b(Meta::Forward<T2>(b))
	{
	}

	virtual FORCEINLINE	~Pair()
	{
	}

	_T1	a;
	_T2	b;
};


#endif
