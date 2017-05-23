#pragma once

#include <Windows.h>
#include <WinInet.h>

namespace Framework
{
	namespace Win32
	{
		class CInternetHandle
		{
		public:
			CInternetHandle(HINTERNET handle)
				: m_handle(handle)
			{

			}

			CInternetHandle(const CInternetHandle&) = delete;

			CInternetHandle(CInternetHandle&&);

			~CInternetHandle()
			{
				Reset();
			}

			CInternetHandle& operator =(const CInternetHandle&) = delete;

			CInternetHandle& operator =(CInternetHandle&&);

			bool IsEmpty() const
			{
				return m_handle == NULL;
			}

			void Reset()
			{
				if(m_handle != NULL)
				{
					InternetCloseHandle(m_handle);
					m_handle = NULL;
				}
			}

			operator HINTERNET() const
			{
				return m_handle;
			}

		private:
			HINTERNET m_handle = NULL;
		};
	}
}
