#pragma once

#include <cstdlib>
#include <jni.h>
#include "Singleton.h"
#include "android/JavaObject.h"

namespace android
{
	namespace database
	{
		class Cursor_ClassInfo : public CSingleton<Cursor_ClassInfo>
		{
		public:
			void PrepareClassInfo();
			
			jclass clazz = NULL;
			jmethodID close = NULL;
			jmethodID getCount = NULL;
		};
		
		class Cursor : public Framework::CJavaObject
		{
		public:
			typedef Cursor_ClassInfo ClassInfo;

			void close();
			jint getCount();
		};
	}
}
