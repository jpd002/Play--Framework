#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "OpenGl.h"

namespace Framework
{
	namespace OpenGl
	{
		class CProgram
		{
		public:
							CProgram();
							~CProgram();

			operator		GLuint();

			void			AttachShader(GLuint);
			void			DetachShader(GLuint);
			bool			Link();
			void			SetUniformf(const char*, float, float);
			void			SetUniformi(const char*, int);
			void			SetUniformi(const char*, int, int);

		private:
			GLuint			m_nHandle;
		};
	}
}

#endif
