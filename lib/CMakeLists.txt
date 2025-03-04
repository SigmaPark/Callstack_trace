file(
	GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

add_library(
	Example_lib STATIC ${SRC_FILES}
)

target_include_directories(
	Example_lib PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_compile_features(
	Example_lib PUBLIC 
	cxx_std_17
)