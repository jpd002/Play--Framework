#pragma once

#include <cassert>

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

namespace Framework
{
	static constexpr bool IsPowerOfTwo(uint32 number)
	{
		uint32 complement = number - 1;
		return (number != 0) && ((number & complement) == 0);
	}

	//TODO: Replace with std::popcount when C++20 is available
	static constexpr uint32 PopCount(uint32 x)
	{
		/* 32-bit recursive reduction using SWAR...
		   but first step is mapping 2-bit values
		   into sum of 2 1-bit values in sneaky way
		*/
		x -= ((x >> 1) & 0x55555555);
		x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
		x = (((x >> 4) + x) & 0x0f0f0f0f);
		x += (x >> 8);
		x += (x >> 16);
		return (x & 0x0000003f);
	}

	static constexpr uint32 GetPowerOf2(uint32 x)
	{
		assert(IsPowerOfTwo(x));

		x |= (x >> 1);
		x |= (x >> 2);
		x |= (x >> 4);
		x |= (x >> 8);
		x |= (x >> 16);

		return PopCount(x >> 1);
	}
};
