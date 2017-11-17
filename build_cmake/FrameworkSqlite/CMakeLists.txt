cmake_minimum_required(VERSION 2.8)
project(Framework_Http)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++")
endif(APPLE)

find_package(SQLite3)
if(NOT SQLITE3_FOUND)
	MESSAGE("-- Using Provided sqlite3 source")
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/sqlite-3.20.1)
else()
	include_directories(${SQLITE3_INCLUDE_DIRS})
endif()

include_directories(../../include)

set(SRC_FILES)

if(ANDROID)
	set(PLATFORM_SRC_FILES
		../../src/sqlite/SqliteAndroidAssetsVfs.cpp
		../../include/sqlite/SqliteAndroidAssetsVfs.h
	)
endif()

add_library(Framework_Sqlite ${SRC_FILES} ${PLATFORM_SRC_FILES})
