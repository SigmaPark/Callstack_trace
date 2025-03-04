file(
	GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

add_executable(
	Example_test 
	${SRC_FILES}
)

target_link_libraries(
	Example_test PRIVATE
	Example_lib
)