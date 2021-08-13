#pragma once

#include <jni.h>
#include <cstdlib>
#include <stdexcept>
#include "JavaVM.h"

namespace Framework
{
	class CJavaObject
	{
	public:
		CJavaObject() = default;
		virtual ~CJavaObject();
		
		//Non-copyable
		CJavaObject(const CJavaObject&) = delete;
		CJavaObject& operator =(const CJavaObject&) = delete;
		
		//Moveable
		CJavaObject(CJavaObject&& src)
		{
			MoveFrom(std::move(src));
		}
		
		CJavaObject& operator =(CJavaObject&& rhs)
		{
			Reset();
			MoveFrom(std::move(rhs));
			return (*this);
		}
		
		template <typename ObjectType>
		static ObjectType CastTo(jobject src)
		{
			auto env = Framework::CJavaVM::GetEnv();
			const auto& classInfo = ObjectType::ClassInfo::GetInstance();
			if(env->IsInstanceOf(src, classInfo.clazz) == JNI_FALSE)
			{
				throw std::runtime_error("Invalid cast");
			}
			ObjectType newObject;
			newObject.Attach(src);
			return newObject;
		}
		
		operator jobject() const
		{
			return m_this;
		}
		
		bool IsEmpty() const
		{
			return (m_this == NULL);
		}
		
	protected:
		void Attach(jobject);
		void Reset();
		void MoveFrom(CJavaObject&&);
		
		jobject m_this = NULL;
	};
}
