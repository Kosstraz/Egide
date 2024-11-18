/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_THREAD_INL
#define NSL_THREAD_INL

# include "../Thread.hpp"

#pragma region Constructor

template <typename TRet>
Thread::Thread(	TRet (*funThread)()) : joined(false)
{
	this->basic_constructor(funThread);
}

template <typename TRet>
Thread::Thread(TRet (*funThread)(void*),
				void* arg) : joined(false)
{
	this->voidptr_constructor(funThread, arg);
}

template <typename TRet, typename ... TFunArgs, typename ... TArgs>
Thread::Thread(TRet (*funThread)(TFunArgs ...),
				TArgs ...args) : joined(false)
{
	this->constructor(funThread, args...);
}
 
template <typename TRet>
Thread::Thread(	Function<TRet()> funThread) : joined(false)
{
	TRet (*funTmp)() = static_cast<TRet (*)()>(funThread);

	this->basic_constructor(funTmp);
}

template <typename TRet>
Thread::Thread(Function<TRet(void*)> funThread,
				void* arg) : joined(false)
{
	this->voidptr_constructor(funThread, arg);
}

template <typename TRet, typename ... TFunArgs, typename ... TArgs>
Thread::Thread(	Function<TRet(TFunArgs...)> funThread,
				TArgs ...args) : joined(false)
{
	TRet (*funTmp)(TArgs ...) = static_cast<TRet (*)(TArgs ...)>(funThread);
	this->constructor(funTmp, args...);
}

template <typename TRet, typename... TFunArgs>
Thread::Thread(Callable<TRet(TFunArgs...)> funThread)
{
	this->constructor_for_callable(funThread);
}

Thread::Thread(letc funThread)
{
	this->constructor_for_callable(funThread);
}

#pragma endregion






#pragma region Constructor non-static methods
template <typename TObject, typename TRet, typename... TFunArgs, typename... TArgs>
Thread::Thread(TRet (TObject::*funmethod)(TFunArgs ...), TObject* obj, TArgs ...args) : joined(false)
{
	this->constructor_methods(funmethod, obj, args...);
}

template <typename TObject, typename TRet, typename... TFunArgs>
Thread::Thread(TRet (TObject::*funmethod)(TFunArgs ...), TObject* obj) : joined(false)
{
	this->constructor_methods(funmethod, obj);
}

template <typename TObject, typename TRet, typename... TFunArgs, typename... TArgs>
Thread::Thread(TRet (TObject::*funmethod)(TFunArgs ...) const, const TObject* obj, TArgs ...args) : joined(false)
{
	this->constructor_methods(funmethod, obj, args...);
}

template <typename TObject, typename TRet, typename... TFunArgs>
Thread::Thread(TRet (TObject::*funmethod)(TFunArgs ...) const, const TObject* obj) : joined(false)
{
	this->constructor_methods(funmethod, obj);
}
#pragma endregion






#pragma region constructorHelper

template <typename TRet, typename ... TFunArgs, typename ... TArgs>
void
Thread::constructor(TRet (*f)(TFunArgs ...), TArgs ...args)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->args = new Package<TArgs...>(args...);
	pthread_create(&this->thread, nullptr, Thread::ThreadWrapper<TRet, TRet (*)(TFunArgs...), TArgs...>, static_cast<void*>(this->wrapperHelper));
}

template <typename TRet>
void
Thread::basic_constructor(TRet (*f)())
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->args = nullptr;
	pthread_create(&this->thread, nullptr, Thread::BasicThreadWrapper<TRet>, static_cast<void*>(this->wrapperHelper));
}

template <typename TRet>
void
Thread::voidptr_constructor(TRet (*f)(void*), void* arg)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->args = arg;
	pthread_create(&this->thread, nullptr, Thread::VoidptrThreadWrapper<TRet>, static_cast<void*>(this->wrapperHelper));
}


template <typename TObject, typename TRet, typename ... TFunArgs, typename ... TArgs>
void
Thread::constructor_methods(TRet (TObject::*&f)(TFunArgs ...), TObject* obj, TArgs ...args)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->args = new Package<TArgs...>(args...);
	this->wrapperHelper->objPtr = static_cast<void*>(obj);
	pthread_create(&this->thread, nullptr, Thread::ThreadWrapperMethods<TObject, TRet, TRet (TObject::*)(TFunArgs...), TArgs...>, static_cast<void*>(this->wrapperHelper));
}

template <typename TObject, typename TRet>
void
Thread::constructor_methods(TRet (TObject::*&f)(), TObject* obj)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->objPtr = static_cast<void*>(obj);
	pthread_create(&this->thread, nullptr, Thread::ThreadWrapperMethodsNoArgs<TObject, TRet, TRet (TObject::*)()>, static_cast<void*>(this->wrapperHelper));
}


template <typename TObject, typename TRet, typename ... TFunArgs, typename ... TArgs>
void
Thread::constructor_methods(TRet (TObject::*&f)(TFunArgs ...) const, const TObject* obj, TArgs ...args)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->args = new Package<TArgs...>(args...);
	this->wrapperHelper->objPtr = static_cast<void*>(obj);
	pthread_create(&this->thread, nullptr, Thread::ThreadWrapperConstMethods<TObject, TRet, TRet (TObject::*)(TFunArgs...) const, TArgs...>, static_cast<void*>(this->wrapperHelper));
}

template <typename TObject, typename TRet>
void
Thread::constructor_methods(TRet (TObject::*&f)() const, const TObject* obj)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = reinterpret_cast<void*&>(f);
	this->wrapperHelper->objPtr = const_cast<void*>(static_cast<const void*>(obj));
	pthread_create(&this->thread, nullptr, Thread::ThreadWrapperConstMethodsNoArgs<TObject, TRet, TRet (TObject::*)() const>, static_cast<void*>(this->wrapperHelper));
}




template <typename TRet, typename... TFunArgs>
void
Thread::constructor_for_callable(Callable<TRet(TFunArgs...)> funThread)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = new Callable<TRet(TFunArgs...)>(funThread);
	pthread_create(&this->thread, nullptr, Thread::BasicThreadWrapper_Callable<TRet, TFunArgs...>, static_cast<void*>(this->wrapperHelper));
}

void
Thread::constructor_for_callable(letc funThread)
{
	this->wrapperHelper = new WrapperHelper;
	this->wrapperHelper->funPtr = new letc(funThread);
	pthread_create(&this->thread, nullptr, Thread::BasicThreadWrapper_LetCallable, static_cast<void*>(this->wrapperHelper));
}

#pragma endregion






#pragma region ThreadWrapper

template <typename TRet, typename TFun, typename ... TArgs>
void*
Thread::ThreadWrapper(void* args)
{
	Thread::WrapperHelper*	helpingArgs = static_cast<Thread::WrapperHelper*>(args);
	TFun					funPtr		= reinterpret_cast<TFun>(helpingArgs->funPtr);
	Package<TArgs...>		*argsPack	= static_cast<Package<TArgs...>*>(helpingArgs->args);
	Unpack<TRet, TArgs...>::Apply(funPtr, *argsPack);
	delete static_cast<Package<TArgs...>*>(helpingArgs->args);
	delete helpingArgs;
	return (nullptr);
}

template <typename TRet>
void*
Thread::BasicThreadWrapper(void* args)
{
	Thread::WrapperHelper*	helpingArgs = static_cast<Thread::WrapperHelper*>(args);
	TRet (*funPtr)()					= reinterpret_cast<TRet (*)()>(helpingArgs->funPtr);
	funPtr();
	delete helpingArgs;
	return (nullptr);
}

template <typename TRet>
void*
Thread::VoidptrThreadWrapper(void* args)
{
	Thread::WrapperHelper*	helpingArgs = static_cast<Thread::WrapperHelper*>(args);
	TRet (*funPtr)(void*)				= reinterpret_cast<TRet (*)(void*)>(helpingArgs->funPtr);
	funPtr(helpingArgs->args);
	delete helpingArgs;
	return (nullptr);
}


template <typename TObject, typename TRet, typename TFun, typename ... TArgs>
void*
Thread::ThreadWrapperMethods(void* args)
{
	Thread::WrapperHelper*	helpingArgs 	= static_cast<Thread::WrapperHelper*>(args);
	TObject*				classInstance	= static_cast<TObject*>(helpingArgs->objPtr);
	TFun					funPtr			= reinterpret_cast<TFun>(reinterpret_cast<TFun&>(helpingArgs->funPtr));
	Package<TArgs...>*		argsPack		= static_cast<Package<TArgs...>*>(helpingArgs->args);
	Unpack<TRet, TArgs...>::Apply(funPtr, classInstance, (*argsPack));
	delete static_cast<Package<TArgs...>*>(helpingArgs->args);
	delete helpingArgs;
	return (nullptr);
}

template <typename TObject, typename TRet, typename TFun, typename ... TArgs>
void*
Thread::ThreadWrapperConstMethods(void* args)
{
	Thread::WrapperHelper*	helpingArgs 	= static_cast<Thread::WrapperHelper*>(args);
	const TObject*			classInstance	= static_cast<const TObject*>(helpingArgs->objPtr);
	TFun					funPtr			= reinterpret_cast<TFun>(reinterpret_cast<TFun&>(helpingArgs->funPtr));
	Package<TArgs...>*		argsPack		= static_cast<Package<TArgs...>*>(helpingArgs->args);
	Unpack<TRet, TArgs...>::Apply(funPtr, classInstance, (*argsPack));
	delete static_cast<Package<TArgs...>*>(helpingArgs->args);
	delete helpingArgs;
	return (nullptr);
}

template <typename TObject, typename TRet, typename TFun>
void*
Thread::ThreadWrapperMethodsNoArgs(void* args)
{
	Thread::WrapperHelper*	helpingArgs 	= static_cast<Thread::WrapperHelper*>(args);
	TObject*				classInstance	= static_cast<TObject*>(helpingArgs->objPtr);
	TFun					funPtr			= reinterpret_cast<TFun>(reinterpret_cast<TFun&>(helpingArgs->funPtr));
	(classInstance->*funPtr)();
	delete helpingArgs;
	return (nullptr);
}

template <typename TObject, typename TRet, typename TFun>
void*
Thread::ThreadWrapperConstMethodsNoArgs(void* args)
{
	Thread::WrapperHelper*	helpingArgs 	= static_cast<Thread::WrapperHelper*>(args);
	const TObject*			classInstance	= static_cast<const TObject*>(helpingArgs->objPtr);
	TFun					funPtr			= reinterpret_cast<TFun>(reinterpret_cast<TFun&>(helpingArgs->funPtr));
	(classInstance->*funPtr)();
	delete helpingArgs;
	return (nullptr);
}

template <typename TRet, typename... TFunArgs>
void*
Thread::BasicThreadWrapper_Callable(void* args)
{
	Thread::WrapperHelper*		helpingArgs	=	static_cast<Thread::WrapperHelper*>(args);
	Callable<TRet, TFunArgs...>	funCallable	=	static_cast<Callable<TRet, TFunArgs...>>(helpingArgs->funPtr);
	funCallable();
	delete helpingArgs;
	return (nullptr);
}

void*
Thread::BasicThreadWrapper_LetCallable(void* args)
{
	Thread::WrapperHelper*	helpingArgs	=	static_cast<Thread::WrapperHelper*>(args);
	letc*					funCallable	=	static_cast<letc*>(helpingArgs->funPtr);
	(*funCallable)();
	delete helpingArgs;
	return (nullptr);
}

#pragma endregion




#pragma region Methods

#pragma endregion


#endif
