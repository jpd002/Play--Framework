#include <cassert>
#include "http/java_net_URL.h"
#include "android/JavaVM.h"

using namespace java::net;

URL::URL(jstring spec)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = URL_ClassInfo::GetInstance();
	jobject result = env->NewObject(classInfo.clazz, classInfo.initS, spec);
	Framework::CJavaVM::CheckException(env);
	assert(result != NULL);
	Attach(result);
}

jobject URL::openConnection()
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = URL_ClassInfo::GetInstance();
	jobject result = env->CallObjectMethod(m_this, classInfo.openConnection);
	Framework::CJavaVM::CheckException(env);
	assert(result != NULL);
	return result;
}

void URL_ClassInfo::PrepareClassInfo()
{
	auto env = Framework::CJavaVM::GetEnv();
	
	jclass tmpClazz = env->FindClass("java/net/URL");
	Framework::CJavaVM::CheckException(env);
	assert(tmpClazz != NULL);
	clazz = reinterpret_cast<jclass>(env->NewGlobalRef(tmpClazz));
	assert(clazz != NULL);
	
	initS = env->GetMethodID(clazz, "<init>", "(Ljava/lang/String;)V");
	Framework::CJavaVM::CheckException(env);
	assert(initS != NULL);
	
	openConnection = env->GetMethodID(clazz, "openConnection", "()Ljava/net/URLConnection;");
	Framework::CJavaVM::CheckException(env);
	assert(openConnection != NULL);
}
