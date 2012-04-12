#include "opengl/Shader.h"

using namespace Framework::OpenGl;

CShader::CShader(unsigned int nType)
{
	m_nHandle = glCreateShader(nType);
}

CShader::~CShader()
{
	glDeleteShader(m_nHandle);
}

CShader::operator unsigned int()
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

	return (nStatus == GL_TRUE);
}
