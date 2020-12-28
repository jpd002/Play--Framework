#pragma once

#ifdef _MSC_VER

#include "Types.h"
#include <intrin.h>

static int bitmanip_clz(uint32 value)
{
	unsigned long r = 0;
	_BitScanReverse(&r, value);
	return (31 - r);
}

static int bitmanip_ctz(uint32 value)
{
	unsigned long r = 0;
	_BitScanForward(&r, value);
	return r;
}

#define __builtin_popcount __popcnt
#define __builtin_clz bitmanip_clz
#define __builtin_ctz bitmanip_ctz

#endif
