cmake_minimum_required(VERSION 2.6)
project(Framework)

set (CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

include_directories(../include /usr/local/include)

add_library(Framework 
	../src/Base64.cpp
	../src/Stream.cpp 
	../src/StdStream.cpp 
	../src/MemStream.cpp
	../src/PathUtils.cpp
	../src/xml/Node.cpp 
	../src/xml/Parser.cpp
	../src/xml/Utils.cpp
	../src/xml/FilteringNodeIterator.cpp
)

