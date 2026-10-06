/*  SPDX-FileCopyrightText: (c) 2025 Jin-Eon Park <greengb@naver.com> <sigma@gm.gist.ac.kr>
*   SPDX-License-Identifier: MIT License
*/
//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$

#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace cst{
	class Callstack_Trace;
}
//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$

class cst::Callstack_Trace{
public:
	static std::size_t constexpr Max_stack_depth = 0x100 - 1;

	// The frame of this constructor is always skipped; skip_frames skips that many more.
	Callstack_Trace(std::size_t skip_frames = 0);

	auto begin() const noexcept->void const * const *{ return _address_arr + _skip_frames + 1; }
	auto end() const noexcept->void const * const *{ return begin() + size(); }
	auto size() const noexcept->std::size_t{ return _depth - _skip_frames; }

	auto symbol_strings() const->std::vector<std::string>;

private:
	void *_address_arr[Max_stack_depth + 1];
	std::size_t _depth, _skip_frames;
};

