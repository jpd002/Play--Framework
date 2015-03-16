#pragma once

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
							CProgram(const CProgram&) = delete;
							~CProgram();

			CProgram&		operator =(const CProgram&) = delete;
							operator GLuint() const;
			
			void			AttachShader(GLuint);
			void			DetachShader(GLuint);
			bool			Link();
			bool			Validate();
			void			SetUniformf(const char*, float, float);
			void			SetUniformi(const char*, int);
			void			SetUniformi(const char*, int, int);

		private:
			GLuint			m_nHandle;
		};

		typedef std::shared_ptr<CProgram> ProgramPtr;
	}
}
