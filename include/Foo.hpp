#pragma once
#include <cstddef>
#include <Windows.h>
#include <DbgHelp.h>


namespace prac
{

	class Callstack;
	struct Symbol_buffer;

}


class prac::Callstack
{
public:
	static constexpr std::size_t Max_stack_depth = 0x40;

	Callstack();

	auto operator[](const std::size_t index) const noexcept-> void*{  return _address_arr[index];  }
	auto hash() const noexcept-> unsigned long{  return _hash;  }
	auto count() const noexcept-> std::size_t{  return _count;  }

private:
	unsigned long _hash;
	std::size_t _count;
	void* _address_arr[Max_stack_depth];
};


struct prac::Symbol_buffer : public SYMBOL_INFO
{
	static constexpr std::size_t Buffer_size = 0x100;
	char buffer[Buffer_size];

	Symbol_buffer();
};