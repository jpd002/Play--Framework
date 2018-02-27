cmake_minimum_required(VERSION 2.8)
project(Framework_Http)

include(../Framework_Common.cmake)

find_package(SQLite3)
if(NOT SQLITE3_FOUND)
	MESSAGE("-- Using Provided sqlite3 source")
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/sqlite-3.20.1)
else()
	include_directories(${SQLITE3_INCLUDE_DIRS})
endif()

set(SRC_FILES)

if(ANDROID)
	set(PLATFORM_SRC_FILES
		../../src/sqlite/SqliteAndroidAssetsVfs.cpp
		../../include/sqlite/SqliteAndroidAssetsVfs.h
	)
endif()

add_library(Framework_Sqlite ${SRC_FILES} ${PLATFORM_SRC_FILES})
target_include_directories(Framework_Http PUBLIC ${FRAMEWORK_INCLUDE_DIR})
