#  SPDX-FileCopyrightText: (c) 2025 Jin-Eon Park <greengb@naver.com> <sigma@gm.gist.ac.kr>
#   SPDX-License-Identifier: MIT License
#
#=========#=========#=========#=========#=========#=========#=========#=========#=========#=========


set(LIB_PROJECT_TITLE ${SOLUTION_TITLE}_lib)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)

file(
	GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

file(
	GLOB_RECURSE INCLUDE_FILES CONFIGURE_DEPENDS
	${INCLUDE_DIR}/*.hpp
	${INCLUDE_DIR}/*.h
)

add_library(
	${LIB_PROJECT_TITLE} STATIC 
	${SRC_FILES}
	${INCLUDE_FILES}
)

target_include_directories(
	${LIB_PROJECT_TITLE} PUBLIC 
	${INCLUDE_DIR}
)

target_compile_features(
	${LIB_PROJECT_TITLE} PUBLIC 
	cxx_std_17
)