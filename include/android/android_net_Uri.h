#pragma once

#include <cstdlib>
#include <jni.h>
#include "Singleton.h"
#include "android/JavaObject.h"

namespace android
{
	namespace net
	{
		class Uri_ClassInfo : public CSingleton<Uri_ClassInfo>
		{
		public:
			void PrepareClassInfo();
			
			jclass clazz = NULL;
			jmethodID parse = NULL;
		};
		
		class Uri : public Framework::CJavaObject
		{
		public:
			typedef Uri_ClassInfo ClassInfo;
			
			static Uri parse(jstring);
			
		private:
		
		};
	}
}
