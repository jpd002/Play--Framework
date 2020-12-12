cmake_minimum_required(VERSION 3.0)
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
	../../src/amazon/AmazonS3Client.cpp
	../../include/amazon/AmazonClient.h
	../../include/amazon/AmazonS3Client.h
)

add_library(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC Framework_Http)
