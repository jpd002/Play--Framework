cmake_minimum_required(VERSION 2.8)
project(Framework_OpenAl)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../../include)

set(SRC_FILES
	../../src/openal/Buffer.cpp
	../../src/openal/Context.cpp
	../../src/openal/Device.cpp
	../../src/openal/Source.cpp
)

add_library(Framework_OpenAl ${SRC_FILES})
