cmake_minimum_required(VERSION 2.8)
project(Framework_MySql)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MYSQL REQUIRED)

set(SRC_FILES
	../../src/mysql/Client.cpp
	../../src/mysql/Result.cpp
	../../src/mysql/AccessInfo.cpp
)

add_library(Framework_MySql ${SRC_FILES})
target_include_directories(Framework_MySql PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include ${MYSQL_INCLUDE_DIR})
