#pragma once

#include "Stream.h"
#include <android/asset_manager_jni.h>

namespace Framework
{
	namespace Android
	{
		class CAssetStream : public CStream
		{
		public:
			           CAssetStream(const char*);
			           CAssetStream(const CAssetStream&) = delete;
			virtual    ~CAssetStream();

			CAssetStream&    operator =(const CAssetStream&) = delete;

			void      Seek(int64, Framework::STREAM_SEEK_DIRECTION) override;
			uint64    Tell() override;
			uint64    Read(void*, uint64) override;
			uint64    Write(const void*, uint64) override;
			bool      IsEOF() override;
			void      Flush() override;
			
		private:
			AAsset*    m_asset = nullptr;
		};
	}
}
