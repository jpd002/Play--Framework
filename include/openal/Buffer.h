#ifndef _OPENAL_BUFFER_H_
#define _OPENAL_BUFFER_H_

#include "OpenAlDef.h"

namespace OpenAl
{
	class CBuffer
	{
	public:
						CBuffer();
		virtual			~CBuffer();

						operator ALuint() const;

	private:
		ALuint			m_name;
	};
};

#endif
