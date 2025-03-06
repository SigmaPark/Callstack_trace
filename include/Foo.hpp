#pragma once
#include <cstddef>
#include <string>


namespace prac
{

	class Callstack;
	class Symbol_lookup;

}


class prac::Callstack
{
public:
	static constexpr std::size_t Max_stack_depth = 0x40;

	Callstack();

	auto begin() const noexcept-> void const* const*{  return _address_arr;  }
	auto end() const noexcept-> void const* const*{  return begin() + size(); }
	auto size() const noexcept-> std::size_t{  return _depth;  }

private:
	std::size_t _depth;
	void* _address_arr[Max_stack_depth];
};


class prac::Symbol_lookup
{
public:
	Symbol_lookup();

	auto symbol_string(void const* const address) const-> std::string;

private:
	static std::size_t constexpr _String_buffer_size_for_1_line = 0x400;
	void* _handle;
};
