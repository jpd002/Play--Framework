#pragma once

#include <jni.h>
#include <cstdlib>

namespace Framework
{
	class CJavaObject
	{
	public:
		CJavaObject() = default;
		virtual ~CJavaObject();
		
		//Non-copyable
		CJavaObject(const CJavaObject&) = delete;
		CJavaObject& operator =(const CJavaObject&) = delete;
		
	protected:
		void Attach(jobject);
		
		jobject m_this = NULL;
	};
}
