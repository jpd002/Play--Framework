#pragma once

#ifdef _MSC_VER

#include "Types.h"
#include <intrin.h>

static inline int bitmanip_clz(uint32 value)
{
	unsigned long r = 0;
	_BitScanReverse(&r, value);
	return (31 - r);
}

static inline int bitmanip_ctz(uint32 value)
{
	unsigned long r = 0;
	_BitScanForward(&r, value);
	return r;
}

static inline int bitmanip_ctzll(uint64 value)
{
#if defined(_M_X64)
	unsigned long r = 0;
	_BitScanForward64(&r, value);
	return r;
#elif defined(_M_IX86)
	unsigned long r = 0;
	if(_BitScanForward(&r, static_cast<uint32>(value)))
	{
		return r;
	}
	_BitScanForward(&r, static_cast<uint32>(value >> 32));
	return r + 32;
#else
#error "Unsupported architecture."
#endif
}

#define __builtin_popcount __popcnt
#define __builtin_clz bitmanip_clz
#define __builtin_ctz bitmanip_ctz
#define __builtin_ctzll bitmanip_ctzll

#endif
