/*  SPDX-FileCopyrightText: (c) 2025 Jin-Eon Park <greengb@naver.com> <sigma@gm.gist.ac.kr>
*   SPDX-License-Identifier: MIT License
*/
//========//========//========//========//=======#//========//========//========//========//=======#


#include "Test_Callstack_trace.hpp"
#include "Callstack_trace.hpp"
#include <iostream>


static void intro()
{
	sgm::h2u::mdo 
	<<	sgm::h2u::Title(L"Introduction to Callstack Trace Library")
	<<	LR"(
		The prac::Callstack library provides a sophisticated yet elegantly simple solution 
		for capturing and analyzing call stack information in modern C++ applications. Born from 
		the necessity to debug complex software systems where understanding the execution flow 
		is paramount, this library bridges the gap between raw debugging tools and practical 
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
				prac::Callstack const callstack;

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
		This example demonstrates the fundamental usage of the prac::Callstack library 
		by capturing a call stack within a nested function call scenario. The test creates 
		a simple call chain: func1() calls func2(), which then captures the stack trace 
		from within a lambda function.
		)"_mdo;

	test1_detail::func1();

	sgm::h2u::mdo << sgm::h2u::Load_code_block(L"test1_ex");
}


SGM_HOW2USE_TESTS(prac::test::Test_, Callstack_trace, /**/)
{   ::intro
,	::Test01
};