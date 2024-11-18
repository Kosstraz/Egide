#ifndef NSL_CALLABLE_HPP
#define NSL_CALLABLE_HPP

//Todo: refactor Unpack			--> GOOD
//Todo: refactor NSUnpack
//Todo: Bind function in Unpack class
//Todo: finish Callable class
//Todo: finish ThreadQueue

# include "Function.hpp"
# include "Package.hpp"
# include "Unpack.hpp"

template <typename TRet, typename ... TArgsPackaged>
struct Unpack;

template <typename TSignature>
class Function;

template <typename TRet, typename... TArgs>
struct Callable;

	// With parameters
template <typename TRet, typename... TArgs>
struct Callable<TRet(TArgs...)> final
{
	typedef TRet (*FUNTYPE)(TArgs...);

	Callable(Callable::FUNTYPE fun, TArgs... args);
	Callable(Function<TRet(TArgs...)> fun, TArgs... args);

	FORCEINLINE
	Function<TRet(TArgs...)>	GetFun()			const noexcept;
	FORCEINLINE
	Package<TArgs...>			GetArgsPackaged()	const noexcept;

	TRet	operator()();

private:
	Function<TRet(TArgs...)>	fun;
	Package<TArgs...>			args;
};

# include "template/Callable.inl"
#endif
