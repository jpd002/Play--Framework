#pragma once

#include "Types.h"
#ifdef _MSC_VER
#include <stdlib.h>
#define __builtin_bswap16(a) _byteswap_ushort(a)
#define __builtin_bswap32(a) _byteswap_ulong(a)
#define __builtin_bswap64(a) _byteswap_uint64(a)
#endif

namespace Framework
{
	class CEndian
	{
	public:
		template <typename IntType>
		static void FromMSBF(IntType&);

		static uint16 FromMSBF16(uint16 value)
		{
			return __builtin_bswap16(value);
		}

		static uint32 FromMSBF32(uint32 value)
		{
			return __builtin_bswap32(value);
		}

		static uint64 FromMSBF64(uint64 value)
		{
			return __builtin_bswap64(value);
		}

		static uint64 ToMSBF64(uint64 value)
		{
			return __builtin_bswap64(value);
		}
	};

	template <>
	inline void CEndian::FromMSBF(uint16& value)
	{
		value = FromMSBF16(value);
	}

	template <>
	inline void CEndian::FromMSBF(uint32& value)
	{
		value = FromMSBF32(value);
	}

	template <>
	inline void CEndian::FromMSBF(uint64& value)
	{
		value = FromMSBF64(value);
	}
}
