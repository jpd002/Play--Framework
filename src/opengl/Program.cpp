#include <cassert>
#include "alloca_def.h"
#include "opengl/Program.h"

using namespace Framework::OpenGl;

CProgram::CProgram()
{
	m_nHandle = glCreateProgram();
}

CProgram::~CProgram()
{
	glDeleteProgram(m_nHandle);
}

CProgram::operator GLuint() const
{
	return m_nHandle;
}

void CProgram::AttachShader(GLuint nShader)
{
	glAttachShader(m_nHandle, nShader);
}

void CProgram::DetachShader(GLuint nShader)
{
	glDetachShader(m_nHandle, nShader);
}

bool CProgram::Link()
{
	GLint nStatus = GL_FALSE;

	glLinkProgram(m_nHandle);
	glGetProgramiv(m_nHandle, GL_LINK_STATUS, &nStatus);

	if(nStatus == GL_FALSE)
	{
		GLint length = 0;
		glGetProgramiv(m_nHandle, GL_INFO_LOG_LENGTH, &length);
		char* error = reinterpret_cast<char*>(alloca(length + 1));
		glGetProgramInfoLog(m_nHandle, length + 1, &length, error);
		error[length] = 0;
		assert(0);
	}

	return (nStatus == GL_TRUE);
}

bool CProgram::Validate()
{
	GLint status = GL_FALSE;

	glValidateProgram(m_nHandle);
	glGetProgramiv(m_nHandle, GL_VALIDATE_STATUS, &status);

	if(status == GL_FALSE)
	{
		GLint length = 0;
		glGetProgramiv(m_nHandle, GL_INFO_LOG_LENGTH, &length);
		char* error = reinterpret_cast<char*>(alloca(length + 1));
		glGetProgramInfoLog(m_nHandle, length + 1, &length, error);
		error[length] = 0;
		assert(0);
	}

	return (status == GL_TRUE);
}

void CProgram::SetUniformf(const char* sName, float nV1, float nV2)
{
	GLuint nUniform = glGetUniformLocation(m_nHandle, sName);
	glUniform2f(nUniform, nV1, nV2);
}

void CProgram::SetUniformi(const char* sName, int nV1)
{
	GLuint nUniform = glGetUniformLocation(m_nHandle, sName);
	glUniform1i(nUniform, nV1);
}

void CProgram::SetUniformi(const char* sName, int nV1, int nV2)
{
	GLuint nUniform = glGetUniformLocation(m_nHandle, sName);
	glUniform2i(nUniform, nV1, nV2);
}
