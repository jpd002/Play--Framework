#pragma once

#include <cstdlib>
#include <vector>
#include <jni.h>
#include "Singleton.h"
#include "android/JavaObject.h"

namespace java
{
	namespace io
	{
		class InputStream : public Framework::CJavaObject
		{
		public:
			InputStream() = default;
			
			static InputStream CastTo(jobject);
			
			//Movable
			InputStream(InputStream&&);
			InputStream& operator =(InputStream&&);
			
			jint read(std::vector<jbyte>&);
		};
		
		class InputStream_ClassInfo : public CSingleton<InputStream_ClassInfo>
		{
		public:
			void PrepareClassInfo();
			
			jclass clazz = NULL;
			jmethodID read = NULL;
		};
	}
}
