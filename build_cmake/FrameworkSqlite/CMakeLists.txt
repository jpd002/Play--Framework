cmake_minimum_required(VERSION 2.8)
project(Framework_Sqlite)

include(../Framework_Common.cmake)

find_package(SQLite3)
if(SQLITE3_FOUND)
	LIST(APPEND PROJECT_INCLUDES ${SQLITE3_INCLUDE_DIRS})
else()
	MESSAGE("-- Using Provided sqlite3 source")
	LIST(APPEND PROJECT_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/sqlite-3.20.1)
endif()

if(ANDROID)
	set(SRC_FILES)
	set(PLATFORM_SRC_FILES
		../../src/sqlite/SqliteAndroidAssetsVfs.cpp
		../../include/sqlite/SqliteAndroidAssetsVfs.h
	)
	add_library(Framework_Sqlite ${PLATFORM_SRC_FILES})
	target_include_directories(Framework_Sqlite PUBLIC ${PROJECT_INCLUDES} ${FRAMEWORK_INCLUDE_DIR})
else()
	add_library(Framework_Sqlite INTERFACE)
	target_include_directories(Framework_Sqlite INTERFACE ${PROJECT_INCLUDES} ${FRAMEWORK_INCLUDE_DIR})
endif()
