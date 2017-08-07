#include <cassert>
#include "android/JavaObject.h"
#include "android/JavaVM.h"

using namespace Framework;

CJavaObject::~CJavaObject()
{
	if(m_this != NULL)
	{
		auto env = Framework::CJavaVM::GetEnv();
		env->DeleteGlobalRef(m_this);
	}
}

void CJavaObject::Attach(jobject srcObject)
{
	assert(m_this == NULL);
	auto env = Framework::CJavaVM::GetEnv();
	m_this = env->NewGlobalRef(srcObject);
	assert(m_this != NULL);
}
