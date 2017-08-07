#include <cassert>
#include <stdexcept>
#include "android/JavaVM.h"

using namespace Framework;

JavaVM* CJavaVM::m_vm = nullptr;

void CJavaVM::SetJavaVM(JavaVM* vm)
{
	m_vm = vm;
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
		throw JavaException(exception);
	}
}
