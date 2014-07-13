#pragma once

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		template <typename Type> class CGdiObj
		{
		public:
			CGdiObj(Type handle = NULL)
				: m_handle(handle)
			{

			}
			
			CGdiObj(const CGdiObj&) = delete;

			CGdiObj(CGdiObj&& src)
			{
				m_handle = src.m_handle;
				src.m_handle = NULL;
			}

			virtual ~CGdiObj()
			{
				Release();
			}

			CGdiObj& operator =(const CGdiObj&) = delete;

			CGdiObj& operator =(CGdiObj&& src)
			{
				if(&src != this)
				{
					Release();
					m_handle = src.m_handle;
					src.m_handle = NULL;
				}
				return (*this);
			}

			bool IsValid() const
			{
				return m_handle != NULL;
			}

			operator HGDIOBJ() const
			{
				return m_handle;
			}

			operator Type() const
			{
				return m_handle;
			}

		private:
			void Release()
			{
				if(m_handle)
				{
					DeleteObject(m_handle);
					m_handle = NULL;
				}
			}

			Type m_handle;
		};

		typedef CGdiObj<HFONT>		CFont;
		typedef CGdiObj<HBRUSH>		CBrush;
		typedef CGdiObj<HBITMAP>	CBitmap;
		typedef CGdiObj<HPEN>		CPen;
	}
}
