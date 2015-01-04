#pragma once

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
						CShader(const CShader&) = delete;
						CShader(CShader&&);
						~CShader();

			CShader&	operator =(const CShader&) = delete;
			CShader&	operator =(CShader&&);
						operator GLuint() const;

			void		SetSource(const char*, size_t = 0);
			bool		Compile();

		private:
			GLuint		m_nHandle;
		};
	}
}
