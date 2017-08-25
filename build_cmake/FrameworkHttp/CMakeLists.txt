cmake_minimum_required(VERSION 2.8)
project(Framework_Http)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++")
endif(APPLE)

include_directories(../../include)

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
elseif(APPLE)
	set(PLATFORM_SRC_FILES
		../../src/http/AppleHttpClient.cpp
		../../include/http/AppleHttpClient.h
	)
endif()

add_library(Framework_Http ${SRC_FILES} ${PLATFORM_SRC_FILES})
