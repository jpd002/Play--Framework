#pragma once

#include "Types.h"
#include <array>

namespace Framework
{
	namespace HashUtils
	{
		std::array<uint8, 0x20> ComputeSha256(const void*, size_t);
		std::array<uint8, 0x20> ComputeHmacSha256(const void*, size_t, const void*, size_t);
	};
}
