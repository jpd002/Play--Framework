#ifndef _ENDIAN_H_
#define _ENDIAN_H_

#include "Types.h"

namespace Framework
{
	class CEndian
	{
	public:
		static uint32		FromMSBF32(uint32);
		static uint32		FromLSBF32(uint32);
	};
}

#endif
