#pragma once

#include <cstdlib>
#include <jni.h>
#include "Singleton.h"
#include "android/JavaObject.h"

namespace javax
{
	namespace crypto
	{
		namespace spec
		{
			class SecretKeySpec_ClassInfo : public CSingleton<SecretKeySpec_ClassInfo>
			{
			public:
				void PrepareClassInfo();
				
				jclass clazz = NULL;
				jmethodID initBAS = NULL;
			};
			
			class SecretKeySpec : public Framework::CJavaObject
			{
			public:
				typedef SecretKeySpec_ClassInfo ClassInfo;
				
				SecretKeySpec(jbyteArray, jstring);
				
				//Movable
				SecretKeySpec(SecretKeySpec&&);
				SecretKeySpec& operator =(SecretKeySpec&&);
			};
		}
	}
}
