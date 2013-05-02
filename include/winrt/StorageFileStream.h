#pragma once

#include "Stream.h"

namespace Framework
{
	namespace WinRt
	{
		class CStorageFileStream : public CStream
		{
		public:
								CStorageFileStream();
								CStorageFileStream(Windows::Storage::StorageFile^);
			virtual				~CStorageFileStream();

			virtual void		Seek(int64, STREAM_SEEK_DIRECTION);
			virtual uint64		Tell();
			virtual uint64		Read(void*, uint64);
			virtual uint64		Write(const void*, uint64);
			virtual bool		IsEOF();

		private:
			Windows::Storage::Streams::IRandomAccessStream^	m_stream;

		};
	}
}
