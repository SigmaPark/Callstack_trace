/*  SPDX-FileCopyrightText: (c) 2025 Jin-Eon Park <greengb@naver.com> <sigma@gm.gist.ac.kr>
*   SPDX-License-Identifier: MIT License
*/
//========//========//========//========//=======#//========//========//========//========//=======#


#pragma once
#include <cstddef>
#include <string>
#include <vector>


namespace prac
{

	class Callstack;

}


class prac::Callstack
{
public:
	static constexpr std::size_t Max_stack_depth = 0x40 - 1;

	Callstack();

	auto begin() const noexcept-> void const* const*{  return _address_arr + 1;  }
	auto end() const noexcept-> void const* const*{  return begin() + size(); }
	auto size() const noexcept-> std::size_t{  return _depth;  }

	auto symbol_strings() const-> std::vector<std::string>;

private:
	void* _address_arr[Max_stack_depth + 1];
	std::size_t _depth;
};
