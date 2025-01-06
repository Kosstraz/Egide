/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_MULTITHREADING_HPP
#define EGIDE_MULTITHREADING_HPP

# include "Thread.hpp"
# include "String.hpp"
# include <map>

// It's a simpler way to create thread and manage them.
class MultiThreading final : private Thread
{
public:
	explicit MultiThreading(const MultiThreading&) 	= delete;
	explicit MultiThreading(MultiThreading&&) 		= delete;
	explicit MultiThreading()						= delete;
	virtual ~MultiThreading()						= delete;

	template <typename TRet, typename TObject, typename... TFArgs, typename... TArgs>
	static void	Create(String threadName, TRet (TObject::*)(TFArgs...), TObject* objInstance, TArgs&&... args) noexcept;
	template <typename TRet, typename... TFArgs, typename... TArgs>
	static void	Create(String threadName, TRet (*)(TFArgs...), TArgs&&... args) noexcept;
	template <typename TRet>
	static void	Create(String threadName, TRet (*)()) noexcept;
	template <typename TRet>
	static TRet	Get(const String& threadToGet) noexcept;
	template <typename TRet>
	static TRet	TryGet(const String& threadToGet);

	using Thread::Wait;
	static void	Wait(const String& threadToWait) noexcept ;

	using Thread::IsAlive;
	static FORCEINLINE bool	IsAlive(const String& threadName) noexcept;
	
	static FORCEINLINE bool	IsExist(const String& threadName) noexcept;

	
	static FORCEINLINE bool	IsAlive(String&& threadName) noexcept;
	
	static FORCEINLINE bool	IsExist(String&& threadName) noexcept;

private:

	static FORCEINLINE bool	__isAlive__(const String& threadName) noexcept;
	
	static FORCEINLINE bool	__isAlive__(String&& threadName) noexcept;

	static FORCEINLINE bool	__isExist__(const String& threadName) noexcept;
	
	static FORCEINLINE bool	__isExist__(String&& threadName) noexcept;

private:
	thread_local static std::map<String, Thread>	threads;
};

# include "template/MultiThreading.inl"
#endif
