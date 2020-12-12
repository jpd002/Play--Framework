cmake_minimum_required(VERSION 3.0)
project(Framework_Vulkan)

include(Header)
include(../Framework_Common.cmake)

find_package(Vulkan REQUIRED)

if(NOT TARGET Framework)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../Framework
		${CMAKE_CURRENT_BINARY_DIR}/Framework
	)
endif()
list(APPEND FRAMEWORK_VULKAN_LIBS Framework)

set(SRC_FILES
	../../src/vulkan/CommandBufferPool.cpp
	../../src/vulkan/Buffer.cpp
	../../src/vulkan/Device.cpp
	../../src/vulkan/Image.cpp
	../../src/vulkan/Instance.cpp
	../../src/vulkan/Loader.cpp
	../../src/vulkan/ShaderModule.cpp
	../../src/vulkan/Utils.cpp
	
	../../include/vulkan/CommandBufferPool.h
	../../include/vulkan/Buffer.h
	../../include/vulkan/Device.h
	../../include/vulkan/Image.h
	../../include/vulkan/Instance.h
	../../include/vulkan/Loader.h
	../../include/vulkan/ShaderModule.h
	../../include/vulkan/StructDefs.h
	../../include/vulkan/Utils.h
	../../include/vulkan/VulkanDef.h
)

if(TARGET_PLATFORM_UNIX)
	list(APPEND FRAMEWORK_VULKAN_LIBS dl)
endif()

add_library(Framework_Vulkan ${SRC_FILES})
target_include_directories(Framework_Vulkan PUBLIC ${FRAMEWORK_INCLUDE_DIR} ${Vulkan_INCLUDE_DIR})
target_link_libraries(Framework_Vulkan PUBLIC ${FRAMEWORK_VULKAN_LIBS})
