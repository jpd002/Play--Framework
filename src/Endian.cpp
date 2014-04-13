#include "Endian.h"

#ifdef WIN32
#define LSB_FIRST
#endif

using namespace Framework;

uint32 CEndian::FromMSBF32(uint32 nValue)
{
	uint8* pValue = reinterpret_cast<uint8*>(&nValue);
	return (pValue[0] << 24) | (pValue[1] << 16) | (pValue[2] << 8) | (pValue[3]);
}
