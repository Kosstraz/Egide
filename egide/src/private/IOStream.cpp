/*
 * Copyright (c) 2024 Kosstraz/Bama
 * Licensed under the MIT License.
*/

#include "../IOStreams.hpp"

namespace IO
{

Streams::Streams() noexcept : text(""), keep(false), save(false)
{
}

Streams::Streams(const Streams& s) noexcept : text(s.text), keep(s.keep), save(s.save)
{
}

void
Streams::__keep__(Streams& s) noexcept
{
	s.keep = true;
	s.save = false;
}

void
Streams::__save__(Streams& s) noexcept
{
	s.keep = false;
	s.save = true;
}

void
Streams::__reset__(Streams& s) noexcept
{
	s.keep = false;
	s.save = false;
}

void
Streams::__clear__(Streams& s) noexcept
{
	s.ClearStockedText();
}

void
Streams::__flush__(Streams& s) noexcept
{
	uint64 __Wno;
	if (!s.GetStockedText().Empty())
		__Wno = write(STDOUT_FILENO, s.GetStockedText().Data(), s.GetStockedText().Len());
	if (s.save)
		s.ClearStockedText();
	(void)__Wno;
}

thread_local Streams	Stream	= Streams();
thread_local Streams&	Echo	= Stream;
thread_local Streams&	Fetch	= Stream;
// Does not display what happens after the mode is activated, but stores it in memory
thread_local void (*KeepMode)(Streams&) = Streams::__keep__;
// Displays what happens after the mode is activated and stores it in memory
thread_local void (*SaveMode)(Streams&) = Streams::__save__;
// Disable IO::KeepMode and IO::SaveMode
thread_local void (*ResetMode)(Streams&) = Streams::__reset__;
// Clear IO::Stream/IO::Echo/IO::Fetch memory
thread_local void (*Clear)(Streams&) = Streams::__clear__;
// Displays the contents of IO::Stream/IO::Echo/IO::Fetch, and clears its memory (unless IO::SaveMode is active)
thread_local void (*Flush)(Streams&) = Streams::__flush__;

}
