cmake_minimum_required(VERSION 2.6)
project(Framework)

set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -Wno-warn-absolute-paths")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

set(BOOST_ROOT /Users/jpd002/Libraries/boost_1_55_0)
set(ZLIB_ROOT /Users/jpd002/Libraries/zlib-1.2.8)

include_directories(
	../include 
	${BOOST_ROOT}
	${ZLIB_ROOT}
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
	../src/PtrStream.cpp
	../src/Utf8.cpp
	../src/xml/Node.cpp 
	../src/xml/Parser.cpp
	../src/xml/Utils.cpp
	../src/xml/FilteringNodeIterator.cpp
	../src/xml/Writer.cpp
	../src/zip/ZipArchiveReader.cpp
	../src/zip/ZipInflateStream.cpp
	../src/zip/ZipStoreStream.cpp
)
