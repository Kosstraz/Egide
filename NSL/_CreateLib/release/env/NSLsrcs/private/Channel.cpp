# include "../Channel.hpp"

std::map<String, void*>	Channel::async_send	= std::map<String, void*>();
Mutex					Channel::mutex_send	= Mutex();
