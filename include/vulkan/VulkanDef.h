#pragma once

#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif

#if defined(__ANDROID__)
#ifndef VK_USE_PLATFORM_ANDROID_KHR
#define VK_USE_PLATFORM_ANDROID_KHR
#endif
#endif

#if defined(__linux__)
#ifndef VK_USE_PLATFORM_XCB_KHR
#define VK_USE_PLATFORM_XCB_KHR
#endif
#endif

#include <vulkan/vulkan.h>

#include <cassert>

#ifdef _DEBUG
#define CHECKVULKANERROR(errorCode) { assert(errorCode == VK_SUCCESS); }
#else
#define CHECKVULKANERROR(errorCode)
#endif
