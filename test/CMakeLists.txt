#  SPDX-FileCopyrightText: (c) 2025 Jin-Eon Park <greengb@naver.com> <sigma@gm.gist.ac.kr>
#   SPDX-License-Identifier: MIT License
#
#=========#=========#=========#=========#=========#=========#=========#=========#=========#=========


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
)