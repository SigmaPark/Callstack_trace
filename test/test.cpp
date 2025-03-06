/*  SPDX-FileCopyrightText: (c) 2025 Jin-Eon Park <greengb@naver.com> <sigma@gm.gist.ac.kr>
*   SPDX-License-Identifier: MIT License
*/
//========//========//========//========//=======#//========//========//========//========//=======#


#include "Callstack_trace.hpp"
#include <iostream>


static void Test01()
{
	{
		prac::Callstack const callstack; 

		for(auto const& line : callstack.symbol_strings())
			std::cout << line << std::endl;
	}
}


int main(int const /*argc*/, char const* const /*argv*/[])
{
	::Test01();

	return 0;
}