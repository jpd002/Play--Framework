#pragma once

#include "Stream.h"

namespace Framework
{
	class CSocketRefStream : public CStream
	{
	public:
		CSocketRefStream(int fd);
		virtual ~CSocketRefStream() = default;
		
		uint64 Read(void* buffer, uint64 size) override;
		uint64 Write(const void* buffer, uint64 size) override;
		uint64 Tell() override;
		void Seek(int64, Framework::STREAM_SEEK_DIRECTION) override;
		bool IsEOF() override;
		
	protected:
		int m_fd = -1;

	private:
		bool m_isEof = false;
	};

	class CSocketStream : public CSocketRefStream
	{
	public:
		CSocketStream(int fd);
		virtual ~CSocketStream();
	};
}
