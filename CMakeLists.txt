cmake_minimum_required(VERSION 2.8)

project(safely)

SET(CMAKE_CXX_FLAGS "-std=c++1y -O3")
SET(CMAKE_INSTALL_PREFIX /usr)

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

INSTALL(
	FILES
		include/guard/access.h
		include/guard/lock.h
		include/guard/safecall.h
 	DESTINATION include/safely/guard
)

INSTALL(
	FILES
		include/locker/atomic.h
		include/locker/locker.h
 	DESTINATION include/safely/locker
)

INSTALL(
	FILES include/safely.h
 	DESTINATION include/safely
)

install (TARGETS safely LIBRARY DESTINATION lib)

target_link_libraries(safelytest safely pthread)