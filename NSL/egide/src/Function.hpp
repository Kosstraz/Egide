/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_FUNCTION_HPP
#define EGIDE_FUNCTION_HPP

# include "Meta.hpp"
# include "IsEmpty.hpp"
# include "Callable.hpp"
# include <type_traits>

template <typename TSignature>
class Function;

template <typename TRet, typename... TArgs>
struct Callable;

// To store a function with any many arguments
template <typename TRet, typename... TArgs>
class Function<TRet(TArgs...)> final
{
public:
	typedef TRet (*FUNTYPE)(TArgs...);

public:
	Function() 							noexcept;
	Function(typename Function<TRet(TArgs...)>::FUNTYPE f) 		noexcept;
	~Function() 						noexcept = default;

public:
	Function::FUNTYPE	Get() 		const	noexcept;
	TRet	Play(TArgs... args)		const	noexcept;
	void	Replace(FUNTYPE fun) 			noexcept;

private:
	Function::FUNTYPE	fun;

public:
	operator FUNTYPE() const noexcept
	{
		return (this->fun);
	}

	TRet	operator()(TArgs ...args) const
	{
		return (this->fun(args ...));
	}
};

# include "template/Function.inl"
#endif
