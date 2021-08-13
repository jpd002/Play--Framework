#pragma once

#include "Singleton.h"
#include "android_content_ContentResolver.h"

namespace Framework
{
	namespace Android
	{
		class CContentResolver : public CSingleton<CContentResolver>
		{
		public:
			android::content::ContentResolver& GetContentResolver();
			void SetContentResolver(android::content::ContentResolver);
			
		private:
			android::content::ContentResolver m_contentResolver;
		};
	}
}
