LOCAL_PATH:= $(call my-dir)

include $(LOCAL_PATH)/ExternalDependencies.mk

include $(CLEAR_VARS)

LOCAL_MODULE		:= libFramework
LOCAL_SRC_FILES		:= 	../../src/Base64.cpp \
						../../src/bitmap/Bitmap.cpp \
						../../src/bitmap/BMP.cpp \
						../../src/bitmap/JPEG.cpp \
						../../src/bitmap/PNG.cpp \
						../../src/bitmap/TGA.cpp \
						../../src/BitStream.cpp \
						../../src/Endian.cpp \
						../../src/idct/IEEE1180.cpp \
						../../src/layout/FlatLayout.cpp \
						../../src/layout/GridLayout.cpp \
						../../src/layout/HorizontalLayout.cpp \
						../../src/layout/LayoutBase.cpp \
						../../src/layout/LayoutBaseItem.cpp \
						../../src/layout/LayoutObject.cpp \
						../../src/layout/LayoutStretch.cpp \
						../../src/layout/VerticalLayout.cpp \
						../../src/MemStream.cpp \
						../../src/PtrStream.cpp \
						../../src/Stream.cpp \
						../../src/StreamBitStream.cpp \
						../../src/StdStream.cpp \
						../../src/Utf8.cpp \
						../../src/xml/FilteringNodeIterator.cpp \
						../../src/xml/Node.cpp \
						../../src/xml/Parser.cpp \
						../../src/xml/Utils.cpp \
						../../src/xml/Writer.cpp
LOCAL_C_INCLUDES		:= $(BOOST_PATH) $(LOCAL_PATH)/../../include
LOCAL_CPP_FEATURES		:= exceptions rtti

include $(BUILD_STATIC_LIBRARY)
