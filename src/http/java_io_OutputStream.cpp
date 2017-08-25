#include <cassert>
#include "http/java_io_OutputStream.h"
#include "android/JavaVM.h"

using namespace java::io;

void OutputStream::close()
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	env->CallVoidMethod(m_this, classInfo.close);
	Framework::CJavaVM::CheckException(env);
}

void OutputStream::write(const jbyte* b, size_t bSize)
{
	auto env = Framework::CJavaVM::GetEnv();
	const auto& classInfo = ClassInfo::GetInstance();
	auto bArray = env->NewByteArray(bSize);

	{
		auto bArrayElems = env->GetByteArrayElements(bArray, NULL);
		memcpy(bArrayElems, b, sizeof(jbyte) * bSize);
		env->ReleaseByteArrayElements(bArray, bArrayElems, 0);
	}

	env->CallVoidMethod(m_this, classInfo.write, bArray);
	Framework::CJavaVM::CheckException(env);
}

void OutputStream_ClassInfo::PrepareClassInfo()
{
	auto env = Framework::CJavaVM::GetEnv();
	
	jclass tmpClazz = env->FindClass("java/io/OutputStream");
	Framework::CJavaVM::CheckException(env);
	assert(tmpClazz != NULL);
	clazz = reinterpret_cast<jclass>(env->NewGlobalRef(tmpClazz));
	assert(clazz != NULL);
	
	close = env->GetMethodID(clazz, "close", "()V");
	Framework::CJavaVM::CheckException(env);
	assert(close != NULL);
	
	write = env->GetMethodID(clazz, "write", "([B)V");
	Framework::CJavaVM::CheckException(env);
	assert(write != NULL);
}
