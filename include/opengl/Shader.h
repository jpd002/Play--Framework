#ifndef _SHADER_H_
#define _SHADER_H_

#include "OpenGl.h"
#include <stdlib.h>

namespace Framework
{
	namespace OpenGl
	{
		class CShader
		{
		public:
						CShader(GLenum);
						~CShader();

			operator	GLuint();

			void		SetSource(const char*, size_t = 0);
			bool		Compile();

		private:
			GLuint		m_nHandle;
		};
	}
}

#endif
