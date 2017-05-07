cmake_minimum_required(VERSION 2.8)
project(Framework_Vulkan)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)

include_directories(../../include ${VULKAN_INCLUDE_DIR})

set(SRC_FILES
	../../src/vulkan/CommandBufferPool.cpp
	../../src/vulkan/Device.cpp
	../../src/vulkan/Instance.cpp
	../../src/vulkan/Loader.cpp
	../../src/vulkan/ShaderModule.cpp
)

add_library(Framework_Vulkan ${SRC_FILES})
