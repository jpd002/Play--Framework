#ifndef _IDCT_INTERFACE_H_
#define _IDCT_INTERFACE_H_

#include "Types.h"

namespace IDCT
{

	class CInterface
	{
	public:
		virtual			~CInterface() {} ;
		virtual void	Transform(int16*, int16*) = 0;
	};

}

#endif
