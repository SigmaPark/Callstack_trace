/*  SPDX-FileCopyrightText: (c) 2025 Jin-Eon Park <greengb@naver.com> <sigma@gm.gist.ac.kr>
*   SPDX-License-Identifier: MIT License
*/
//========//========//========//========//=======#//========//========//========//========//=======#


#pragma once
#include <cstddef>
#include <string>
#include <vector>


namespace cst
{

	class Callstack;

}


class cst::Callstack
{
public:
	static constexpr std::size_t Max_stack_depth = 0x40 - 1;

	Callstack(unsigned int skip_frames = 0);

	auto begin() const noexcept-> void const* const*{  return _address_arr + 1 + _skip_frames;  }
	auto end() const noexcept-> void const* const*{  return begin() + size(); }
	auto size() const noexcept-> std::size_t
	{
		return _depth > _skip_frames ? _depth - _skip_frames : 0;
	}

	auto symbol_strings() const-> std::vector<std::string>;

private:
	void* _address_arr[Max_stack_depth + 1];
	std::size_t _depth;
	unsigned int _skip_frames;
};
