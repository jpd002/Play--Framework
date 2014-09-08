LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE        := libFramework
LOCAL_SRC_FILES     := ../../src/Base64.cpp \
                       ../../src/BitStream.cpp \
                       ../../src/Stream.cpp \
                       ../../src/StdStream.cpp
LOCAL_C_INCLUDES    := $(LOCAL_PATH)/../../include
LOCAL_CFLAGS        += -fexceptions

include $(BUILD_STATIC_LIBRARY)
