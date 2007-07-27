#include "PtrStream.h"
#include <assert.h>
#include <string.h>

using namespace Framework;

CPtrStream::CPtrStream(void* pData, uint64 nSize)
{
	m_pData = (char*)pData;
	m_nSize = nSize;
	m_nPosition = 0;
	m_nEOF = false;
}

void CPtrStream::Seek(int64 nPosition, STREAM_SEEK_DIRECTION nDirection)
{
	m_nEOF = false;
	switch(nDirection)
	{
	case STREAM_SEEK_SET:
		assert((uint64)nPosition <= m_nSize);
		m_nPosition = nPosition;
		break;
	case STREAM_SEEK_CUR:
		assert((m_nPosition + nPosition) <= m_nSize);
		assert((m_nPosition + nPosition) >= 0);
		m_nPosition += nPosition;
        break;
	case STREAM_SEEK_END:
		m_nPosition = m_nSize;
		break;
	}
}

uint64 CPtrStream::Tell()
{
	return m_nPosition;
}

bool CPtrStream::IsEOF()
{
	return m_nEOF;
}

uint64 CPtrStream::Read(void* pBuffer, uint64 nSize)
{
	if(m_nPosition == m_nSize)
	{
		m_nEOF = true;
		return 0;
	}
	if((m_nPosition + nSize) > m_nSize)
	{
		nSize = (m_nSize - m_nPosition);
	}
	memcpy(pBuffer, m_pData + m_nPosition, (size_t)nSize);
	m_nPosition += nSize;
	return nSize;
}

uint64 CPtrStream::Write(const void* pBuffer, uint64 nSize)
{
	//Operation not supported
	assert(0);
	return 0;
}
