#pragma once

#ifdef _MSC_VER

#include <intrin.h>

static unsigned long bitmanip_clz(unsigned long value)
{
	unsigned long r = 0;
	_BitScanReverse(&r, value);
	return (31 - r);
}

#define __builtin_popcount __popcnt
#define __builtin_clz bitmanip_clz

#endif
