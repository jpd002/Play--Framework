#pragma once

#include "Stream.h"

namespace Framework
{

	class CMemStream : public CStream
	{
	public:
							CMemStream();
		virtual				~CMemStream();
		uint64				Read(void*, uint64);
		uint64				Write(const void*, uint64);
		uint64				Tell();
		void				Seek(int64, STREAM_SEEK_DIRECTION);
		bool				IsEOF();
		void				ResetBuffer();
		void				Allocate(unsigned int);
		void				Truncate();
		uint8*				GetBuffer() const;
		unsigned int		GetSize() const;

	private:
		unsigned int		m_size;
		unsigned int		m_grow;
		unsigned int		m_position;
		uint8*				m_data;
		bool				m_isEof;
	};

}
