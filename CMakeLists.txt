cmake_minimum_required(VERSION 2.8)

project(ws)

SET(CMAKE_CXX_FLAGS "-std=c++1y -g3")

include_directories(include/)

file(
	GLOB_RECURSE
	source_files
	src/*
)

file(
	GLOB_RECURSE
	header_files
	include/*
)

add_executable(ws
	${header_files}
	${source_files}
)

target_link_libraries(ws pthread)