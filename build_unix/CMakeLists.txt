cmake_minimum_required(VERSION 2.8)
project(Framework)

set(CMAKE_MODULE_PATH
	${Framework_SOURCE_DIR}/Modules
	${CMAKE_MODULE_PATH}
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../include)

set(Boost_FIND_REQUIRED TRUE)
find_package(Boost COMPONENTS system filesystem chrono)
include_directories(${Boost_INCLUDE_DIRS})

find_package(MYSQL REQUIRED)
include_directories(${MYSQL_INCLUDE_DIR})

add_library(Framework
	../src/Base64.cpp
	../src/bitmap/Bitmap.cpp
	../src/bitmap/BMP.cpp
	../src/bitmap/JPEG.cpp
	../src/bitmap/PNG.cpp
	../src/bitmap/TGA.cpp
	../src/BitStream.cpp
	../src/Config.cpp
	../src/Endian.cpp
	../src/idct/IEEE1180.cpp
	../src/layout/FlatLayout.cpp
	../src/layout/GridLayout.cpp
	../src/layout/HorizontalLayout.cpp
	../src/layout/LayoutBase.cpp
	../src/layout/LayoutBaseItem.cpp
	../src/layout/LayoutObject.cpp
	../src/layout/LayoutStretch.cpp
	../src/layout/VerticalLayout.cpp
	../src/math/MathStringUtils.cpp
	../src/MemStream.cpp
	../src/mpeg2/CodedBlockPatternTable.cpp
	../src/mpeg2/DcSizeChrominanceTable.cpp
	../src/mpeg2/DcSizeLuminanceTable.cpp
	../src/mpeg2/DctCoefficientTable.cpp
	../src/mpeg2/DctCoefficientTable0.cpp
	../src/mpeg2/DctCoefficientTable1.cpp
	../src/mpeg2/InverseScanTable.cpp
	../src/mpeg2/MacroblockAddressIncrementTable.cpp
	../src/mpeg2/MacroblockTypeBTable.cpp
	../src/mpeg2/MacroblockTypeITable.cpp
	../src/mpeg2/MacroblockTypePTable.cpp
	../src/mpeg2/MotionCodeTable.cpp
	../src/mpeg2/QuantiserScaleTable.cpp
	../src/mpeg2/VLCTable.cpp
	../src/opengl/Program.cpp
	../src/opengl/Shader.cpp
	../src/PathUtils.cpp
	../src/PtrStream.cpp
	../src/Stream.cpp
	../src/StreamBitStream.cpp
	../src/StdStream.cpp
	../src/StdStreamUtils.cpp
	../src/Utf8.cpp
	../src/xml/FilteringNodeIterator.cpp
	../src/xml/Node.cpp
	../src/xml/Parser.cpp
	../src/xml/Utils.cpp
	../src/xml/Writer.cpp
	../src/zip/ZipArchiveReader.cpp
	../src/zip/ZipArchiveWriter.cpp
	../src/zip/ZipDeflateStream.cpp
	../src/zip/ZipFile.cpp
	../src/zip/ZipInflateStream.cpp
	../src/zip/ZipStoreStream.cpp
)

add_library(Framework_MySql
	../src/mysql/Client.cpp
	../src/mysql/Result.cpp
	../src/mysql/AccessInfo.cpp
)
