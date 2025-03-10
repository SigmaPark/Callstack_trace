/*  SPDX-FileCopyrightText: (c) 2025 Jin-Eon Park <greengb@naver.com> <sigma@gm.gist.ac.kr>
*   SPDX-License-Identifier: MIT License
*/
//========//========//========//========//=======#//========//========//========//========//=======#


#include "Callstack_trace.hpp"


#ifdef WIN32
template<class T>
class Useless
{
public:
	operator T&() const noexcept{  return *&*this;  }
	auto operator&() const noexcept-> T*{  return reinterpret_cast<T*>(_buf);  }

private:
	mutable std::byte _buf[sizeof(T)];
};


#include <Windows.h>
#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")


struct _Symbol_buffer : public SYMBOL_INFO
{
	_Symbol_buffer() noexcept;

private:
	static constexpr std::size_t _String_buffer_size_for_name = 0x100;
	
	// Won't be used directly but will be overwrited by pointer.
	char _buffer_for_name_string[_String_buffer_size_for_name]; 
};


static auto _Symbol_string(void* const handle, void const* const address)-> std::string;
//--------//--------//--------//--------//-------#//--------//--------//--------//--------//-------#


prac::Callstack::Callstack() 
:	_address_arr{0, }
,	_depth( CaptureStackBackTrace(0, Max_stack_depth + 1, _address_arr, &Useless<ULONG>{}) - 1 )
{}


auto prac::Callstack::symbol_strings() const-> std::vector<std::string>
{
	HANDLE const cur_handle
	=	[]
		{
			HANDLE res = GetCurrentProcess();
			
			SymInitialize(res, NULL, TRUE);
			SymSetOptions(SYMOPT_LOAD_LINES);

			return res;
		}();

	std::vector<std::string> res;
	
	res.reserve(size());

	for(auto const address : *this)
		res.emplace_back( ::_Symbol_string(cur_handle, address) );

	return res;
}


auto _Symbol_string(void* const handle, void const* const address)-> std::string
{
	if(address == nullptr)
		return "";


	auto const addr = reinterpret_cast<DWORD64>(address);

	::_Symbol_buffer const symbol
	=	[handle, addr]
		{
			::_Symbol_buffer res;

			SymFromAddr(handle, addr, 0, &res);

			return res;
		}();

	std::size_t constexpr Max_string_size_per_line = 0x400;
	char buffer[Max_string_size_per_line] = {0, };

	if
	(	IMAGEHLP_LINE64 line{sizeof(IMAGEHLP_LINE64)}
	;	SymGetLineFromAddr64(handle, addr, &Useless<DWORD>{}, &line)
	)
		sprintf_s
		(	buffer, Max_string_size_per_line, "[%p] %s(%d) : %s"
		,	address, line.FileName, line.LineNumber, symbol.Name
		);
	else
		sprintf_s
		(	buffer, Max_string_size_per_line, "[%p] No line info : %s"
		,	address, symbol.Name
		);

	return buffer;	
}
//--------//--------//--------//--------//-------#//--------//--------//--------//--------//-------#


::_Symbol_buffer::_Symbol_buffer() noexcept : _buffer_for_name_string{0, }
{
	SYMBOL_INFO::MaxNameLen = static_cast<ULONG>(_String_buffer_size_for_name);
	SYMBOL_INFO::SizeOfStruct = sizeof(SYMBOL_INFO);
}
//========//========//========//========//=======#//========//========//========//========//=======#


#elif defined(__unix__) || defined(__unix) || defined(unix)
#include <execinfo.h>
#include <memory>


prac::Callstack::Callstack() 
:	_address_arr{0, }
,	_depth( backtrace(_address_arr, Max_stack_depth + 1) - 1 )
{}


auto prac::Callstack::symbol_strings() const-> std::vector<std::string>
{
	std::unique_ptr<char*, decltype(&free)> strings
	(	backtrace_symbols(_address_arr + 1, size())
	,	&free
	);

	std::vector<std::string> res;
	
	res.reserve(size());

	for(std::size_t i = 0;  i < size();  ++i)
		res.emplace_back(strings.get()[i]);

	return res;	
}

#else

#endif