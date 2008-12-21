#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "OpenAlDef.h"

namespace OpenAl
{
	class CContext
	{
	public:
						CContext(ALCdevice*, ALCint*, bool = true);
		virtual			~CContext();

		void			MakeCurrent();

	private:
		ALCcontext*		m_context;
	};
}

#endif
