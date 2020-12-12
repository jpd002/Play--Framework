cmake_minimum_required(VERSION 3.0)
project(Framework_OpenAl)

include(../Framework_Common.cmake)

find_package(OpenAL REQUIRED)

set(SRC_FILES
	../../src/openal/Buffer.cpp
	../../src/openal/Context.cpp
	../../src/openal/Device.cpp
	../../src/openal/Source.cpp
)

add_library(Framework_OpenAl ${SRC_FILES})
target_link_libraries(Framework_OpenAl PUBLIC ${OPENAL_LIBRARY})
target_include_directories(Framework_OpenAl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include ${OPENAL_INCLUDE_DIR})
