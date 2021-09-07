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

	query = env->GetMethodID(clazz, "query", "(Landroid/net/Uri;[Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;Landroid/os/CancellationSignal;)Landroid/database/Cursor;");
	Framework::CJavaVM::CheckException(env);
	assert(query != NULL);
}

android::os::ParcelFileDescriptor ContentResolver::openFileDescriptor(jobject uri, jstring mode)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	jobject pfdObject = env->CallObjectMethod(m_this, classInfo.openFileDescriptor, uri, mode);
	Framework::CJavaVM::CheckException(env);

	return Framework::CJavaObject::CastTo<android::os::ParcelFileDescriptor>(pfdObject);
}

android::database::Cursor ContentResolver::query(jobject uri, jobjectArray projection, jstring selection, jobjectArray selectionArgs, jstring sortOrder, jobject cancellationSignal)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	jobject cursorObject = env->CallObjectMethod(m_this, classInfo.query, uri, projection, selection, selectionArgs, sortOrder, cancellationSignal);
	Framework::CJavaVM::CheckException(env);

	return Framework::CJavaObject::CastTo<android::database::Cursor>(cursorObject);
}
