#include "android/android_os_ParcelFileDescriptor.h"

#include <cassert>
#include "android/JavaVM.h"

using namespace android::os;

void ParcelFileDescriptor_ClassInfo::PrepareClassInfo()
{
	auto env = Framework::CJavaVM::GetEnv();
	
	jclass tmpClazz = env->FindClass("android/os/ParcelFileDescriptor");
	Framework::CJavaVM::CheckException(env);
	assert(tmpClazz != NULL);
	clazz = reinterpret_cast<jclass>(env->NewGlobalRef(tmpClazz));
	assert(clazz != NULL);
	
	getFd = env->GetMethodID(clazz, "getFd", "()I");
	Framework::CJavaVM::CheckException(env);
	assert(getFd != NULL);
	
	close = env->GetMethodID(clazz, "close", "()V");
	Framework::CJavaVM::CheckException(env);
	assert(close != NULL);
}

jint ParcelFileDescriptor::getFd()
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	jint result = env->CallIntMethod(m_this, classInfo.getFd);
	Framework::CJavaVM::CheckException(env);
	
	return result;
}

void ParcelFileDescriptor::close()
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	env->CallVoidMethod(m_this, classInfo.close);
	Framework::CJavaVM::CheckException(env);
}
