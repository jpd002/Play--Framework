#include "PtrStream.h"
#include <assert.h>
#include <string.h>

using namespace Framework;

CPtrStream::CPtrStream(const void* data, uint64 size)
: m_data(reinterpret_cast<const char*>(data))
, m_size(size)
, m_position(0)
, m_isEof(false)
{

}

void CPtrStream::Seek(int64 position, STREAM_SEEK_DIRECTION direction)
{
	m_isEof = false;
	switch(direction)
	{
	case STREAM_SEEK_SET:
		assert((uint64)position <= m_size);
		m_position = position;
		break;
	case STREAM_SEEK_CUR:
		assert((m_position + position) <= m_size);
		assert((m_position + position) >= 0);
		m_position += position;
		break;
	case STREAM_SEEK_END:
		m_position = m_size;
		break;
	}
}

uint64 CPtrStream::Tell()
{
	return m_position;
}

bool CPtrStream::IsEOF()
{
	return m_isEof;
}

uint64 CPtrStream::Read(void* buffer, uint64 size)
{
	if(m_position == m_size)
	{
		m_isEof = true;
		return 0;
	}
	if((m_position + size) > m_size)
	{
		size = (m_size - m_position);
	}
	memcpy(buffer, m_data + m_position, (size_t)size);
	m_position += size;
	return size;
}

uint64 CPtrStream::Write(const void*, uint64)
{
	//Operation not supported
	assert(0);
	return 0;
}
