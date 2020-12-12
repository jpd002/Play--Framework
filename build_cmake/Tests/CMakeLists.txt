cmake_minimum_required(VERSION 3.0)
project(Tests)

include(../Framework_Common.cmake)

set(tests_srcs
	../../tests/BmpTest.cpp
	../../tests/BmpTest.h
	../../tests/Main.cpp
	../../tests/MathStringUtilsTest.cpp
	../../tests/MathStringUtilsTest.h
	../../tests/SignalTest.cpp
	../../tests/SignalTest.h
	../../tests/StringCastTest.cpp
	../../tests/StringCastTest.h
	../../tests/StringUtilsTest.cpp
	../../tests/StringUtilsTest.h
)

if(NOT TARGET Framework)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../Framework
		${CMAKE_CURRENT_BINARY_DIR}/Framework
	)
endif()

add_executable(Tests ${tests_srcs})
target_link_libraries(Tests Framework)
