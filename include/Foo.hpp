#pragma once
#include <cstddef>


namespace prac
{

	class Callstack;

}


class prac::Callstack
{
public:
	static constexpr std::size_t Max_stack_depth = 64;

	Callstack();

	auto operator[](const std::size_t index) const noexcept-> void*{  return _address_arr[index];  }
	auto GetHash() const noexcept-> unsigned long{  return _hash;  }
	auto GetCount() const noexcept-> std::size_t{  return _count;  }

private:
	unsigned long _hash;
	std::size_t _count;
	void* _address_arr[Max_stack_depth];
};