#pragma once

#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif

#if defined(__ANDROID__)

	#ifndef VK_USE_PLATFORM_ANDROID_KHR
	#define VK_USE_PLATFORM_ANDROID_KHR
	#endif

#elif defined(__linux__)

	#ifndef VK_USE_PLATFORM_XCB_KHR
	#define VK_USE_PLATFORM_XCB_KHR
	#endif

#elif defined(_WIN32)

	#ifndef VK_USE_PLATFORM_WIN32_KHR
	#define VK_USE_PLATFORM_WIN32_KHR
	#endif

#elif defined(__APPLE__)

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE

	#ifndef VK_USE_PLATFORM_IOS_MVK
	#define VK_USE_PLATFORM_IOS_MVK
	#endif

#else

	#ifndef VK_USE_PLATFORM_MACOS_MVK
	#define VK_USE_PLATFORM_MACOS_MVK
	#endif

#endif
#endif

#include <vulkan/vulkan.h>

#include <cassert>

#ifdef _DEBUG
#define CHECKVULKANERROR(errorCode) { assert(errorCode == VK_SUCCESS); }
#else
#define CHECKVULKANERROR(errorCode)
#endif
