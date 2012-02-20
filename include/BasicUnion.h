#ifndef _BASICUNION_H_
#define _BASICUNION_H_

#include "Types.h"

template <typename FullType, typename HalfType>
struct basic_union
{
	static_assert(sizeof(FullType) == (2 * sizeof(HalfType)), "Full type size isn't twice of half type size.");

	basic_union() {}
	basic_union(const FullType& f) : f(f) {}
	basic_union(const HalfType& h0, const HalfType& h1) : h0(h0), h1(h1) {}

	union
	{
		struct
		{
			HalfType h0;
			HalfType h1;
		};
		FullType f;
	};
};

typedef basic_union<uint32, uint16> UNION32_16;
typedef basic_union<uint64, uint32> UNION64_32;
typedef basic_union<uint64, UNION32_16> UNION64_32_16;

#endif
