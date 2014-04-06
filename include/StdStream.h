#ifndef _STDSTREAM_H_
#define _STDSTREAM_H_

#include "Stream.h"
#include <stdio.h>

namespace Framework
{

	class CStdStream : public CStream
	{
	public:
						CStdStream();
						CStdStream(CStdStream&&);
		explicit		CStdStream(FILE*);
						CStdStream(const char*, const char*);
						CStdStream(const wchar_t*, const wchar_t*);
		virtual			~CStdStream();
		
		void			Clear();
		bool			IsEmpty() const;

						operator FILE*() const;
		CStdStream&		operator =(CStdStream&&);
		
		void			Seek(int64, STREAM_SEEK_DIRECTION);
		uint64			Tell();
		uint64			Read(void*, uint64);
		uint64			Write(const void*, uint64);
		bool			IsEOF();
		void			Flush();
		void			Close();
		
	private:
						CStdStream(const CStdStream&) {}
		CStdStream&		operator =(const CStdStream&) { return *this; }
		
		FILE*			m_file = nullptr;
	};

}

#endif
