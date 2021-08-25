#include "android/android_database_Cursor.h"

#include <cassert>
#include "android/JavaVM.h"

using namespace android::database;

void Cursor_ClassInfo::PrepareClassInfo()
{
	auto env = Framework::CJavaVM::GetEnv();
	
	jclass tmpClazz = env->FindClass("android/database/Cursor");
	Framework::CJavaVM::CheckException(env);
	assert(tmpClazz != NULL);
	clazz = reinterpret_cast<jclass>(env->NewGlobalRef(tmpClazz));
	assert(clazz != NULL);
	
	close = env->GetMethodID(clazz, "close", "()V");
	Framework::CJavaVM::CheckException(env);
	assert(close != NULL);

	getCount = env->GetMethodID(clazz, "getCount", "()I");
	Framework::CJavaVM::CheckException(env);
	assert(getCount != NULL);
}

void Cursor::close()
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	env->CallVoidMethod(m_this, classInfo.close);
	Framework::CJavaVM::CheckException(env);
}

jint Cursor::getCount()
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	jint result = env->CallIntMethod(m_this, classInfo.getCount);
	Framework::CJavaVM::CheckException(env);
	return result;
}
