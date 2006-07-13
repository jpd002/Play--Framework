#ifndef _GZIPSTREAM_H_
#define _GZIPSTREAM_H_

#include <zlib.h>
#include "Stream.h"

namespace Framework
{
	class CGZipStream : public CStream
	{
	public:
					CGZipStream(const char*, const char*);
		virtual		~CGZipStream();
		void		Seek(int64, STREAM_SEEK_DIRECTION);
		uint64		Tell();
		uint64		Read(void*, uint64);
		uint64		Write(const void*, uint64);
		bool		IsEOF();

	private:
		gzFile		m_File;
	};
}

#endif
