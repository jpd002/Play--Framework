cmake_minimum_required(VERSION 2.8)
project(Framework_OpenGl)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX OR WIN32 AND NOT ANDROID AND NOT APPLE)
	if (NOT TARGET glew_s)
		add_subdirectory(
			${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/glew-2.0.0
			${CMAKE_CURRENT_BINARY_DIR}/glew-2.0.0
		)
	endif()
	list(APPEND PROJECT_LIBS glew_s)
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
)

add_library(Framework_OpenGl ${SRC_FILES})
target_link_libraries(Framework_OpenGl PUBLIC Framework ${PROJECT_LIBS})
target_include_directories(Framework_OpenGl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
