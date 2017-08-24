#include <cassert>
#include "http/java_io_InputStream.h"
#include "android/JavaVM.h"

using namespace java::io;

jint InputStream::read(std::vector<jbyte>& b)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	auto bArray = env->NewByteArray(b.size());
	auto result = env->CallIntMethod(m_this, classInfo.read, bArray);
	Framework::CJavaVM::CheckException(env);
	env->GetByteArrayRegion(bArray, 0, b.size(), b.data());
	return result;
}

void InputStream_ClassInfo::PrepareClassInfo()
{
	auto env = Framework::CJavaVM::GetEnv();
	
	jclass tmpClazz = env->FindClass("java/io/InputStream");
	Framework::CJavaVM::CheckException(env);
	assert(tmpClazz != NULL);
	clazz = reinterpret_cast<jclass>(env->NewGlobalRef(tmpClazz));
	assert(clazz != NULL);
	
	read = env->GetMethodID(clazz, "read", "([B)I");
	Framework::CJavaVM::CheckException(env);
	assert(read != NULL);
}
