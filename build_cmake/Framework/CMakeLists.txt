cmake_minimum_required(VERSION 2.8)
project(Framework)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/cmake-modules
	${CMAKE_MODULE_PATH}
)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the type of build, options are: None Debug Release"
		FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++")
endif(APPLE)

find_package(ZLIB)
if(ZLIB_FOUND)
	include_directories(${ZLIB_INCLUDE_DIRS})
else()
	MESSAGE("-- Using Provided zlib source")
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/zlib-1.2.8)
endif(ZLIB_FOUND)

find_package(ICUUC)
if(ICUUC_FOUND)
	include_directories(${ICUUC_INCLUDE_DIRS})
	add_definitions(-DHAS_ICU)
endif()

if (NOT TARGET Boost::boost)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/boost-cmake
		${CMAKE_CURRENT_BINARY_DIR}/boost-cmake
	)
endif()

if (WIN32)
	add_definitions(-D_UNICODE -DUNICODE)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-D_LIB)
endif (WIN32)

include_directories(../../include)

set(COMMON_SRC_FILES
	../../src/Base64.cpp
	../../src/bitmap/Bitmap.cpp
	../../src/bitmap/BMP.cpp
	../../src/bitmap/JPEG.cpp
	../../src/bitmap/PNG.cpp
	../../src/bitmap/TGA.cpp
	../../src/BitStream.cpp
	../../src/Config.cpp
	../../src/Endian.cpp
	../../src/idct/IEEE1180.cpp
	../../src/layout/FlatLayout.cpp
	../../src/layout/GridLayout.cpp
	../../src/layout/HorizontalLayout.cpp
	../../src/layout/LayoutBase.cpp
	../../src/layout/LayoutBaseItem.cpp
	../../src/layout/LayoutObject.cpp
	../../src/layout/LayoutStretch.cpp
	../../src/layout/VerticalLayout.cpp
	../../src/LzAri.cpp
	../../src/math/MathStringUtils.cpp
	../../src/MemStream.cpp
	../../src/mpeg2/CodedBlockPatternTable.cpp
	../../src/mpeg2/DcSizeChrominanceTable.cpp
	../../src/mpeg2/DcSizeLuminanceTable.cpp
	../../src/mpeg2/DctCoefficientTable.cpp
	../../src/mpeg2/DctCoefficientTable0.cpp
	../../src/mpeg2/DctCoefficientTable1.cpp
	../../src/mpeg2/InverseScanTable.cpp
	../../src/mpeg2/MacroblockAddressIncrementTable.cpp
	../../src/mpeg2/MacroblockTypeBTable.cpp
	../../src/mpeg2/MacroblockTypeITable.cpp
	../../src/mpeg2/MacroblockTypePTable.cpp
	../../src/mpeg2/MotionCodeTable.cpp
	../../src/mpeg2/QuantiserScaleTable.cpp
	../../src/mpeg2/VLCTable.cpp
	../../src/PathUtils.cpp
	../../src/PtrStream.cpp
	../../src/Stream.cpp
	../../src/StreamBitStream.cpp
	../../src/string_cast.cpp
	../../src/string_cast_sjis.cpp
	../../src/StdStream.cpp
	../../src/StdStreamUtils.cpp
	../../src/Utf8.cpp
	../../src/xml/FilteringNodeIterator.cpp
	../../src/xml/Node.cpp
	../../src/xml/Parser.cpp
	../../src/xml/Utils.cpp
	../../src/xml/Writer.cpp
	../../src/zip/ZipArchiveReader.cpp
	../../src/zip/ZipArchiveWriter.cpp
	../../src/zip/ZipDeflateStream.cpp
	../../src/zip/ZipFile.cpp
	../../src/zip/ZipInflateStream.cpp
	../../src/zip/ZipStoreStream.cpp
)

if(ANDROID)
	set(PLATFORM_SPECIFIC_SRC_FILES
		../../src/android/AssetStream.cpp
		../../src/android/AssetManager.cpp
		../../src/android/JavaObject.cpp
		../../src/android/JavaVM.cpp
		../../src/PosixFileStream.cpp
	)
endif()

add_library(Framework ${COMMON_SRC_FILES} ${PLATFORM_SPECIFIC_SRC_FILES})
target_link_libraries(Framework PUBLIC Boost::boost)
