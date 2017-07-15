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

include_directories(../../include)

set(SRC_FILES
	../../src/http/HttpClient.cpp
	../../src/http/HttpClientFactory.cpp
	../../src/http/Win32HttpClient.cpp
)

set(HEADER_FILES
	../../include/http/HttpClient.h
	../../include/http/HttpClientFactory.h
	../../include/http/Win32HttpClient.h
)

add_library(Framework_Http ${SRC_FILES} ${HEADER_FILES})
