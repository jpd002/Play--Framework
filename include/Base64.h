#pragma once

#include "Types.h"
#include <vector>
#include <string>

namespace Framework
{
	std::string ToBase64(const std::string&);
	std::string ToBase64(const void* buffer, size_t size);
	std::vector<uint8> FromBase64(const char* source);
}
