#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "MemStream.h"
#include "PtrMacro.h"

#define GROWSIZE		(0x1000)

using namespace Framework;

CMemStream::CMemStream()
{
	m_nSize = 0;
	m_nGrow = 0;
	m_pData = NULL;
}

CMemStream::~CMemStream()
{
	FREEPTR(m_pData);
}

bool CMemStream::IsEOF()
{
	return true;
}

uint64 CMemStream::Tell()
{
	return m_nSize;
}

void CMemStream::Seek(int64 nPosition, STREAM_SEEK_DIRECTION nDir)
{
	assert(0);
}

uint64 CMemStream::Read(void* pData, uint64 nSize)
{
	assert(0);
	return 0;
}

uint64 CMemStream::Write(const void* pData, uint64 nSize)
{
	while((m_nSize + nSize) > m_nGrow)
	{
		m_nGrow += GROWSIZE;
		m_pData = (uint8*)realloc(m_pData, m_nGrow);
	}
	memcpy(m_pData + m_nSize, pData, (uint32)nSize);
	m_nSize += (uint32)nSize;
	return nSize;
}

const uint8* CMemStream::GetBuffer()
{
	return m_pData;
}

const unsigned int CMemStream::GetSize()
{
	return m_nSize;
}
