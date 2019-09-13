cmake_minimum_required(VERSION 2.8)
project(Framework_Vulkan)

include(../Framework_Common.cmake)

find_package(Vulkan REQUIRED)

set(SRC_FILES
	../../src/vulkan/CommandBufferPool.cpp
	../../src/vulkan/Device.cpp
	../../src/vulkan/Instance.cpp
	../../src/vulkan/Loader.cpp
	../../src/vulkan/ShaderModule.cpp
	
	../../include/vulkan/CommandBufferPool.h
	../../include/vulkan/Device.h
	../../include/vulkan/Instance.h
	../../include/vulkan/Loader.h
	../../include/vulkan/ShaderModule.h
	../../include/vulkan/VulkanDef.h
)

add_library(Framework_Vulkan ${SRC_FILES})
target_include_directories(Framework_Vulkan PUBLIC ${FRAMEWORK_INCLUDE_DIR} ${Vulkan_INCLUDE_DIR})
