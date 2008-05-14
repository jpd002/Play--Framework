#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <stdexcept>
#include "MemStream.h"
#include "PtrMacro.h"

#define GROWSIZE		(0x1000)

using namespace Framework;
using namespace std;

CMemStream::CMemStream() :
m_position(0)
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
	return m_position;
}

void CMemStream::Seek(int64 nPosition, STREAM_SEEK_DIRECTION nDir)
{
    switch(nDir)
    {
    case STREAM_SEEK_SET:
        if(nPosition > m_nSize) throw runtime_error("Invalid position.");
        m_position = static_cast<unsigned int>(nPosition);
        break;
    case STREAM_SEEK_CUR:
        m_position += static_cast<int>(nPosition);
        break;
    case STREAM_SEEK_END:
        m_position = m_nSize;
        break;
    }
}

uint64 CMemStream::Read(void* pData, uint64 nSize)
{
	assert(0);
	return 0;
}

uint64 CMemStream::Write(const void* pData, uint64 nSize)
{
    if((m_position + nSize) > m_nGrow)
    {
        m_nGrow += ((static_cast<unsigned int>(nSize) + GROWSIZE - 1) / GROWSIZE) * GROWSIZE;
        m_pData = reinterpret_cast<uint8*>(realloc(m_pData, m_nGrow));
    }
    memcpy(m_pData + m_position, pData, (uint32)nSize);
    m_position += static_cast<unsigned int>(nSize);
    m_nSize = max<unsigned int>(m_nSize, m_position);
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
