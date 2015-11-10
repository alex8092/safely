cmake_minimum_required(VERSION 2.8)

project(safely)

SET(CMAKE_CXX_FLAGS "-std=c++1y -O3")

include_directories(include/)

file(
	GLOB_RECURSE
	source_files
	src/locker/*
)

file(
	GLOB_RECURSE
	header_files
	include/*
)

add_library(safely SHARED
	${header_files}
	${source_files})

add_executable(safelytest
	${header_files}
	${source_files}
	src/main.cpp
)

target_link_libraries(safelytest safely pthread)