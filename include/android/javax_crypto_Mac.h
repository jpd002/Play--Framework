#pragma once

#include <cstdlib>
#include <jni.h>
#include "Singleton.h"
#include "android/JavaObject.h"

namespace javax
{
	namespace crypto
	{
		class Mac_ClassInfo : public CSingleton<Mac_ClassInfo>
		{
		public:
			void PrepareClassInfo();
			
			jclass clazz = NULL;
			jmethodID getInstance = NULL;
			jmethodID init = NULL;
			jmethodID doFinal = NULL;
		};
		
		class Mac : public Framework::CJavaObject
		{
		public:
			typedef Mac_ClassInfo ClassInfo;
			
			Mac() = default;
			
			//Movable
			Mac(Mac&&);
			Mac& operator =(Mac&&);
			
			static Mac getInstance(jstring);
			
			void init(jobject);
			jbyteArray doFinal(jbyteArray);
		};
	}
}
