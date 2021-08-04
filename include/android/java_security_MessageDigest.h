#pragma once

#include <cstdlib>
#include <jni.h>
#include "Singleton.h"
#include "android/JavaObject.h"

namespace java
{
	namespace security
	{
		class MessageDigest_ClassInfo : public CSingleton<MessageDigest_ClassInfo>
		{
		public:
			void PrepareClassInfo();
			
			jclass clazz = NULL;
			jmethodID getInstance = NULL;
			jmethodID digest = NULL;
		};
		
		class MessageDigest : public Framework::CJavaObject
		{
		public:
			typedef MessageDigest_ClassInfo ClassInfo;
			
			MessageDigest() = default;
			
			//Movable
			MessageDigest(MessageDigest&&);
			MessageDigest& operator =(MessageDigest&&);
			
			static MessageDigest getInstance(jstring);
			
			jbyteArray digest(jbyteArray);
			
		private:
		
		};
	}
}
