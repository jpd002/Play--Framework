/*

	Framework - StdStream.h
	File Version 1.0.000

*/

#ifndef _STDSTREAM_H_
#define _STDSTREAM_H_

#include "Stream.h"
#include <stdio.h>

namespace Framework
{

	class CStdStream : public CStream
	{
	public:
				CStdStream(FILE*);
		virtual	~CStdStream();
		void	Seek(int64, STREAM_SEEK_DIRECTION);
		uint64	Tell();
		uint64	Read(void*, uint64);
		uint64	Write(const void*, uint64);
		bool	IsEOF();
		void	Flush();
		void	Close();
	private:
		FILE*	m_pFile;
	};

}


#endif
