/*  SPDX-FileCopyrightText: (c) 2025 Jin-Eon Park <greengb@naver.com> <sigma@gm.gist.ac.kr>
*   SPDX-License-Identifier: MIT License
*/
//========//========//========//========//=======#//========//========//========//========//=======#


#include "Test_Callstack_Trace.hpp"
#include "Callstack_Trace.hpp"
#include <iostream>


static void intro()
{
	sgm::h2u::mdo 
	<<	sgm::h2u::Title(L"Introduction to Callstack Trace Library")
	<<	LR"(
		The cst::Callstack_Trace library provides a sophisticated yet elegantly simple solution 
		for capturing and analyzing call stack information in modern C++ applications. Born from 
		the necessity to debug complex software systems where understanding the execution flow 
		is paramount, this library bridges the gap between raw debugging tools and csttical 
		application development needs.
		
		Designed with cross-platform compatibility at its core, the library seamlessly adapts 
		to different operating environments-leveraging Windows powerful DbgHelp API for detailed 
		symbol resolution, while utilizing the robust backtrace functionality on Unix-like
		systems. This architectural flexibility ensures that developers can maintain consistent 
		debugging capabilities regardless of their target platform.
		)"_mdo;
}


BEGIN_CODE_BLOCK(test1_ex)
namespace test1_detail
{

	static void func2()
	{
		auto Lambda_f 
		=	[]
			{
				cst::Callstack_Trace const callstack;

				for(auto const& line : callstack.symbol_strings())
					std::cout << line << std::endl;

				SGM_H2U_ASSERT(callstack.symbol_strings().size() >= 3);

				SGM_H2U_ASSERT
				(	callstack.symbol_strings()[1].find("test1_detail::func2") 
				!=	std::string::npos
				);

				SGM_H2U_ASSERT
				(	callstack.symbol_strings()[2].find("test1_detail::func1") 
				!=	std::string::npos
				);
			};

		Lambda_f();
	}

	static void func1()
	{
		func2();
	}

}
END_CODE_BLOCK(test1_ex)


static void Test01()
{
	sgm::h2u::mdo
	<<	sgm::h2u::Title(L"Basic Usage with Function Call Chain")
	<<	LR"(
		This example demonstrates the fundamental usage of the cst::Callstack_Trace library 
		by capturing a call stack within a nested function call scenario. The test creates 
		a simple call chain: func1() calls func2(), which then captures the stack trace 
		from within a lambda function.
		)"_mdo;

	test1_detail::func1();

	sgm::h2u::mdo << sgm::h2u::Load_code_block(L"test1_ex");
}


BEGIN_CODE_BLOCK(test2_ex)
namespace test2_detail
{

	static void wrapper_level2()
	{
		// Skip 2 frames: this function and wrapper_level1
		cst::Callstack_Trace const callstack{2};

		auto const strings = callstack.symbol_strings();

		for(auto const& line : strings)
			std::cout << line << std::endl;

		// Verify that the first visible frame is wrapper_level0 or its caller
		SGM_H2U_ASSERT(callstack.size() >= 1);

		// The first frame should NOT contain "wrapper_level2" or "wrapper_level1"
		SGM_H2U_ASSERT(strings[0].find("wrapper_level2") == std::string::npos);
		SGM_H2U_ASSERT(strings[0].find("wrapper_level1") == std::string::npos);
	}

	static void wrapper_level1()
	{
		wrapper_level2();
	}

	static void wrapper_level0()
	{
		wrapper_level1();
	}

}
END_CODE_BLOCK(test2_ex)


static void Test02()
{
	sgm::h2u::mdo
	<<	sgm::h2u::Title(L"Frame Skipping for Wrapper Functions")
	<<	LR"(
		This test demonstrates the frame skipping feature that allows debugging tools
		to exclude their own wrapper functions from the call stack output. By passing
		a skip count to the Callstack_Trace constructor, the top N frames can be hidden,
		revealing only the meaningful application-level call chain.
		)"_mdo;

	test2_detail::wrapper_level0();

	sgm::h2u::mdo << sgm::h2u::Load_code_block(L"test2_ex");
}


SGM_HOW2USE_TESTS(cst::test::Test_, Callstack_Trace, /**/)
{   ::intro
,	::Test01
,	::Test02
};