cmake_minimum_required(VERSION 2.8)
project(Framework_Sqlite)

include(../Framework_Common.cmake)

find_package(SQLite3)
if(SQLite3_FOUND)
	LIST(APPEND PROJECT_LIBS SQLite::SQLite3)
else()
	MESSAGE("-- Using Provided sqlite3 source")
	if(NOT TARGET sqlite3static)
		add_subdirectory(
			${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/build_cmake/sqlite-3.20.1
			${CMAKE_CURRENT_BINARY_DIR}/sqlite-3.20.1
		)
	endif()
	LIST(APPEND PROJECT_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/sqlite-3.20.1)
	LIST(APPEND PROJECT_LIBS sqlite3static)
endif()

if(ANDROID)
	set(SRC_FILES)
	set(PLATFORM_SRC_FILES
		../../src/sqlite/SqliteAndroidAssetsVfs.cpp
		../../include/sqlite/SqliteAndroidAssetsVfs.h
	)
	add_library(Framework_Sqlite ${PLATFORM_SRC_FILES})
	target_include_directories(Framework_Sqlite PUBLIC ${PROJECT_INCLUDES} ${FRAMEWORK_INCLUDE_DIR})
	target_link_libraries(Framework_Sqlite PUBLIC ${PROJECT_LIBS})
else()
	add_library(Framework_Sqlite INTERFACE)
	target_include_directories(Framework_Sqlite INTERFACE ${PROJECT_INCLUDES} ${FRAMEWORK_INCLUDE_DIR})
	target_link_libraries(Framework_Sqlite INTERFACE ${PROJECT_LIBS})
endif()
