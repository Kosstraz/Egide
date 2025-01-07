#include "../ThreadQueue.hpp"

void
ThreadQueue::ThreadQueueManager(ThreadQueue* tq) noexcept
{
	tq->mtx.RLock();
	while (!tq->waitForDestroy)
	{
		tq->mtx.Unlock();
		tq->mtx.RLock();
		if (tq->canPlay && tq->queue.Size() > 0ULL)
		{
			tq->mtx.Unlock();
			tq->mtx.WRLock();
			tq->isPlayingNow = true;
			//Thread	t(tq->queue.Pop());
			tq->mtx.Unlock();
			//t.Wait();
			tq->mtx.WRLock();
			tq->isPlayingNow = false;
			tq->mtx.Unlock();
		}
		else
			tq->mtx.Unlock();
		Thread::Async::Yield();
	}
	tq->mtx.Unlock();
}

ThreadQueue::ThreadQueue() noexcept :	canPlay(true), waitForDestroy(false),
										isPlayingNow(true)
{
	//this->manager = Thread(ThreadQueue::ThreadQueueManager, this);
}

ThreadQueue::~ThreadQueue() noexcept
{
	this->mtx.WRLock();
	this->waitForDestroy = true;
	this->mtx.Unlock();
	this->manager->Wait();
}
