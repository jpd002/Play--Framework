#ifndef _SHADER_H_
#define _SHADER_H_

#include "OpenGlDef.h"
#include <stdlib.h>

namespace Framework
{
	namespace OpenGl
	{
		class CShader
		{
		public:
						CShader(unsigned int);
						~CShader();

			operator	unsigned int();

			void		SetSource(const char*, size_t = 0);
			bool		Compile();

		private:
			GLuint		m_nHandle;
		};
	}
}

#endif
