cmake_minimum_required(VERSION 2.8)
project(Framework_OpenGl)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)

include(Header)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(TARGET_PLATFORM_ANDROID OR TARGET_PLATFORM_IOS OR TARGET_PLATFORM_UNIX_AARCH64)
	set(USE_GLES ON CACHE BOOL "Use GLES")
else()
	set(USE_GLES OFF CACHE BOOL "Use GLES")
endif()

set(USE_GLEW OFF)
if(NOT USE_GLES AND NOT APPLE)
	if (NOT TARGET glew_s)
		add_subdirectory(
			${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/glew-2.0.0
			${CMAKE_CURRENT_BINARY_DIR}/glew-2.0.0
		)
	endif()
	list(APPEND PROJECT_LIBS glew_s)
	set(USE_GLEW ON)
endif()

if (NOT TARGET Framework)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../Framework
		${CMAKE_CURRENT_BINARY_DIR}/Framework
	)
endif()
set(SRC_FILES
	../../src/opengl/Program.cpp
	../../src/opengl/Shader.cpp
	../../include/opengl/OpenGlDef.h
	../../include/opengl/Program.h
	../../include/opengl/Resource.h
	../../include/opengl/Shader.h
)

add_library(Framework_OpenGl ${SRC_FILES})
target_link_libraries(Framework_OpenGl PUBLIC Framework ${PROJECT_LIBS})
target_include_directories(Framework_OpenGl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

if(USE_GLES)
	target_compile_definitions(Framework_OpenGl PUBLIC GLES_COMPATIBILITY)
endif()
if(USE_GLEW)
	target_compile_definitions(Framework_OpenGl PUBLIC USE_GLEW)
endif()
