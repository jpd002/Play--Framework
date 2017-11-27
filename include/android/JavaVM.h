#pragma once

#include <cstddef>
#include <stdexcept>
#include <jni.h>

namespace Framework
{
	class JavaException : public std::exception
	{
	public:
		JavaException(jthrowable exception)
			: m_exception(exception)
		{
			
		}
		
		jthrowable m_exception = NULL;
	};
	
	class CJavaVM
	{
	public:
		static void SetJavaVM(JavaVM*);
		
		static JNIEnv* GetEnv();
		
		static void CheckException(JNIEnv*);
		
	private:
		static JavaVM* m_vm;
	};
}
