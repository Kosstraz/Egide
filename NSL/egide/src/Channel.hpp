/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#ifndef EGIDE_SYNC_HPP
#define EGIDE_SYNC_HPP

# include "Mutex.hpp"
# include "String.hpp"
# include "Sleep.hpp"
# include <map>

// You can safely send & receive data between any threads
class Channel final
{
public:
	Channel()				= delete;
	Channel(const Channel&)	= delete;
	Channel(Channel&&)		= delete;
	~Channel()				= delete;

		// FRANCAIS :
	// Toujours utiliser des ID différents, sinon cela pourrait provoquer des comportements indéfinis, tels que des segfault.
	// Quand un message est receptioné avec Receive(), l'ID est libéré et réutilisable.
	//
		// ENGLISH :
	// Always use different IDs, otherwise it may cause undefined behavior, such as segfault.
	// When a message is received with Thread::Receive(), the ID is released and can be reused.
	template <typename TRet>
	FORCEINLINE static void	Send(const String& messageID, const TRet& arg_to_send)
	{
		TRet*	argptr = new TRet;//static_cast<TRet*>(::operator new(sizeof(TRet)));
		*argptr = arg_to_send;
		Channel::mutex_send.Lock();
		Channel::async_send.insert(std::make_pair<const String&, void*>(messageID, argptr));
		Channel::mutex_send.Unlock();
		
	}

		// Receive a message from Thread::Send()
	template <typename TRet>
	FORCEINLINE static TRet	Receive(const String&& messageID)
	{
		Channel::mutex_send.Lock();
		while (!Channel::async_send.contains(messageID))
		{
			Channel::mutex_send.Unlock();
			Thread::Async::LongYield();
			Channel::mutex_send.Lock();
		}
		TRet*	ptr = static_cast<TRet*>(Channel::async_send.at(messageID));
		TRet	ret = *ptr;
		delete(ptr);//::operator delete(ptr);
		Channel::async_send.erase(messageID);
		Channel::mutex_send.Unlock();
		return (ret);
	}

private:
	static std::map<String, void*>
							async_send;
	static Mutex			mutex_send;
};

#endif
