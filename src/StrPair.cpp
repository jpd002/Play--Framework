#include "StrPair.h"

using namespace Framework;

CStrPair::CStrPair(const char* sFirst, const char* sSecond)
{
	m_sString[0] = sFirst;
	m_sString[1] = sSecond;
}

CStrPair::~CStrPair()
{
	
}

const char* CStrPair::First()
{
	return m_sString[0];
}

const char* CStrPair::Second()
{
	return m_sString[1];
}

const char* CStrPair::operator [] (int nIndex)
{
	if(nIndex < 0) return NULL;
	if(nIndex > 2) return NULL;
	return m_sString[nIndex];
}
