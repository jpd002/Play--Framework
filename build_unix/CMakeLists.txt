cmake_minimum_required(VERSION 2.6)
project(Framework)

set (CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

include_directories(../include /usr/local/include /usr/local/include/c++/v1 /usr/local/include/mysql)

add_library(Framework 
	../src/Base64.cpp
	../src/Config.cpp
	../src/Endian.cpp
	../src/Stream.cpp 
	../src/StdStream.cpp 
	../src/MemStream.cpp
	../src/PathUtils.cpp
	../src/xml/Node.cpp 
	../src/xml/Parser.cpp
	../src/xml/Utils.cpp
	../src/xml/FilteringNodeIterator.cpp
	../src/xml/Writer.cpp
)

add_library(Framework_MySql
	../src/mysql/Client.cpp
	../src/mysql/Result.cpp
	../src/mysql/AccessInfo.cpp
)

