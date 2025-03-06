#include "Foo.hpp"
#include <Windows.h>
#include <DbgHelp.h>
#include <iostream>
//========//========//========//========//=======#//========//========//========//========//=======#


prac::Callstack::Callstack() : _hash{0}, _count{0}, _address_arr{0, }
{
	_count = CaptureStackBackTrace(0, Max_stack_depth, _address_arr, &_hash);
}

