#pragma once

#ifdef _WIN32
	#define FRAMEWORK_SIMD_USE_SSE
#elif defined(__APPLE__)
	#include <TargetConditionals.h>
	#if TARGET_CPU_X86_64
		#define FRAMEWORK_SIMD_USE_SSE
	#elif TARGET_CPU_ARM64
		#define FRAMEWORK_SIMD_USE_NEON
	#endif
#elif defined(__ANDROID__) || defined(__linux__) || defined(__FreeBSD__)
	#if defined(__x86_64__) || defined(__i386__)
		#define FRAMEWORK_SIMD_USE_SSE
	#elif defined(__aarch64__) || defined(__arm__)
		#define FRAMEWORK_SIMD_USE_NEON
	#endif
#elif defined(__EMSCRIPTEN__)
	#define FRAMEWORK_SIMD_USE_NEON
#endif

#if !defined(FRAMEWORK_SIMD_USE_SSE) && !defined(FRAMEWORK_SIMD_USE_NEON)
#error No SIMD instrinsics available for this platform.
#endif
