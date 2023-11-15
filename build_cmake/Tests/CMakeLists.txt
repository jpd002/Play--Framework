project(FrameworkTests)

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
	../../tests/TestDefs.h
	../../tests/XmlTest.cpp
	../../tests/XmlTest.h
)

if(NOT TARGET Framework)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../Framework
		${CMAKE_CURRENT_BINARY_DIR}/Framework
	)
endif()

enable_testing()
add_executable(FrameworkTests ${tests_srcs})
target_link_libraries(FrameworkTests Framework)
add_test(FrameworkTests FrameworkTests)
