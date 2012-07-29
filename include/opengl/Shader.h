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
			explicit	CShader(GLenum);
						CShader(CShader&&);
						~CShader();

			CShader&	operator =(CShader&&);

			operator	GLuint() const;

			void		SetSource(const char*, size_t = 0);
			bool		Compile();

		private:
						CShader(const CShader&) {}
						CShader& operator =(const CShader&) {}

			GLuint		m_nHandle;
		};
	}
}

#endif
