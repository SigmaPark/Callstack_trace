#  SPDX-FileCopyrightText: (c) 2025 Jin-Eon Park <greengb@naver.com> <sigma@gm.gist.ac.kr>
#   SPDX-License-Identifier: MIT License
#
#=========#=========#=========#=========#=========#=========#=========#=========#=========#=========


include(FetchContent)
FetchContent_Declare(
	How2use
	GIT_REPOSITORY https://github.com/SigmaPark/How2use.git
	GIT_TAG v2.1.1
)

set(BUILD_HOW2USE_TEST_PROJ OFF CACHE BOOL "Disable How2use's test project build" FORCE)
FetchContent_MakeAvailable(How2use)


set(TEST_PROJECT_TITLE ${SOLUTION_TITLE}_test)

file(
	GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

add_executable(
	${TEST_PROJECT_TITLE} 
	${SRC_FILES}
)

target_link_libraries(
	${TEST_PROJECT_TITLE} PRIVATE
	${SOLUTION_TITLE}_lib
    How2use_lib
)