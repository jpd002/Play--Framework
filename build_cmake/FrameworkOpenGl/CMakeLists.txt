cmake_minimum_required(VERSION 2.8)
project(Framework_OpenGl)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX OR WIN32 AND NOT ANDROID AND NOT APPLE)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/glew-2.0.0/include)
endif()

include_directories(../../include)

set(SRC_FILES
	../../src/opengl/Program.cpp
	../../src/opengl/Shader.cpp
)

add_library(Framework_OpenGl ${SRC_FILES})
