/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#include "../MultiThreading.hpp"

thread_local std::map<String, Thread>	MultiThreading::threads = std::map<String, Thread>();

void
MultiThreading::Wait(const String& threadToWait) noexcept
{
	MultiThreading::threads.at(threadToWait).Wait();
	MultiThreading::threads.erase(threadToWait);
}
