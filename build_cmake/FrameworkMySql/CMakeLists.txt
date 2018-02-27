cmake_minimum_required(VERSION 2.8)
project(Framework_MySql)

include(../Framework_Common.cmake)

find_package(MYSQL REQUIRED)

set(SRC_FILES
	../../src/mysql/Client.cpp
	../../src/mysql/Result.cpp
	../../src/mysql/AccessInfo.cpp
)

add_library(Framework_MySql ${SRC_FILES})
target_include_directories(Framework_MySql PUBLIC ${FRAMEWORK_INCLUDE_DIR} ${MYSQL_INCLUDE_DIR})
