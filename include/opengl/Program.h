#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "OpenGlDef.h"
#include <memory>

namespace Framework
{
	namespace OpenGl
	{
		class CProgram
		{
		public:
							CProgram();
							~CProgram();

			operator		GLuint() const;
			
			void			AttachShader(GLuint);
			void			DetachShader(GLuint);
			bool			Link();
			void			SetUniformf(const char*, float, float);
			void			SetUniformi(const char*, int);
			void			SetUniformi(const char*, int, int);

		private:
							CProgram(const CProgram&) {}
							CProgram& operator =(const CProgram&) {}

			GLuint			m_nHandle;
		};

		typedef std::shared_ptr<CProgram> ProgramPtr;
	}
}

#endif
