# Introduction to Callstack Trace Library
The prac::Callstack library provides a sophisticated yet elegantly simple solution   
for capturing and analyzing call stack information in modern C++ applications. Born from   
the necessity to debug complex software systems where understanding the execution flow   
is paramount, this library bridges the gap between raw debugging tools and practical   
application development needs.  
		  
Designed with cross-platform compatibility at its core, the library seamlessly adapts   
to different operating environments-leveraging Windows powerful DbgHelp API for detailed   
symbol resolution, while utilizing the robust backtrace functionality on Unix-like  
systems. This architectural flexibility ensures that developers can maintain consistent   
debugging capabilities regardless of their target platform.  
		  
# Basic Usage with Function Call Chain
This example demonstrates the fundamental usage of the prac::Callstack library   
by capturing a call stack within a nested function call scenario. The test creates   
a simple call chain: func1() calls func2(), which then captures the stack trace   
from within a lambda function.  
		  
```cpp
namespace test1_detail  
{  
  
	static void func2()  
	{  
		auto Lambda_f   
		=	[]  
			{  
				prac::Callstack const callstack;  
  
				for(auto const& line : callstack.symbol_strings())  
					std::cout << line << std::endl;  
			};  
  
		Lambda_f();  
	}  
  
	static void func1()  
	{  
		func2();  
	}  
  
}  
```

After calling "test1_detail::func1" on Windows platform, the result could be like this

```
[00007FF7AA9C5270] C:\Users\YourName\Programming\Callstack_trace\test\Test_Callstack_trace.cpp(41) : <lambda_51a28b13e18ef290787404aeb719a299>::operator()
[00007FF7AA9C5222] C:\Users\YourName\Programming\Callstack_trace\test\Test_Callstack_trace.cpp(59) : test1_detail::func2
[00007FF7AA9C616B] C:\Users\YourName\Programming\Callstack_trace\test\Test_Callstack_trace.cpp(64) : test1_detail::func1

...

[00007FF7AA9CDD68] C:\Users\YourName\Programming\Callstack_trace\test\test.cpp(14) : main

...
```