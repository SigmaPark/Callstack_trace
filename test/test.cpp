#include "Foo.hpp"
#include <iostream>


static void Test01()
{
	{
	#if 0
		prac::SymbolLookup lookup;

		prac::Callstack callstack; 
		for(size_t i = 0;  i < callstack.count();  ++i)
		{
			std::string const str = lookup.symbol_string(callstack[i]);
			std::cout << str << std::endl;
		}
	#endif
	}

	
}


int main(int const /*argc*/, char const* const /*argv*/[])
{
	::Test01();

	return 0;
}