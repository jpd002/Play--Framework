#pragma once

#include <cstdlib>
#include <jni.h>
#include "Singleton.h"
#include "android/JavaObject.h"

namespace java
{
	namespace net
	{
		class URL : public Framework::CJavaObject
		{
		public:
			URL(jstring);
			
			//Movable
			URL(URL&&);
			URL& operator =(URL&&);
			
			jobject openConnection();
		};
		
		class URL_ClassInfo : public CSingleton<URL_ClassInfo>
		{
		public:
			void PrepareClassInfo();
			
			jclass clazz = NULL;
			jmethodID initS = NULL;
			jmethodID openConnection = NULL;
		};
	}
}
