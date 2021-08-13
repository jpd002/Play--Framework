#pragma once

#include "../PosixFileStream.h"
#include "android_os_ParcelFileDescriptor.h"

namespace Framework
{
	namespace Android
	{
		class CContentStream : public CPosixFileStream
		{
		public:
			CContentStream(const char*, const char*);
			CContentStream(const CContentStream&) = delete;
			
			virtual ~CContentStream();

			CContentStream& operator =(const CContentStream&) = delete;
			
		private:
			android::os::ParcelFileDescriptor m_pfd;
		};
	}
}
