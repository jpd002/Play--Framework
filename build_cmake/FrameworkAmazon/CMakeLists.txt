cmake_minimum_required(VERSION 2.8)
project(Framework_Amazon)

include(../Framework_Common.cmake)

if(NOT TARGET Framework_Http)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../FrameworkHttp
		${CMAKE_CURRENT_BINARY_DIR}/FrameworkHttp
	)
endif()

set(SRC_FILES
	../../src/amazon/AmazonClient.cpp
	../../include/amazon/AmazonClient.h
)

add_library(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC Framework_Http)
