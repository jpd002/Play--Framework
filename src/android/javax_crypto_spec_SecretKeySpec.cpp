#include "android/javax_crypto_spec_SecretKeySpec.h"

#include <cassert>
#include "android/JavaVM.h"

using namespace javax::crypto::spec;

SecretKeySpec::SecretKeySpec(jbyteArray key, jstring algorithm)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	jobject result = env->NewObject(classInfo.clazz, classInfo.initBAS, key, algorithm);
	Framework::CJavaVM::CheckException(env);
	assert(result != NULL);
	Attach(result);
}

void SecretKeySpec_ClassInfo::PrepareClassInfo()
{
	auto env = Framework::CJavaVM::GetEnv();
	
	jclass tmpClazz = env->FindClass("javax/crypto/spec/SecretKeySpec");
	Framework::CJavaVM::CheckException(env);
	assert(tmpClazz != NULL);
	clazz = reinterpret_cast<jclass>(env->NewGlobalRef(tmpClazz));
	assert(clazz != NULL);
	
	initBAS = env->GetMethodID(clazz, "<init>", "([BLjava/lang/String;)V");
	Framework::CJavaVM::CheckException(env);
	assert(initBAS != NULL);
}
