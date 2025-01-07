/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_THREAD_INL
#define EGIDE_THREAD_INL

# include "../Thread.hpp"

/**/template <typename TFun>
Thread::Thread(TFun pFun)
{
	this->wrapperHelper = new Thread::WrapperHelper;
	this->wrapperHelper->funPtr = ptrCast<void*>(&pFun);
	this->wrapperHelper->args = nullptr;
	this->wrapperHelper->objPtr = nullptr;
	pthread_create(&this->thread, nullptr, Thread::ThreadWrapper<TFun>, this->wrapperHelper);
}

template <typename TFun, typename... TArgs>
Thread::Thread(TFun pFun, TArgs&&... pArgs)
{
	this->wrapperHelper = new Thread::WrapperHelper;
	this->wrapperHelper->funPtr = ptrCast<void*>(&pFun);
	this->wrapperHelper->args = ptrCast<void*>(new Package(Meta::Forward<TArgs>(pArgs)...));
	this->wrapperHelper->objPtr = nullptr;
	pthread_create(&this->thread, nullptr, Thread::ThreadWrapperVariadic<TFun, TArgs...>, this->wrapperHelper);
}

template <typename TRet, class CObject>
Thread::Thread(TRet (CObject::*pFun)(void), CObject* pObjInstance)
{
	this->wrapperHelper = new Thread::WrapperHelper;
	this->wrapperHelper->funPtr = ptrCast<void*>(&pFun);
	this->wrapperHelper->args = nullptr;
	this->wrapperHelper->objPtr = pObjInstance;
	pthread_create(&this->thread, nullptr, Thread::ThreadMethodWrapper<TRet (CObject::*)(void), CObject>, this->wrapperHelper);
}

template <typename TRet, class CObject, typename... TFunArgs, typename... TArgs>
Thread::Thread(TRet (CObject::*pFun)(TFunArgs...), CObject* pObjInstance, TArgs&&... pArgs)
{
	this->wrapperHelper = new Thread::WrapperHelper;
	this->wrapperHelper->funPtr = ptrCast<void*>(&pFun);
	this->wrapperHelper->args = ptrCast<void*>(new Package(Meta::Forward<TArgs>(pArgs)...));
	this->wrapperHelper->objPtr = pObjInstance;
	pthread_create(&this->thread, nullptr, Thread::ThreadMethodWrapperVariadic<TRet (CObject::*)(TFunArgs...), CObject, TArgs...>, this->wrapperHelper);
}

template <typename TFun>
void*
Thread::ThreadWrapper(void* args)
{
	Thread::WrapperHelper*	helpingArgs = static_cast<Thread::WrapperHelper*>(args);
	TFun*					fun = reinterpret_cast<TFun*>(helpingArgs->funPtr);
	(*fun)();
	delete(helpingArgs);
	return (nullptr);
}

template <typename TFun, typename... TArgs>
void*
Thread::ThreadWrapperVariadic(void* args)
{
	Thread::WrapperHelper*	helpingArgs = static_cast<Thread::WrapperHelper*>(args);
	TFun*					fun = reinterpret_cast<TFun*>(helpingArgs->funPtr);
	Package<TArgs...>*		pack = static_cast<Package<TArgs...>*>(helpingArgs->args);
	Unpack::Apply(*fun, *pack);
	delete(helpingArgs);
	delete(pack);
	return (nullptr);
}

template <typename TFun, class CObject>
void*
Thread::ThreadMethodWrapper(void* args)
{
	Thread::WrapperHelper*	helpingArgs	= static_cast<Thread::WrapperHelper*>(args);
	TFun*					fun			= reinterpret_cast<TFun*>(helpingArgs->funPtr);
	CObject*				instance	= static_cast<CObject*>(helpingArgs->objPtr);
	(instance->*(*fun))();
	delete (helpingArgs);
	return (nullptr);
}

template <typename TFun, class CObject, typename... TArgs>
void*
Thread::ThreadMethodWrapperVariadic(void* args)
{
	Thread::WrapperHelper*	helpingArgs	= static_cast<Thread::WrapperHelper*>(args);
	TFun*					fun			= reinterpret_cast<TFun*>(helpingArgs->funPtr);
	Package<TArgs...>*		pack		= static_cast<Package<TArgs...>*>(helpingArgs->args);
	CObject*				instance	= static_cast<CObject*>(helpingArgs->objPtr);
	Unpack::Apply(*fun, instance, *pack);
	delete(helpingArgs);
	delete(pack);
	return (nullptr);
}

#endif
