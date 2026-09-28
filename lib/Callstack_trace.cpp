/*  SPDX-FileCopyrightText: (c) 2025 Jin-Eon Park <greengb@naver.com> <sigma@gm.gist.ac.kr>
*   SPDX-License-Identifier: MIT License
*/
//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$

#include "Callstack_trace.hpp"
#include <algorithm>
#include <cassert>

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#include <DbgHelp.h>
#include <sstream>
#pragma comment(lib, "dbghelp.lib")

namespace{
	// An out-parameter nobody is going to read.
	template<class T>
	class Useless{
	public:
		auto operator&() const noexcept->T *{ return reinterpret_cast<T *>(_buf); }
	private:
		alignas(T) mutable std::byte _buf[sizeof(T)];
	};

	struct Symbol_Buffer
	: public SYMBOL_INFO{
		Symbol_Buffer() noexcept
		: SYMBOL_INFO{}, _name_tail{}{
			SYMBOL_INFO::MaxNameLen = static_cast<ULONG>(_Name_capacity);
			SYMBOL_INFO::SizeOfStruct = sizeof(SYMBOL_INFO);
		}
	private:
		static std::size_t constexpr _Name_capacity = 0x100;

		// Never touched by name; SymFromAddr writes into it through SYMBOL_INFO::Name.
		char _name_tail[_Name_capacity];
	};

	auto Symbol_string(HANDLE const process, void const * const address)->std::string{
		if(address == nullptr){ return ""; }

		auto const addr = reinterpret_cast<DWORD64>(address);

		Symbol_Buffer const  
			symbol
			= [process, addr]{
				Symbol_Buffer res;

				SymFromAddr(process, addr, nullptr, &res);

				return res;
			}()
		;

		IMAGEHLP_LINE64 line{ sizeof(IMAGEHLP_LINE64) };
		std::ostringstream oss;

		oss << '[' << address << "] ";

		if( SymGetLineFromAddr64(process, addr, &Useless<DWORD>{}, &line) ){
			oss << line.FileName << '(' << line.LineNumber << ')';
		} else{
			oss << "No line info";
		}

		oss << " : " << symbol.Name;

		return oss.str();
	}
}
//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$

cst::Callstack_Trace::Callstack_Trace(std::size_t const skip_frames)
:
	_address_arr{},
	_depth(
		std::max<std::size_t>(
			CaptureStackBackTrace(0, Max_stack_depth + 1, _address_arr, &Useless<ULONG>{}), 1
		)
		- 1
	),
	_skip_frames(skip_frames)
{
	assert(_depth >= _skip_frames);
}

auto cst::Callstack_Trace::symbol_strings() const->std::vector<std::string>{
	HANDLE const  
		cur_process
		= []{
			HANDLE const res = GetCurrentProcess();

			SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);
			SymInitialize(res, nullptr, TRUE);

			return res;
		}()
	;

	std::vector<std::string> res;

	res.reserve(size());

	for(auto const address : *this){
		res.emplace_back( Symbol_string(cur_process, address) );
	}

	return res;
}
//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$

#elif defined(__unix__) || defined(__unix) || defined(unix)
#include <cstdlib>
#include <cxxabi.h>
#include <execinfo.h>
#include <memory>

namespace{
	// backtrace_symbols yields "module(mangled+offset) [address]". Demangle the part in parentheses,
	// or return the line untouched when there is no symbol or it is not a C++ name.
	auto Demangled(char const* const line)->std::string{
		std::string res = line;

		auto const open_pos = res.find('(');
		auto const plus_pos = res.find('+', open_pos);

		if(open_pos == std::string::npos || plus_pos == std::string::npos || plus_pos == open_pos + 1)
			return res;

		std::string const mangled = res.substr(open_pos + 1, plus_pos - open_pos - 1);
		int status = -1;

		std::unique_ptr<char, void(*)(void*)> const
			name( abi::__cxa_demangle(mangled.c_str(), nullptr, nullptr, &status), &std::free )
		;

		if(status == 0 && name != nullptr)
			res.replace(open_pos + 1, mangled.size(), name.get());

		return res;
	}
}

cst::Callstack_Trace::Callstack_Trace(std::size_t const skip_frames)
:
	_address_arr{},
	_depth(  std::max( backtrace(_address_arr, Max_stack_depth + 1), 1 ) - 1  ),
	_skip_frames(skip_frames)
{
	assert(_depth >= _skip_frames);
}

auto cst::Callstack_Trace::symbol_strings() const->std::vector<std::string>{
	std::unique_ptr<char *, void(*)(void *)> const  
		strings(
			backtrace_symbols( _address_arr + _skip_frames + 1, static_cast<int>(size()) ),
			&std::free
		)
	;

	std::vector<std::string> res;

	if(strings == nullptr)
		return res;

	res.reserve( size() );

	for(std::size_t i = 0;  i < size();  ++i)
		res.push_back( Demangled(strings.get()[i]) );

	return res;
}
//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$//--//--//--//--//-$

#else
#error "cst::Callstack_Trace is not implemented for this platform."
#endif
