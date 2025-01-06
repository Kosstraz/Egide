/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_THREADQUEUE_HPP
#define EGIDE_THREADQUEUE_HPP

# include "Function.hpp"
# include "Thread.hpp"
# include "Async.hpp"
# include "Mutex.hpp"
# include "Queue.hpp"
# include "Sleep.hpp"
# include "Trio.hpp"
# include "Let.hpp"

class ThreadQueue
{
private:
	static void	ThreadQueueManager(ThreadQueue* tq) noexcept; //Passer en non static

public:
	ThreadQueue() noexcept;
 
	template <typename TRet, typename... TArgs>
	FORCEINLINE
	ThreadQueue(Function<TRet(TArgs...)> fun, TArgs... args) noexcept;

	~ThreadQueue() noexcept;

	template <typename TRet, typename... TArgs>
	void	Push(Function<TRet(TArgs...)> fun, TArgs... args) noexcept;
	template <typename TFun, typename... TArgs>
	void	Push(TFun fun, TArgs... args) noexcept;

	template <typename TRet>
	void	Push(Function<TRet()> fun) noexcept;
	template <typename TFun>
	void	Push(TFun fun) noexcept;

	FORCEINLINE
	void	OpenQueue()				noexcept;
	FORCEINLINE
	void	CloseQueue()			noexcept;
	FORCEINLINE
	bool	QueueIsOpen()	const	noexcept;

	FORCEINLINE
	void	WaitQueue()				noexcept;

protected:
	Queue<letc>			queue;
	Mutex::Strict		mtx;
	bool				canPlay;
	bool				waitForDestroy;
	bool				isPlayingNow;
	SmartPtr<Thread>	manager;
};

# include "template/ThreadQueue.inl"
#endif
