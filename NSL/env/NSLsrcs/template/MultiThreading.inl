/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef NSL_MULTITHREADING_INL
#define NSL_MULTITHREADING_INL

# include "../MultiThreading.hpp"

template <typename TRet>
TRet
MultiThreading::Get(const String& threadToWait) noexcept
{
	return (MultiThreading::threads.at(threadToWait).Get<TRet>());
}

template <typename TRet>
TRet
MultiThreading::TryGet(const String& threadToWait)
{
	try
	{
		return (MultiThreading::threads.at(threadToWait).TryGet<TRet>());
	}
	catch (Thread::IsStillAliveException& e)
	{
		throw (e);
	}
	catch (...)
	{
		throw (std::exception());
	}
}

template <typename TRet, typename TObject, typename... TFArgs, typename... TArgs>
void
MultiThreading::Create(String threadName, TRet (TObject::*memFun)(TFArgs...), TObject* objInstance, TArgs&&... args) noexcept
{
	MultiThreading::threads.insert(std::make_pair<String, Thread>(Meta::Move(threadName), Thread(memFun, objInstance, Meta::Move(args)...)));
}

template <typename TRet, typename... TFArgs, typename... TArgs>
void
MultiThreading::Create(String threadName, TRet (*fun)(TFArgs...), TArgs&&... args) noexcept
{
	MultiThreading::threads.insert(std::make_pair<String, Thread>(Meta::Move(threadName), Thread(fun, Meta::Move(args)...)));
}

template <typename TRet>
void
MultiThreading::Create(String threadName, TRet (*fun)()) noexcept
{
	MultiThreading::threads.insert(std::make_pair<String, Thread>(Meta::Move(threadName), Thread(fun)));
}

FORCEINLINE bool
MultiThreading::IsAlive(const String& threadName) noexcept
{
	return (MultiThreading::__isAlive__(threadName));
}

FORCEINLINE bool
MultiThreading::IsExist(const String& threadName) noexcept
{
	return (MultiThreading::__isExist__(threadName));
}

FORCEINLINE bool
MultiThreading::IsAlive(String&& threadName) noexcept
{
	return (MultiThreading::__isAlive__(Meta::Move(threadName)));
}

FORCEINLINE bool
MultiThreading::IsExist(String&& threadName) noexcept
{
	return (MultiThreading::__isExist__(Meta::Move(threadName)));
}

FORCEINLINE bool
MultiThreading::__isAlive__(String&& threadName) noexcept
{
	if (MultiThreading::threads.contains(Meta::Move(threadName)))
		if (MultiThreading::threads.at(Meta::Move(threadName)).IsAlive())
			return (true);
	return (false);
}

FORCEINLINE bool
MultiThreading::__isAlive__(const String& threadName) noexcept
{
	if (MultiThreading::threads.contains(Meta::Move(threadName)))
		if (MultiThreading::threads.at(Meta::Move(threadName)).IsAlive())
			return (true);
	return (false);
}

FORCEINLINE bool
MultiThreading::__isExist__(String&& threadName) noexcept
{
	return (MultiThreading::threads.contains(Meta::Move(threadName)));
}

FORCEINLINE bool
MultiThreading::__isExist__(const String& threadName) noexcept
{
	return (MultiThreading::threads.contains(Meta::Move(threadName)));
}

#endif
