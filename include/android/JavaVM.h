#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>
#include <jni.h>

namespace Framework
{
	class JavaException : public std::exception
	{
	public:
		JavaException(jthrowable exception)
			: m_exception(exception)
		{
			GetExceptionMessage();
		}

		const char* what() const noexcept override
		{
			return m_message.c_str();
		}

		jthrowable m_exception = NULL;
		std::string m_message;

	private:
		void GetExceptionMessage();
	};

	class CJavaVM
	{
	public:
		static void SetJavaVM(JavaVM*);
		
		static void AttachCurrentThread(JNIEnv**, const char* = nullptr);
		static void DetachCurrentThread();
		
		static JNIEnv* GetEnv();
		
		static void CheckException(JNIEnv*);
		
	private:
		static JavaVM* m_vm;
	};
}
