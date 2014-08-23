#pragma once

#include <Windows.h>
#include <assert.h>

namespace Framework
{
	namespace Win32
	{
		template <typename PtrType>
		class CComPtr
		{
		public:
			CComPtr()
			: m_ptr(nullptr)
			{

			}

			explicit CComPtr(PtrType* ptr)
			: m_ptr(ptr)
			{

			}

			CComPtr(const CComPtr& rhs)
			: m_ptr(nullptr)
			{
				CopyFrom(rhs);
			}

			CComPtr(CComPtr&& rhs)
			: m_ptr(nullptr)
			{
				MoveFrom(std::move(rhs));
			}

			~CComPtr()
			{
				Reset();
			}

			operator PtrType*()
			{
				return m_ptr;
			}

			operator PtrType*() const
			{
				return m_ptr;
			}

			operator PtrType**()
			{
				return &m_ptr;
			}

			CComPtr& operator =(const CComPtr& rhs)
			{
				if(&rhs != this)
				{
					Reset();
					CopyFrom(rhs);
				}
				return (*this);
			}

			CComPtr& operator =(CComPtr&& rhs)
			{
				Reset();
				MoveFrom(std::move(rhs));
				return (*this);
			}

			PtrType* operator ->() const
			{
				return m_ptr;
			}

			PtrType** operator &()
			{
				//Usually used for creation, must be empty
				assert(m_ptr == nullptr);
				return &m_ptr;
			}

			PtrType* Detach()
			{
				PtrType* result = m_ptr;
				m_ptr = nullptr;
				return result;
			}

			void Reset()
			{
				if(m_ptr != nullptr)
				{
					m_ptr->Release();
					m_ptr = nullptr;
				}
			}

			bool IsEmpty() const
			{
				return (m_ptr == nullptr);
			}

		private:
			void CopyFrom(const CComPtr& src)
			{
				assert(m_ptr == nullptr);
				m_ptr = src.m_ptr;
				if(m_ptr != nullptr)
				{
					m_ptr->AddRef();
				}
			}

			void MoveFrom(CComPtr&& src)
			{
				std::swap(m_ptr, src.m_ptr);
			}

			PtrType* m_ptr;
		};
	};
};
