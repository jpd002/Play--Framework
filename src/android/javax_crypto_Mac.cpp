#include "android/javax_crypto_Mac.h"
#include "android/JavaVM.h"
#include <cassert>

using namespace javax::crypto;

Mac Mac::getInstance(jstring algorithm)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	jobject macObject = env->CallStaticObjectMethod(classInfo.clazz, classInfo.getInstance, algorithm);
	Framework::CJavaVM::CheckException(env);

	Mac mac;
	mac.Attach(macObject);
	return mac;
}

void Mac::init(jobject key)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	env->CallVoidMethod(m_this, classInfo.init, key);
	Framework::CJavaVM::CheckException(env);
}

jbyteArray Mac::doFinal(jbyteArray input)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	jbyteArray result = static_cast<jbyteArray>(env->CallObjectMethod(m_this, classInfo.doFinal, input));
	Framework::CJavaVM::CheckException(env);
	return result;
}

void Mac_ClassInfo::PrepareClassInfo()
{
	auto env = Framework::CJavaVM::GetEnv();
	
	jclass tmpClazz = env->FindClass("javax/crypto/Mac");
	Framework::CJavaVM::CheckException(env);
	assert(tmpClazz != NULL);
	clazz = reinterpret_cast<jclass>(env->NewGlobalRef(tmpClazz));
	assert(clazz != NULL);
	
	getInstance = env->GetStaticMethodID(clazz, "getInstance", "(Ljava/lang/String;)Ljavax/crypto/Mac;");
	Framework::CJavaVM::CheckException(env);
	assert(getInstance != NULL);
	
	init = env->GetMethodID(clazz, "init", "(Ljava/security/Key;)V");
	Framework::CJavaVM::CheckException(env);
	assert(init != NULL);
	
	doFinal = env->GetMethodID(clazz, "doFinal", "([B)[B");
	Framework::CJavaVM::CheckException(env);
	assert(doFinal != NULL);
}
