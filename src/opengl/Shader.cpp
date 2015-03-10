#include <algorithm>
#include <cassert>
#include "alloca_def.h"
#include "opengl/Shader.h"

using namespace Framework::OpenGl;

CShader::CShader(GLenum nType)
: m_nHandle(0)
{
	m_nHandle = glCreateShader(nType);
}

CShader::CShader(CShader&& src)
: m_nHandle(0)
{
	std::swap(src.m_nHandle, m_nHandle);
}

CShader::~CShader()
{
	if(m_nHandle != 0)
	{
		glDeleteShader(m_nHandle);
	}
}

CShader::operator GLuint() const
{
	return m_nHandle;
}

void CShader::SetSource(const char* sSource, size_t nLength)
{
	GLint* pSize(NULL);

	if(nLength != 0)
	{
		pSize = reinterpret_cast<GLint*>(&nLength);
	}
	else
	{
		pSize = NULL;
	}

	glShaderSource(m_nHandle, 1, &sSource, pSize);
}

bool CShader::Compile()
{
	GLint nStatus = GL_FALSE;

	glCompileShader(m_nHandle);
	glGetShaderiv(m_nHandle, GL_COMPILE_STATUS, &nStatus);

	if(nStatus == GL_FALSE)
	{
		GLint length = 0;
		glGetShaderiv(m_nHandle, GL_INFO_LOG_LENGTH, &length);
		char* error = reinterpret_cast<char*>(alloca(length + 1));
		glGetShaderInfoLog(m_nHandle, length + 1, &length, error);
		error[length] = 0;
		assert(0);
	}

	return (nStatus == GL_TRUE);
}
