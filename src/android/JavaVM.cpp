#include <cassert>
#include <stdexcept>
#include "android/JavaVM.h"

using namespace Framework;

JavaVM* CJavaVM::m_vm = nullptr;

void CJavaVM::SetJavaVM(JavaVM* vm)
{
	m_vm = vm;
}

void CJavaVM::AttachCurrentThread(JNIEnv** env, const char* threadName)
{
	assert(m_vm != nullptr);

	JavaVMAttachArgs args = {};
	args.version = JNI_VERSION_1_6;
	args.name = threadName;

	[[maybe_unused]] jint result = m_vm->AttachCurrentThread(env, &args);
	assert(result == JNI_OK);
}

void CJavaVM::DetachCurrentThread()
{
	assert(m_vm != nullptr);
	m_vm->DetachCurrentThread();
}

JNIEnv* CJavaVM::GetEnv()
{
	assert(m_vm != nullptr);
	JNIEnv* env = nullptr;
	if(m_vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK)
	{
		throw std::runtime_error("Failed to obtain JNIEnv");
	}
	return env;
}

void CJavaVM::CheckException(JNIEnv* env)
{
	if(env->ExceptionCheck())
	{
		env->ExceptionDescribe();
		jthrowable exception = env->ExceptionOccurred();
		env->ExceptionClear();
		throw JavaException(exception);
	}
}

void JavaException::GetExceptionMessage()
{
	auto env = CJavaVM::GetEnv();
	jclass clazz = env->GetObjectClass(m_exception);
	jmethodID toString = env->GetMethodID(clazz, "toString", "()Ljava/lang/String;");
	jstring messageObject = static_cast<jstring>(env->CallObjectMethod(m_exception, toString));
	const char* messageString = env->GetStringUTFChars(messageObject, NULL);
	m_message = messageString;
	env->ReleaseStringUTFChars(messageObject, messageString);
	env->DeleteLocalRef(messageObject);
	env->DeleteLocalRef(clazz);
}
