#include "android/java_security_MessageDigest.h"
#include "android/JavaVM.h"
#include <cassert>

using namespace java::security;

MessageDigest MessageDigest::getInstance(jstring algorithm)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	jobject digestObject = env->CallStaticObjectMethod(classInfo.clazz, classInfo.getInstance, algorithm);
	Framework::CJavaVM::CheckException(env);

	MessageDigest digest;
	digest.Attach(digestObject);
	return digest;
}

jbyteArray MessageDigest::digest(jbyteArray input)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	jbyteArray result = static_cast<jbyteArray>(env->CallObjectMethod(m_this, classInfo.digest, input));
	Framework::CJavaVM::CheckException(env);
	return result;
}

void MessageDigest_ClassInfo::PrepareClassInfo()
{
	auto env = Framework::CJavaVM::GetEnv();
	
	jclass tmpClazz = env->FindClass("java/security/MessageDigest");
	Framework::CJavaVM::CheckException(env);
	assert(tmpClazz != NULL);
	clazz = reinterpret_cast<jclass>(env->NewGlobalRef(tmpClazz));
	assert(clazz != NULL);
	
	getInstance = env->GetStaticMethodID(clazz, "getInstance", "(Ljava/lang/String;)Ljava/security/MessageDigest;");
	Framework::CJavaVM::CheckException(env);
	assert(getInstance != NULL);

	digest = env->GetMethodID(clazz, "digest", "([B)[B");
	Framework::CJavaVM::CheckException(env);
	assert(digest != NULL);
}
