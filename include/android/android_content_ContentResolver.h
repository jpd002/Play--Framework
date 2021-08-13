#pragma once

#include <cstdlib>
#include <jni.h>
#include "Singleton.h"
#include "android/JavaObject.h"
#include "android/android_os_ParcelFileDescriptor.h"

namespace android
{
	namespace content
	{
		class ContentResolver_ClassInfo : public CSingleton<ContentResolver_ClassInfo>
		{
		public:
			void PrepareClassInfo();
			
			jclass clazz = NULL;
			jmethodID openFileDescriptor = NULL;
		};
		
		class ContentResolver : public Framework::CJavaObject
		{
		public:
			typedef ContentResolver_ClassInfo ClassInfo;
			
			android::os::ParcelFileDescriptor openFileDescriptor(jobject, jstring);
			
		private:
		
		};
	}
}
