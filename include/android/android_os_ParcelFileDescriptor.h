#pragma once

#include <cstdlib>
#include <jni.h>
#include "Singleton.h"
#include "android/JavaObject.h"

namespace android
{
	namespace os
	{
		class ParcelFileDescriptor_ClassInfo : public CSingleton<ParcelFileDescriptor_ClassInfo>
		{
		public:
			void PrepareClassInfo();
			
			jclass clazz = NULL;
			jmethodID getFd = NULL;
			jmethodID close = NULL;
		};
		
		class ParcelFileDescriptor : public Framework::CJavaObject
		{
		public:
			typedef ParcelFileDescriptor_ClassInfo ClassInfo;
			
			jint getFd();
			void close();
		};
	}
}
