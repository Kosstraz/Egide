/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_THREAD_HPP
#define EGIDE_THREAD_HPP

# include "../egide_platform.h"

# include "Function.hpp"
# include "Callable.hpp"
# include "Package.hpp"
# include "Unpack.hpp"
# include "String.hpp"
# include "Mutex.hpp"
# include "Let.hpp"
# include <pthread.h>
# include <map>

extern pthread_t	Thread_MainThreadID;

// A well threading system
//
// INFO:
// Please exit threads cleanly with Thread::Return(...), particularly if you need a return value
class Thread
{
private:
	struct WrapperHelper
	{
		WrapperHelper() : args(nullptr), funPtr(nullptr), objPtr(nullptr)
		{}

		void*	args	= nullptr;
		void*	funPtr	= nullptr;
		void*	objPtr	= nullptr;
	};

public:
#pragma region Constructors
	Thread() = delete;

			//* Basic constructors

	/**/template <typename TFun>
	Thread(TFun pFun);

	template <typename TFun, typename... TArgs>
	Thread(TFun pFun, TArgs&&... pArgs);

	template <typename TRet, class CObject>
	Thread(TRet (CObject::*pFun)(void), CObject* pObjInstance);

	template <typename TRet, class CObject, typename... TFunArgs, typename... TArgs>
	Thread(TRet (CObject::*pFun)(TFunArgs...), CObject* pObjInstance, TArgs&&... pArgs);

	~Thread();
#pragma endregion

	bool	IsAlive();
	void	TryStop();

	// Check if Thread can get return value, if not, throw an exception
	template <typename TRet>
	FORCEINLINE TRet	TryGet()
	{
		void*	buffer;
		TRet	ret;
		if (this->joined)
			throw (Thread::IsStillAliveException());
		else if (pthread_tryjoin_np(this->thread, &buffer) == EBUSY)
			throw (Thread::IsStillAliveException());
		this->joined = true;
		ret = *static_cast<TRet*>(buffer);
		delete(static_cast<int*>(buffer));//::operator delete(buffer);
		return (ret);
	}

	// Waits for the thread to finish and returns its Thread::Return() value
	template <typename TRet>
	FORCEINLINE TRet	Get()
	{
		void*	buffer;
		TRet	ret;
		pthread_join(this->thread, &buffer);
		if (buffer)
		{
			this->joined = true;
			ret = *static_cast<TRet*>(buffer);
			delete(static_cast<int*>(buffer));//::operator delete(buffer);
		}
		return (ret);
	}

	// Waits for thread end
	FORCEINLINE void	Wait() noexcept
	{
		void*	buffer;
		pthread_join(this->thread, &buffer);
		this->joined = true;
		::operator delete(buffer);
	}
	// FRANCAIS :
	// Permet de quitter un thread, cependant si la fonction est appelé de manière native ET dans le MainThread, il faudra placer un 'return (...);' juste après, de manière à ce que la fonction quitte comme prévu, car cette fonction (Thread::Return) sera ignorée.
	// Si elle est appelée de manière native dans un thread qui n'est pas le principal, le thread sera quitté entièrement.
	//
	// ENGLISH :
	// Allows you to exit a thread, but if the function is called natively AND in the MainThread, you'll need to place a 'return (...);' just after it, so that the function exits as expected, as this function (Thread::Return) will be ignored.
	// If it is called natively in a thread that is not the main thread, the thread will be exited entirely
	template <typename TRet>
	FORCEINLINE static TRet	Return(TRet return_arg)
	{
		if (pthread_equal(pthread_self(), Thread_MainThreadID))
			return (return_arg);
		TRet*	ret = new TRet;//static_cast<TRet*>(::operator new(sizeof(TRet)));
		*ret = return_arg;
		pthread_exit(ret);
		CODE_UNREACHABLE;
	}

	class IsStillAliveException
	{
	public:
		const char* what() const noexcept;
	};

	class Async;

private:

		// wrapper for 'pthread'
	template <typename TFun>
	static void*	ThreadWrapper(void*);
	template <typename TFun, typename... TArgs>
	static void*	ThreadWrapperVariadic(void*);
	template <typename TFun, class CObject>
	static void*	ThreadMethodWrapper(void*);
	template <typename TFun, class CObject, typename... TArgs>
	static void*	ThreadMethodWrapperVariadic(void*);

public:
	thread_local static const int32	ThisTID;

private:
	bool					joined;
	pthread_t				thread;
	WrapperHelper*			wrapperHelper = nullptr;
};

# include "template/Thread.inl"
#endif
