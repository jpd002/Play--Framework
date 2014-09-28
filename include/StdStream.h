#pragma once

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
		
		void			Seek(int64, STREAM_SEEK_DIRECTION) override;
		uint64			Tell() override;
		uint64			Read(void*, uint64) override;
		uint64			Write(const void*, uint64) override;
		bool			IsEOF() override;
		void			Flush() override;
		void			Close();
		
	private:
						CStdStream(const CStdStream&) {}
		CStdStream&		operator =(const CStdStream&) { return *this; }
		
		FILE*			m_file = nullptr;
	};

}
