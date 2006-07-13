#ifndef _MEMSTREAM_H_
#define _MEMSTREAM_H_

#include "Stream.h"

namespace Framework
{

	class CMemStream : public CStream
	{
	public:
							CMemStream();
							~CMemStream();
		uint64				Read(void*, uint64);
		uint64				Write(const void*, uint64);
		uint64				Tell();
		void				Seek(int64, STREAM_SEEK_DIRECTION);
		bool				IsEOF();
		const uint8*		GetBuffer();
		const unsigned int	GetSize();
	private:
		unsigned int		m_nSize;
		unsigned int		m_nGrow;
		uint8*				m_pData;
	};

}


#endif