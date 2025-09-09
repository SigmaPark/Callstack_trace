/*  SPDX-FileCopyrightText: (c) 2025 Jin-Eon Park <greengb@naver.com> <sigma@gm.gist.ac.kr>
*   SPDX-License-Identifier: MIT License
*/
//========//========//========//========//=======#//========//========//========//========//=======#


#include "Test_Callstack_trace.hpp"


int main(int const /*argc*/, char const* const /*argv*/ [])
{
	try
	{
		prac::test::Test_Callstack_trace::test();
	}
	catch(std::exception& xc)
	{
		std::cerr << "Test failed by an exception : " << xc.what() << std::endl;

		return -1;
	}
	catch(...)
	{
		std::cerr << "Test failed by an unexpected exception ." << std::endl;

		return -1;
	}

	return 0;
}
