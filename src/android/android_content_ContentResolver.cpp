#include "android/android_content_ContentResolver.h"

#include <cassert>
#include "android/JavaVM.h"

using namespace android::content;

void ContentResolver_ClassInfo::PrepareClassInfo()
{
	auto env = Framework::CJavaVM::GetEnv();
	
	jclass tmpClazz = env->FindClass("android/content/ContentResolver");
	Framework::CJavaVM::CheckException(env);
	assert(tmpClazz != NULL);
	clazz = reinterpret_cast<jclass>(env->NewGlobalRef(tmpClazz));
	assert(clazz != NULL);
	
	openFileDescriptor = env->GetMethodID(clazz, "openFileDescriptor", "(Landroid/net/Uri;Ljava/lang/String;)Landroid/os/ParcelFileDescriptor;");
	Framework::CJavaVM::CheckException(env);
	assert(openFileDescriptor != NULL);
}

android::os::ParcelFileDescriptor ContentResolver::openFileDescriptor(jobject uri, jstring mode)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	jobject pfdObject = env->CallObjectMethod(m_this, classInfo.openFileDescriptor, uri, mode);
	Framework::CJavaVM::CheckException(env);

	return Framework::CJavaObject::CastTo<android::os::ParcelFileDescriptor>(pfdObject);
}
