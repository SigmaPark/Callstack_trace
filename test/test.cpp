#include "Foo.hpp"
#include <iostream>


static void Test01()
{
	{
		prac::Symbol_lookup const lookup;
		prac::Callstack const callstack; 

		for(auto const address : callstack)
			std::cout << lookup.symbol_string(address) << std::endl;
	}
}


int main(int const /*argc*/, char const* const /*argv*/[])
{
	::Test01();

	return 0;
}