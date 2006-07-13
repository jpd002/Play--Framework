#ifndef _PTRSTREAM_H_
#define _PTRSTREAM_H_

#include "Stream.h"

namespace Framework
{

	class CPtrStream : public CStream
	{
	public:
				CPtrStream(void*, uint64);
		void	Seek(int64, STREAM_SEEK_DIRECTION);
		uint64	Tell();
		uint64	Read(void*, uint64);
		uint64	Write(const void*, uint64);
		bool	IsEOF();
	private:
		uint64	m_nPosition;
		uint64	m_nSize;
		char*	m_pData;
		bool	m_nEOF;
	};

}

#endif
