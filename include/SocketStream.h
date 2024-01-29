#pragma once

#include "SocketDef.h"
#include "Stream.h"

namespace Framework
{
	void InitializeSocketSupport();

	class CSocketRefStream : public CStream
	{
	public:
		CSocketRefStream(SOCKET fd);
		virtual ~CSocketRefStream() = default;

		uint64 Read(void* buffer, uint64 size) override;
		uint64 Write(const void* buffer, uint64 size) override;
		uint64 Tell() override;
		void Seek(int64, Framework::STREAM_SEEK_DIRECTION) override;
		bool IsEOF() override;

	protected:
		SOCKET m_fd = INVALID_SOCKET;

	private:
		bool m_isEof = false;
	};

	class CSocketStream : public CSocketRefStream
	{
	public:
		CSocketStream(SOCKET fd);
		virtual ~CSocketStream();
	};
}
