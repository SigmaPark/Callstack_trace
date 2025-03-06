#include "Foo.hpp"
#include <iostream>


static void Test01()
{
	{
		prac::Symbol_lookup const lookup;
		prac::Callstack const callstack; 

		for(std::size_t i = 0;  i < callstack.count();  ++i)
			std::cout << lookup.symbol_string(callstack[i]) << std::endl;
	}
}


int main(int const /*argc*/, char const* const /*argv*/[])
{
	::Test01();

	return 0;
}