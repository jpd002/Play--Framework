#include <string.h>
#include <stdexcept>
#include "Base64.h"

using namespace Framework;

static const uint8 g_encodeLookupTable[64] =
{
	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
	0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76,
	0x77, 0x78, 0x79, 0x7A, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x2B, 0x2F
};

static const int g_decodeLookupTable[128] = 
{
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
	52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-1,-1,-1,
	-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
	15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
	-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
	41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1
};

std::string Framework::ToBase64(const std::string& source)
{
	return ToBase64(source.c_str(), source.size());
}

std::string Framework::ToBase64(const void* source, size_t sourceLength)
{
	std::string result;

	size_t paddedSourceLength = ((sourceLength + 2) / 3) * 3;
	for(unsigned int i = 0; i < paddedSourceLength; i += 3)
	{
		uint8 srcValues[3] = { 0, 0, 0 };
		for(unsigned int j = 0; j < 3; j++)
		{
			if(i + j >= sourceLength) continue;
			srcValues[j] = *(reinterpret_cast<const uint8*>(source) + i + j);
		}
		uint8 dstValues[4];
		dstValues[0] = (srcValues[0] & 0xFC) >> 2;
		dstValues[1] = ((srcValues[0] & 0x03) << 4) | ((srcValues[1] & 0xF0) >> 4);
		dstValues[2] = ((srcValues[1] & 0x0F) << 2) | ((srcValues[2] & 0xC0) >> 6);
		dstValues[3] = (srcValues[2] & 0x3F);

		dstValues[0] = g_encodeLookupTable[dstValues[0] & 0x3F];
		dstValues[1] = g_encodeLookupTable[dstValues[1] & 0x3F];
		dstValues[2] = ((i + 1) >= sourceLength) ? '=' : g_encodeLookupTable[dstValues[2] & 0x3F];
		dstValues[3] = ((i + 2) >= sourceLength) ? '=' : g_encodeLookupTable[dstValues[3] & 0x3F];

		result += dstValues[0];
		result += dstValues[1];
		result += dstValues[2];
		result += dstValues[3];
	}
	return result;
}

std::vector<uint8> Framework::FromBase64(const char* source)
{
	std::vector<uint8> result;

	size_t sourceLength = strlen(source);
	result.reserve(((sourceLength + 3) / 4) * 3);
	for(unsigned int i = 0; i < sourceLength; i += 4)
	{
		uint8 sourceValues[4] = { 0, 0, 0, 0 };
		unsigned int paddingCount = 0;
		for(unsigned int j = 0; j < 4; j++)
		{
			if(i + j >= sourceLength) continue;
			uint8 sourceChar = source[i + j];
			if(sourceChar >= 128)
			{
				throw std::runtime_error("Invalid base64 character.");
			}
			if(sourceChar == '=')
			{
				paddingCount++;
				continue;
			}
			int8 sourceValue = g_decodeLookupTable[sourceChar];
			if(sourceValue == static_cast<int8>(-1))
			{
				throw std::runtime_error("Invalid base64 character.");
			}
			sourceValues[j] = sourceValue;
		}
		uint8 dstValues[3];
		dstValues[0] = ((sourceValues[0] & 0x3F) << 2) | ((sourceValues[1] & 0x30) >> 4);
		dstValues[1] = ((sourceValues[1] & 0x0F) << 4) | ((sourceValues[2] & 0x3C) >> 2);
		dstValues[2] = ((sourceValues[2] & 0x03) << 6) | ((sourceValues[3] & 0x3F) >> 0);
		if(paddingCount <= 2) result.push_back(dstValues[0]);
		if(paddingCount <= 1) result.push_back(dstValues[1]);
		if(paddingCount <= 0) result.push_back(dstValues[2]);
	}

	return result;
}
