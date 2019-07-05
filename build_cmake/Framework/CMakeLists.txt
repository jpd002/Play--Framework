cmake_minimum_required(VERSION 3.1)
project(Framework)

include(../Framework_Common.cmake)

find_package(ZLIB)
if(NOT ZLIB_FOUND)
	MESSAGE("-- Using Provided zlib source")
	if(NOT TARGET zlibstatic)
		add_subdirectory(
			${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/build_cmake/zlib-1.2.8
			${CMAKE_CURRENT_BINARY_DIR}/zlib-1.2.8
		)
	endif()
endif(NOT ZLIB_FOUND)
LIST(APPEND PROJECT_LIBS ZLIB::ZLIB)

find_package(ICUUC)
if(ICUUC_FOUND)
	LIST(APPEND PROJECT_INCLUDES ${ICUUC_INCLUDE_DIRS})
	LIST(APPEND PROJECT_LIBS ${ICUUC_LIBRARIES})
	add_definitions(-DHAS_ICU)
endif()

find_package(OpenSSL)
if(OPENSSL_FOUND)
	LIST(APPEND PROJECT_INCLUDES ${OPENSSL_INCLUDE_DIR})
	LIST(APPEND PROJECT_LIBS ${OPENSSL_LIBRARIES})
	add_definitions(-DHAS_OPENSSL)
endif()

if(NOT TARGET Boost::boost)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/boost-cmake
		${CMAKE_CURRENT_BINARY_DIR}/boost-cmake
	)
endif()

if(APPLE)
	LIST(APPEND PRIVATE_PROJECT_LIBS "-framework Foundation")
endif()

set(COMMON_SRC_FILES
	../../src/Base64.cpp
	../../src/bitmap/Bitmap.cpp
	../../src/bitmap/BMP.cpp
	../../src/bitmap/JPEG.cpp
	../../src/bitmap/PNG.cpp
	../../src/bitmap/TGA.cpp
	../../src/BitStream.cpp
	../../src/Config.cpp
	../../src/Csv.cpp
	../../include/Csv.h
	../../src/Endian.cpp
	../../src/HashUtils.cpp
	../../include/HashUtils.h
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
	../../include/maybe_unused.h
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
	../../src/StringUtils.cpp
	../../include/StringUtils.h
	../../src/string_cast.cpp
	../../src/string_cast_sjis.cpp
	../../src/string_cast_win1252.cpp
	../../include/std_experimental_map.h
	../../src/StdStream.cpp
	../../src/StdStreamUtils.cpp
	../../src/ThreadPool.cpp
	../../include/ThreadPool.h
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
	set(PLATFORM_SRC_FILES
		../../src/android/AssetStream.cpp
		../../src/android/AssetManager.cpp
		../../src/android/JavaObject.cpp
		../../src/android/JavaVM.cpp
		../../src/PosixFileStream.cpp
	)
endif()

add_library(Framework ${COMMON_SRC_FILES} ${PLATFORM_SRC_FILES})
target_link_libraries(Framework PUBLIC Boost::boost Boost::filesystem ${PROJECT_LIBS} PRIVATE ${PRIVATE_PROJECT_LIBS})
target_include_directories(Framework PUBLIC ${FRAMEWORK_INCLUDE_DIR} ${PROJECT_INCLUDES})
