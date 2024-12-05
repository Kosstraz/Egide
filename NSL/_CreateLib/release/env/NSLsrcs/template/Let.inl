#ifndef NSL_LET_INL
#define NSL_LET_INL

# include "../Let.hpp"

#pragma region LetVar








template <typename T>
LetVar::LetVar(const T& v) noexcept : var(SmartPtr<LetVar::True<T>>(LetVar::True<T>(v)))
{
}

template <typename T, uint64 N>
LetVar::LetVar(const T(&v)[N]) noexcept : var(SmartPtr<LetVar::True<const T(&)[N]>>(LetVar::True<const T(&)[N]>(v)))
{
}

template <typename T>
LetVar::LetVar(T&& v) noexcept : var(SmartPtr<LetVar::True<T>>(LetVar::True<T>(Meta::Move(v))))
{
}

template <typename T>
T&
LetVar::Cast() noexcept
{
	return ((static_cast<LetVar::True<T>*>(this->var.get()))->var);
}

template <typename T>
const T&
LetVar::ConstCast() const noexcept
{
	return ((static_cast<const LetVar::True<T>*>(this->var.const_get()))->var);
}

template <typename T>
LetVar&
LetVar::operator =(const T& v) noexcept
{
	this->var = SmartPtr<LetVar::True<T>>(LetVar::True<T>(v));
	return (*this);
}

template <typename T>
LetVar&
LetVar::operator =(T&& v) noexcept
{
	this->var = SmartPtr<LetVar::True<T>>(LetVar::True<T>(Meta::Move(v)));
	return (*this);
}



#pragma endregion






#pragma region LetFunction




/*
template <typename TFun>
LetFunction::LetFunction(TFun&& f) noexcept : fun(True1<TFun>
													(Meta::Move<TFun>(f))
												)
{
}

template <typename TFun>
TFun&
LetFunction::Cast() noexcept
{
	return ((static_cast<True1<TFun>*>(this->fun.get()))->fun);
}

template <typename TFun>
const TFun&
LetFunction::ConstCast() const noexcept
{
	return ((static_cast<const True1<TFun>*>(this->fun.const_get()))->fun);
}

template <typename... TArgs>
void
LetFunction::Call(TArgs... args) const noexcept
{
	//this->fun->Invoke(Meta::Move(args)...);
}

template <typename TRet, typename... TArgs>
TRet
LetFunction::Call(TArgs... args) const noexcept
{
	//fun->Invoke<TRet>(Meta::Move(args)...);
	//return ((static_cast<const LetF::True<TRet(*)(TArgs...)>*>(this->fun.const_get())->fun)
	//	(Meta::Move(args)...));
}

template <typename TFun>
LetFunction&
LetFunction::operator =(TFun&& f) noexcept
{
	this->fun = SmartPtr<True1<TFun>>(True1<TFun>(f));
	return (*this);
}
#include<iostream>
template <typename... TArgs>
void
LetFunction::operator ()(TArgs... args) const noexcept
{
	this->fun->Invoke(Meta::Move(args)...);
}
#pragma endregion

*/





#pragma region LetCallable




LetCallable::LetCallable() noexcept
{
}

template <typename TRet, typename... TArgs>
LetCallable::LetCallable(TRet (*f)(TArgs...), TArgs... args) noexcept
:	lambda([_fun = f, _pack = Package<TArgs...>(Meta::Move(args)...)]()
	mutable
	{
		Unpack::Apply(_fun, _pack);
	})
{
}

void
LetCallable::Call() const noexcept
{
	this->lambda();
}

template <typename TRet>
TRet
LetCallable::Call() const noexcept
{
	return (this->lambda());
}

template <typename TRet, typename... TArgs>
void
LetCallable::Set(TRet (*f)(TArgs...), TArgs... args) noexcept
{
	this->lambda = 
	([_fun = f, _pack = Package<TArgs...>(Meta::Move(args)...)]()
	mutable
	{
		Unpack::Apply(_fun, _pack);
	});
}

void
LetCallable::operator ()() const noexcept
{
	this->lambda();
}
#pragma endregion



#endif
