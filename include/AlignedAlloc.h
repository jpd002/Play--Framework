#pragma once

#ifdef _MSC_VER
#include <malloc.h>
#else
#include <stdlib.h>
#endif

static void* framework_aligned_alloc(size_t allocSize, size_t alignment)
{
#if defined(_MSC_VER)
	return _aligned_malloc(allocSize, alignment);
#elif defined(__ANDROID__)
	void* result = nullptr;
	if(posix_memalign(&result, alignment, allocSize) != 0)
	{
		return nullptr;
	}
	return result;
#else
	return malloc(allocSize);
#endif
}

static void framework_aligned_free(void* ptr)
{
#if defined(_MSC_VER)
	_aligned_free(ptr);
#else
	free(ptr);
#endif
}
