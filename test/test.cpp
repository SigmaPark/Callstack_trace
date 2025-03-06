#include "Foo.hpp"
#include <string>
#include <iostream>


static void Test01()
{
	{
	#if 0
		prac::SymbolLookup lookup;

		prac::Callstack callstack; 
		for(size_t i = 0;  i < callstack.GetCount();  ++i)
		{
			std::string const& str = lookup.GetSymbolString(callstack[i]);
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