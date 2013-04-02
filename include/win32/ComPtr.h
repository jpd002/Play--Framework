#pragma once

#include <Windows.h>
#include <boost/utility.hpp>

namespace Framework
{
	namespace Win32
	{
		template <typename PtrType>
		class CComPtr : public boost::noncopyable
		{
		public:
			CComPtr()
			: m_ptr(nullptr)
			{

			}

			~CComPtr()
			{
				if(m_ptr)
				{
					m_ptr->Release();
				}
			}

			operator PtrType*()
			{
				return m_ptr;
			}

			operator PtrType**()
			{
				return &m_ptr;
			}

			PtrType* operator ->()
			{
				return m_ptr;
			}

			PtrType** operator &()
			{
				return &m_ptr;
			}

			PtrType* Detach()
			{
				PtrType* result = m_ptr;
				m_ptr = nullptr;
				return result;
			}

			bool IsEmpty() const
			{
				return (m_ptr == nullptr);
			}

		private:
			PtrType*		m_ptr;
		};
	};
};
