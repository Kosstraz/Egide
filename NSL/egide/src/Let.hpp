#ifndef EGIDE_LET_HPP
#define EGIDE_LET_HPP

# include "SmartPtr.hpp"
# include "Package.hpp"
//# include "VTable.hpp"


#pragma region LetVar





class LetVar
{
private:
	struct Base
	{
		FORCEINLINE
		Base() noexcept = default;
		FORCEINLINE
		virtual ~Base() noexcept = default;
	};

	template <typename T>
	struct True : LetVar::Base
	{
		FORCEINLINE
		True(const T& v) noexcept : var(v){}
		FORCEINLINE
		True(T&& v)		noexcept : var(Meta::Move(v)){}
		FORCEINLINE
		virtual ~True() = default;
		T	var;
	};

	template <typename T, uint64 N>
	struct True<const T(&)[N]> : LetVar::Base
	{
		FORCEINLINE
		True(const T(&v)[N])	noexcept : var(v){}
		FORCEINLINE
		True(T&& v)			noexcept = delete;
		FORCEINLINE
		virtual ~True() = default;
		const T(&var)[N];
	};

public:

	FORCEINLINE
	LetVar()						noexcept = default;
	template <typename T>
	LetVar(const T&)		noexcept;
	template <typename T, uint64 N>
	LetVar(const T(&)[N])	noexcept;
	template <typename T>
	LetVar(T&&)			noexcept;

	virtual ~LetVar() noexcept = default;

	template <typename T>
	T&
	Cast() noexcept;

	template <typename T>
	FORCEINLINE
	const T&	//const T&
	ConstCast() const noexcept;

	template <typename T>
	LetVar&	operator =(const T&) noexcept;
	template <typename T>
	LetVar&	operator =(T&&) noexcept;

private:
	SmartPtr<LetVar::Base>	var;
};

#pragma endregion





/*
#pragma region LetFunction

# define VIRTUAL_TEMPLATE(ArgsType) 					unsigned long long _ULindex = StatefulTypeList::TryPush<VTable< ArgsType >>()
# define ENABLE_VIRTUAL_TEMPLATED_METHODS(BaseClass)	const std::span<void (*)( BaseClass* , void*)>	__vtable__;
# define VIRTUAL_BODY(ArgsType, args)					Package<ArgsType> __pack__ = Package<ArgsType>(args);\
														this->__vtable__[_ULindex](this, &__pack__);
# define VIRTUAL_TEMPL_CONSTRUCT						typename FTDerived
# define VIRTUAL_ATTR_CONSTRUCT							__vtable__(CreateVTable<FTDerived>(StatefulTypeList::Get<FTDerived>()))
# define VIRTUAL_ARG_CONSTRUCT							FTDerived*
# define VIRTUAL_CHILD_ALLOW							this

# include <span>
# include <utility>
# include <tuple>

struct LetFunction;

struct Base1
{
	template <VIRTUAL_TEMPL_CONSTRUCT>
	Base1(VIRTUAL_ARG_CONSTRUCT) noexcept : VIRTUAL_ATTR_CONSTRUCT
	{}

	virtual ~Base1() noexcept = default;

	template <typename... TArgs, VIRTUAL_TEMPLATE(TArgs...)>
	void Invoke(TArgs&&... args)
	{
		VIRTUAL_BODY(TArgs..., Meta::Move(args)...);
	}

	ENABLE_VIRTUAL_TEMPLATED_METHODS(Base1);
};

template <typename TFun>
struct True1 : Base1
{
	FORCEINLINE
	True1(TFun&& f) noexcept : Base1(VIRTUAL_CHILD_ALLOW), fun(Meta::Move<TFun>(f)){}
	FORCEINLINE
	virtual ~True1() noexcept = default;
	template <typename... TArgs>
	FORCEINLINE
	void Invoke(TArgs&&... args)
	{
		this->fun(Meta::Move(args)...);
	}

	TFun	fun;
};

class LetFunction
{
	using LetF = LetFunction;

public:

public:

	FORCEINLINE
	LetFunction()					noexcept = default;
	template <typename TFun>
	LetFunction(TFun&&)	noexcept;

	virtual ~LetFunction() noexcept = default;

	template <typename TFun>
	TFun&
	Cast() noexcept;

	template <typename TFun>
	const TFun&
	ConstCast() const noexcept;

	template <typename... TArgs>
	void
	Call(TArgs...) const noexcept;
	template <typename TRet, typename... TArgs>
	TRet
	Call(TArgs...) const noexcept;

	template <typename TFun>
	LetFunction&	operator =(TFun&&) noexcept;

	template <typename... TArgs>
	void operator ()(TArgs...) const noexcept;

private:
	SmartPtr<Base1>	fun;
};

#pragma endregion
*/






#pragma region LetCallable






#include <functional>
class LetCallable
{
private:
	using LetC = LetCallable;

public:

	FORCEINLINE
	LetCallable()												noexcept;
	template <typename TRet, typename... TArgs>
	LetCallable(TRet (*f)(TArgs...), TArgs... args)	noexcept;

	FORCEINLINE
	virtual ~LetCallable() noexcept = default;

	FORCEINLINE
	void
	Call() const noexcept;
	template <typename TRet>
	TRet
	Call() const noexcept;

	template <typename TRet, typename... TArgs>
	void
	Set(TRet (*f)(TArgs...), TArgs... args) noexcept;

	FORCEINLINE
	void operator ()() const noexcept;

private:
	std::function<void()>	lambda; //replace by letf, later
};

#pragma endregion





#pragma region Let

#pragma endregion

//typedef Let			let;
typedef LetVar		let;
//typedef LetFunction	letf;
typedef LetCallable	letc;

# include "template/Let.inl"
#endif
