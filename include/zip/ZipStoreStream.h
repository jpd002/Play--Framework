#pragma once

#include "Stream.h"

namespace Framework
{
	class CZipStoreStream : public Framework::CStream
	{
	public:
								CZipStoreStream(Framework::CStream&, unsigned int);
		virtual					~CZipStoreStream() = default;

		void					Seek(int64, Framework::STREAM_SEEK_DIRECTION) override;
		uint64					Tell() override;
		uint64					Read(void*, uint64) override;
		uint64					Write(const void*, uint64) override;
		bool					IsEOF() override;

	private:
		Framework::CStream&		m_baseStream;
		unsigned int			m_length = 0;
	};
}
