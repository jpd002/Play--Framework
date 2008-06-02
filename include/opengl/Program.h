#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "OpenGlDef.h"

namespace Framework
{
	namespace OpenGl
	{
		class CProgram
		{
		public:
							CProgram();
							~CProgram();

			operator		unsigned int();
			
			void			AttachShader(unsigned int);
			void			DetachShader(unsigned int);
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
