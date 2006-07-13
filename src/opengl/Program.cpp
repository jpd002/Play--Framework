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

CProgram::operator GLuint()
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
	GLint nStatus;

	glLinkProgram(m_nHandle);
	glGetProgramiv(m_nHandle, GL_LINK_STATUS, &nStatus);

	return (nStatus == GL_TRUE);
}

void CProgram::SetUniformf(const char* sName, float nV1, float nV2)
{
	GLuint nUniform;
	nUniform = glGetUniformLocation(m_nHandle, sName);
	glUniform2f(nUniform, nV1, nV2);
}

void CProgram::SetUniformi(const char* sName, int nV1)
{
	GLuint nUniform;
	nUniform = glGetUniformLocation(m_nHandle, sName);
	glUniform1i(nUniform, nV1);
}

void CProgram::SetUniformi(const char* sName, int nV1, int nV2)
{
	GLuint nUniform;
	nUniform = glGetUniformLocation(m_nHandle, sName);
	glUniform2i(nUniform, nV1, nV2);
}
