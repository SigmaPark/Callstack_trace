#include "Foo.hpp"


prac::Callstack::Callstack() : _hash{0}, _count{0}, _address_arr{0, }
{
	_count = CaptureStackBackTrace(0, Max_stack_depth, _address_arr, &_hash);
}


prac::Symbol_buffer::Symbol_buffer()
{
	SYMBOL_INFO::MaxNameLen = static_cast<ULONG>(Buffer_size);
	SYMBOL_INFO::SizeOfStruct = sizeof(SYMBOL_INFO);
}