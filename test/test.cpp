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