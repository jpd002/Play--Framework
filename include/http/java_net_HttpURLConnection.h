#pragma once

#include <cstdlib>
#include <jni.h>
#include "Singleton.h"
#include "android/JavaObject.h"

namespace java
{
	namespace net
	{
		class HttpURLConnection_ClassInfo : public CSingleton<HttpURLConnection_ClassInfo>
		{
		public:
			void PrepareClassInfo();
			
			jclass clazz = NULL;
			jmethodID disconnect = NULL;
			jmethodID getInputStream = NULL;
			jmethodID getResponseCode = NULL;
		};
		
		class HttpURLConnection : public Framework::CJavaObject
		{
		public:
			typedef HttpURLConnection_ClassInfo ClassInfo;
			
			HttpURLConnection() = default;
			
			//Movable
			HttpURLConnection(HttpURLConnection&&);
			HttpURLConnection& operator =(HttpURLConnection&&);
			
			void disconnect();
			jobject getInputStream();
			jint getResponseCode();
		};
	}
}
