#ifndef NSL_THREADQUEUE_INL
#define NSL_THREADQUEUE_INL

# include "../ThreadQueue.hpp"

template <typename TRet, typename... TArgs>
ThreadQueue::ThreadQueue(Function<TRet(TArgs...)> fun, TArgs... args) noexcept 
					:	canPlay(true), waitForDestroy(false),
						isPlayingNow(true)
						
{
	this->manager = Thread(ThreadQueue::ThreadQueueManager, this);
	this->mtx.WRLock();
	this->queue.Push(letc(fun, args...));
	this->mtx.Unlock();
}

template <typename TRet, typename... TArgs>
void
ThreadQueue::Push(Function<TRet(TArgs...)> fun, TArgs... args) noexcept
{
	this->mtx.WRLock();
	this->queue.Push(letc(fun, Meta::Move(args)...));
	this->mtx.Unlock();
}

template <typename TFun, typename... TArgs>
void
ThreadQueue::Push(TFun fun, TArgs... args) noexcept
{
	this->mtx.WRLock();
	this->queue.Push(letc(fun, Meta::Move(args)...));
	this->mtx.Unlock();
}


template <typename TRet>
void
ThreadQueue::Push(Function<TRet()> fun) noexcept
{
	this->mtx.WRLock();
	this->queue.Push(letc(fun));
	this->mtx.Unlock();
}

template <typename TFun>
void
ThreadQueue::Push(TFun fun) noexcept
{
	this->mtx.WRLock();
	this->queue.Push(letc(fun));
	this->mtx.Unlock();
}

void
ThreadQueue::OpenQueue() noexcept
{
	this->mtx.WRLock();
	this->canPlay = true;
	this->mtx.Unlock();
}

void
ThreadQueue::CloseQueue() noexcept
{
	this->mtx.WRLock();
	this->canPlay = false;
	this->mtx.Unlock();
}

bool
ThreadQueue::QueueIsOpen() const noexcept
{
	return (this->canPlay);
}

void
ThreadQueue::WaitQueue() noexcept
{
	this->mtx.RLock();
	while (this->isPlayingNow)
	{
		this->mtx.Unlock();
		this->mtx.RLock();
	}
	this->mtx.Unlock();
}

#endif
