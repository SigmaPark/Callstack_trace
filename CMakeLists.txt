cmake_minimum_required(VERSION 3.5)

set(SOLUTION_TITLE Callstack_trace)

project(
	${SOLUTION_TITLE}_sln
	LANGUAGES CXX
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(lib)

option(BUILD_TEST_PROJ "Build test project" ON)
if(BUILD_TEST_PROJ)
	add_subdirectory(test)
endif()