#include <cassert>
#include "android/JavaObject.h"
#include "android/JavaVM.h"

using namespace Framework;

CJavaObject::~CJavaObject()
{
	Reset();
}

void CJavaObject::Attach(jobject srcObject)
{
	assert(m_this == NULL);
	if(srcObject == NULL)
	{
		//Attaching nothing is not a problem
		return;
	}
	auto env = Framework::CJavaVM::GetEnv();
	m_this = env->NewGlobalRef(srcObject);
	assert(m_this != NULL);
}

void CJavaObject::Reset()
{
	if(m_this != NULL)
	{
		auto env = Framework::CJavaVM::GetEnv();
		env->DeleteGlobalRef(m_this);
	}
	m_this = NULL;
}

void CJavaObject::MoveFrom(CJavaObject&& rhs)
{
	assert(m_this == NULL);
	std::swap(rhs.m_this, m_this);
}
