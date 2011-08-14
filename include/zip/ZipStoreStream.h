#ifndef _ZIPSTORESTREAM_H_
#define _ZIPSTORESTREAM_H_

#include "Stream.h"

namespace Framework
{
	class CZipStoreStream : public Framework::CStream
	{
	public:
								CZipStoreStream(Framework::CStream&, unsigned int);
		virtual					~CZipStoreStream();

		virtual void			Seek(int64, Framework::STREAM_SEEK_DIRECTION);
		virtual uint64			Tell();
		virtual uint64			Read(void*, uint64);
		virtual uint64			Write(const void*, uint64);
		virtual bool			IsEOF();

	private:
		Framework::CStream&		m_baseStream;
		unsigned int			m_length;
	};
}

#endif
