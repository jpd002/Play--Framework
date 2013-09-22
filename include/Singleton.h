#pragma once

#include <mutex>
#include <memory>

template <typename Type> class CSingleton
{
public:
	static Type& GetInstance()
	{
		std::call_once(m_onceFlag, 
			[] ()
			{
				m_instance.reset(new Type());
			}
		);
		return *m_instance;
	}

private:
	static std::unique_ptr<Type>	m_instance;
	static std::once_flag			m_onceFlag;
};

template <typename Type, typename DependantType> class CDependantSingleton
{
public:
	static Type& GetInstance()
	{
		std::call_once(m_onceFlag, 
			[] ()
			{
				m_instance.reset(new Type(DependantType::GetInstance()));
			}
		);
		return *m_instance;
	}

private:
	static std::unique_ptr<Type>	m_instance;
	static std::once_flag			m_onceFlag;
};

template <typename Type> std::unique_ptr<Type>	CSingleton<Type>::m_instance;
template <typename Type> std::once_flag			CSingleton<Type>::m_onceFlag;

template <typename Type, typename DependantType> std::unique_ptr<Type>	CDependantSingleton<Type, DependantType>::m_instance;
template <typename Type, typename DependantType> std::once_flag			CDependantSingleton<Type, DependantType>::m_onceFlag;
