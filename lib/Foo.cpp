#include "Foo.hpp"


prac::Callstack::Callstack() : _hash{0}, _count{0}, _address_arr{0, }
{
	_count = CaptureStackBackTrace(0, Max_stack_depth, _address_arr, &_hash);
}


prac::Symbol_lookup::Symbol_lookup() : _handle(GetCurrentProcess())
{
	SymInitialize(_handle, NULL, TRUE);
	SymSetOptions(SYMOPT_LOAD_LINES);
}


template<class T>
class Useless
{
public:
	operator T&() const noexcept{  return *&*this;  }
	auto operator&() const noexcept-> T*{  return reinterpret_cast<T*>(_buf);  }

private:
	mutable std::byte _buf[sizeof(T)];
};


auto prac::Symbol_lookup::symbol_string(void const* const address) const-> std::string
{
	if(address == nullptr)
		return "";


	auto const addr = reinterpret_cast<DWORD64>(address);

	Symbol_buffer const symbol
	=	[handle = _handle, addr]
		{
			Symbol_buffer res;

			SymFromAddr(handle, addr, 0, &res);

			return res;
		}();


	char buffer[_String_buffer_size] = {0, };

	if
	(	IMAGEHLP_LINE64 line{sizeof(IMAGEHLP_LINE64)}
	;	SymGetLineFromAddr64(_handle, addr, &Useless<DWORD>{}, &line)
	)
		sprintf_s
		(	buffer, _String_buffer_size, "%s(%d) : %s"
		,	line.FileName, line.LineNumber, symbol.Name
		);
	else
		sprintf_s(buffer, _String_buffer_size, "No line info : %s", symbol.Name);

	return buffer;
}


prac::Symbol_buffer::Symbol_buffer()
{
	SYMBOL_INFO::MaxNameLen = static_cast<ULONG>(Buffer_size);
	SYMBOL_INFO::SizeOfStruct = sizeof(SYMBOL_INFO);
}

