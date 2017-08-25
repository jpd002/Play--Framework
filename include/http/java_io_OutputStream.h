#pragma once

#include <cstdlib>
#include <jni.h>
#include "Singleton.h"
#include "android/JavaObject.h"

namespace java
{
	namespace io
	{
		class OutputStream_ClassInfo : public CSingleton<OutputStream_ClassInfo>
		{
		public:
			void PrepareClassInfo();
			
			jclass clazz = NULL;
			jmethodID close = NULL;
			jmethodID write = NULL;
		};
		
		class OutputStream : public Framework::CJavaObject
		{
		public:
			typedef OutputStream_ClassInfo ClassInfo;
			
			OutputStream() = default;
			
			//Movable
			OutputStream(OutputStream&&);
			OutputStream& operator =(OutputStream&&);
			
			void close();
			void write(const jbyte*, size_t);
		};
	}
}
