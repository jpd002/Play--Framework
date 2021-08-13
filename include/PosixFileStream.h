#pragma once

#define _LARGEFILE64_SOURCE
#include <fcntl.h>
#include "Stream.h"

namespace Framework
{

	class CPosixFileStream : public CStream
	{
	public:
					CPosixFileStream(const char* path, int flags);
					CPosixFileStream(const CPosixFileStream&) = delete;
		virtual		~CPosixFileStream();

		CPosixFileStream& operator =(const CPosixFileStream&) = delete;
		
		void		Seek(int64, STREAM_SEEK_DIRECTION) override;
		uint64		Tell() override;
		uint64		Read(void*, uint64) override;
		uint64		Write(const void*, uint64) override;
		bool		IsEOF() override;
		void		Flush() override;

	protected:
					CPosixFileStream() = default;

		int			m_fd = 0;
		bool		m_ownsFd = false;
		bool		m_isEof = false;
	};

}
