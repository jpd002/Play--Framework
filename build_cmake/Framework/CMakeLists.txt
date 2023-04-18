cmake_minimum_required(VERSION 3.1)
project(Framework)

include(../Framework_Common.cmake)

if(NOT TARGET libzstd_zlibwrapper_static)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/build_cmake/zstd_zlibwrapper
		${CMAKE_CURRENT_BINARY_DIR}/zstd_zlibwrapper
	)
endif()
LIST(APPEND PROJECT_LIBS libzstd_zlibwrapper_static)

if(NOT TARGET ghc_filesystem)
	add_subdirectory(
		${CMAKE_CURRENT_SOURCE_DIR}/../../../Dependencies/ghc_filesystem
		${CMAKE_CURRENT_BINARY_DIR}/ghc_filesystem
	)
endif()
LIST(APPEND PROJECT_LIBS ghc_filesystem)

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
	../../src/FilesystemUtils.cpp
	../../src/HashUtils.cpp
	../../src/idct/IEEE1180.cpp
	../../src/idct/TrivialC.cpp
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
	../../src/StringUtils.cpp
	../../src/string_cast.cpp
	../../src/string_cast_sjis.cpp
	../../src/string_cast_win1252.cpp
	../../src/StdStream.cpp
	../../src/ThreadPool.cpp
	../../src/ThreadUtils.cpp
	../../src/Url.cpp
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

	../../include/BitManip.h
	../../include/Csv.h
	../../include/EndianUtils.h
	../../include/filesystem_def.h
	../../include/FilesystemUtils.h
	../../include/HashUtils.h
	../../include/layout/FlatLayout.h
	../../include/layout/GridLayout.h
	../../include/layout/HorizontalLayout.h
	../../include/layout/LayoutBase.h
	../../include/layout/LayoutBaseItem.h
	../../include/layout/LayoutObject.h
	../../include/layout/LayoutStretch.h
	../../include/layout/VerticalLayout.h
	../../include/maybe_unused.h
	../../include/nodiscard.h
	../../include/signal/Signal.h
	../../include/Singleton.h
	../../include/StringUtils.h
	../../include/std_experimental_map.h
	../../include/std_experimental_set.h
	../../include/ThreadPool.h
	../../include/ThreadUtils.h
	../../include/Url.h
	../../include/Utf8.h
	../../include/zip/ZipArchiveReader.h
	../../include/zip/ZipArchiveWriter.h
	../../include/zip/ZipDeflateStream.h
	../../include/zip/ZipFile.h
	../../include/zip/ZipInflateStream.h
	../../include/zip/ZipStoreStream.h
)

if(ANDROID)
	set(PLATFORM_SRC_FILES
		../../src/android/android_content_ContentResolver.cpp
		../../src/android/android_database_Cursor.cpp
		../../src/android/android_net_Uri.cpp
		../../src/android/android_os_ParcelFileDescriptor.cpp
		../../src/android/AssetStream.cpp
		../../src/android/AssetManager.cpp
		../../src/android/ContentResolver.cpp
		../../src/android/ContentStream.cpp
		../../src/android/ContentUtils.cpp
		../../src/android/java_security_MessageDigest.cpp
		../../src/android/JavaObject.cpp
		../../src/android/JavaVM.cpp
		../../src/android/javax_crypto_Mac.cpp
		../../src/android/javax_crypto_spec_SecretKeySpec.cpp
		../../src/PosixFileStream.cpp
		
		../../include/android/android_content_ContentResolver.h
		../../include/android/android_database_Cursor.h
		../../include/android/android_net_Uri.h
		../../include/android/android_os_ParcelFileDescriptor.h
		../../include/android/AssetStream.h
		../../include/android/AssetManager.h
		../../include/android/ContentResolver.h
		../../include/android/ContentStream.h
		../../include/android/ContentUtils.h
		../../include/android/java_security_MessageDigest.h
		../../include/android/JavaObject.h
		../../include/android/JavaVM.h
		../../include/android/javax_crypto_Mac.h
		../../include/android/javax_crypto_spec_SecretKeySpec.h
		../../include/PosixFileStream.h
	)
endif()

add_library(Framework ${COMMON_SRC_FILES} ${PLATFORM_SRC_FILES})
target_link_libraries(Framework PUBLIC ${PROJECT_LIBS} PRIVATE ${PRIVATE_PROJECT_LIBS})
target_include_directories(Framework PUBLIC ${FRAMEWORK_INCLUDE_DIR} ${PROJECT_INCLUDES})
