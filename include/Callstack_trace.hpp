#pragma once
#include <cstddef>
#include <string>
#include <vector>


namespace prac
{

	class Callstack;

}


class prac::Callstack
{
public:
	static constexpr std::size_t Max_stack_depth = 0x40;

	Callstack();

	auto begin() const noexcept-> void const* const*{  return _address_arr;  }
	auto end() const noexcept-> void const* const*{  return begin() + size(); }
	auto size() const noexcept-> std::size_t{  return _depth;  }

	auto symbol_strings() const-> std::vector<std::string>;

private:
	void* _address_arr[Max_stack_depth];
	std::size_t _depth;
};
