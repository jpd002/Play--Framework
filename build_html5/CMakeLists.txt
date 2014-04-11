cmake_minimum_required(VERSION 2.6)
project(Framework)

set (CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -Wno-warn-absolute-paths")

include_directories(
	../include 
	/usr/local/include 
	/usr/local/include/c++/v1 
	/usr/local/include/mysql 
	/Users/jpd002/Libraries/boost_1_55_0
)

add_library(Framework 
	../src/Base64.cpp
	../src/BitStream.cpp
	../src/bitmap/Bitmap.cpp
	../src/bitmap/BMP.cpp
	../src/bitmap/JPEG.cpp
	../src/bitmap/PNG.cpp
	../src/bitmap/TGA.cpp
	../src/Config.cpp
	../src/Endian.cpp
	../src/idct/IEEE1180.cpp
	../src/Stream.cpp
	../src/StreamBitStream.cpp
	../src/StdStream.cpp 
	../src/MemStream.cpp
	../src/PathUtils.cpp
	../src/Utf8.cpp
	../src/xml/Node.cpp 
	../src/xml/Parser.cpp
	../src/xml/Utils.cpp
	../src/xml/FilteringNodeIterator.cpp
	../src/xml/Writer.cpp
)

# add_library(Framework_MySql
# 	../src/mysql/Client.cpp
# 	../src/mysql/Result.cpp
# 	../src/mysql/AccessInfo.cpp
# )
