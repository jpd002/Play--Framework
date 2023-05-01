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
		const char*	m_data = nullptr;
		uint64		m_size = 0;
		uint64		m_position = 0;
		bool		m_isEof = false;
	};

}
