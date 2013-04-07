#pragma once

#include "Stream.h"

namespace Framework
{

	class CPtrStream : public CStream
	{
	public:
					CPtrStream(const void*, uint64);
		void		Seek(int64, STREAM_SEEK_DIRECTION);
		uint64		Tell();
		uint64		Read(void*, uint64);
		uint64		Write(const void*, uint64);
		bool		IsEOF();
	private:
		uint64		m_position;
		uint64		m_size;
		const char*	m_data;
		bool		m_isEof;
	};

}
