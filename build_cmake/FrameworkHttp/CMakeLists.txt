cmake_minimum_required(VERSION 2.8)
project(Framework_Http)

include(../Framework_Common.cmake)

if(NOT TARGET Framework)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../Framework
		${CMAKE_CURRENT_BINARY_DIR}/Framework
	)
endif()

set(SRC_FILES
	../../src/http/HttpClient.cpp
	../../include/http/HttpClient.h
	../../src/http/HttpClientFactory.cpp
	../../include/http/HttpClientFactory.h
)

if(ANDROID)
	set(PLATFORM_SRC_FILES
		../../src/http/AndroidHttpClient.cpp
		../../include/http/AndroidHttpClient.h
		../../src/http/java_io_InputStream.cpp
		../../include/http/java_io_InputStream.h
		../../src/http/java_io_OutputStream.cpp
		../../include/http/java_io_OutputStream.h
		../../src/http/java_net_HttpURLConnection.cpp
		../../include/http/java_net_HttpURLConnection.h
		../../src/http/java_net_URL.cpp
		../../include/http/java_net_URL.h
	)
elseif(WIN32)
	set(PLATFORM_SRC_FILES
		../../src/http/Win32HttpClient.cpp
		../../include/http/Win32HttpClient.h
	)
	list(APPEND PROJECT_LIBS wininet)
elseif(APPLE)
	set(PLATFORM_SRC_FILES
		../../src/http/AppleHttpClient.cpp
		../../include/http/AppleHttpClient.h
	)
else()
	find_package(CURL REQUIRED)
	if(CURL_FOUND)
		include_directories(${CURL_INCLUDE_DIRS})
		
		set(PLATFORM_SRC_FILES
			../../src/http/CurlHttpClient.cpp
			../../include/http/CurlHttpClient.h
		)
		
		add_definitions(-DHAS_CURL)
		set(PROJECT_LIBS ${CURL_LIBRARIES})
	endif()
endif()

add_library(Framework_Http ${SRC_FILES} ${PLATFORM_SRC_FILES})
target_link_libraries(Framework_Http PUBLIC Framework ${PROJECT_LIBS})
target_include_directories(Framework_Http PUBLIC ${FRAMEWORK_INCLUDE_DIR})
