#include "Foo.hpp"
#include <Windows.h>
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")


template<class T>
class Useless
{
public:
	operator T&() const noexcept{  return *&*this;  }
	auto operator&() const noexcept-> T*{  return reinterpret_cast<T*>(_buf);  }

private:
	mutable std::byte _buf[sizeof(T)];
};


prac::Callstack::Callstack() : _depth{0}, _address_arr{0, }
{
	_depth = CaptureStackBackTrace(0, Max_stack_depth, _address_arr, &Useless<ULONG>{});
}


prac::Symbol_lookup::Symbol_lookup() : _handle(GetCurrentProcess())
{
	SymInitialize(_handle, NULL, TRUE);
	SymSetOptions(SYMOPT_LOAD_LINES);
}


namespace prac
{
	
	struct _Symbol_buffer;

}


struct prac::_Symbol_buffer : public SYMBOL_INFO
{
	_Symbol_buffer() noexcept;

private:
	static constexpr std::size_t _String_buffer_size_for_name = 0x100;
	
	// Won't be used directly but will be overwrited by pointer.
	char _buffer_for_name_string[_String_buffer_size_for_name]; 
};


auto prac::Symbol_lookup::symbol_string(void const* const address) const-> std::string
{
	if(address == nullptr)
		return "";


	auto const addr = reinterpret_cast<DWORD64>(address);

	_Symbol_buffer const symbol
	=	[handle = _handle, addr]
		{
			_Symbol_buffer res;

			SymFromAddr(handle, addr, 0, &res);

			return res;
		}();

	char buffer[_String_buffer_size_for_1_line] = {0, };

	if
	(	IMAGEHLP_LINE64 line{sizeof(IMAGEHLP_LINE64)}
	;	SymGetLineFromAddr64(_handle, addr, &Useless<DWORD>{}, &line)
	)
		sprintf_s
		(	buffer, _String_buffer_size_for_1_line, "%s(%d) : %s"
		,	line.FileName, line.LineNumber, symbol.Name
		);
	else
		sprintf_s(buffer, _String_buffer_size_for_1_line, "No line info : %s", symbol.Name);

	return buffer;
}


prac::_Symbol_buffer::_Symbol_buffer() noexcept : _buffer_for_name_string{0, }
{
	SYMBOL_INFO::MaxNameLen = static_cast<ULONG>(_String_buffer_size_for_name);
	SYMBOL_INFO::SizeOfStruct = sizeof(SYMBOL_INFO);
}

