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


auto prac::Symbol_lookup::symbol_string(void const* const address) const-> std::string
{
	if(address == nullptr)
		return "";
	

	DWORD displacement = 0;
	auto addr = reinterpret_cast<DWORD64>(address);

	Symbol_buffer symbol;
	char buffer[_String_buffer_size] = {0, };

	// �ּҿ� �����ϴ� �ɺ��� �����̸� + line�� ������ ��ü		
	IMAGEHLP_LINE64 line;
	line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

	// SymbolBuffer ��ü�� address�� �����ϴ� �ɺ� �̸�(�Լ���) ����
	SymFromAddr(_handle, addr, 0, &symbol);

	if( SymGetLineFromAddr64(_handle, addr, &displacement, &line) )
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

