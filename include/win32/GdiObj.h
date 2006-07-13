#ifndef _GDIOBJ_H_
#define _GDIOBJ_H_

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		template <typename Type> class CGdiObj
		{
		public:
			CGdiObj(Type nHandle)
			{
				m_nHandle = nHandle;
			}

			virtual ~CGdiObj()
			{
				DeleteObject(m_nHandle);
			}

			operator HGDIOBJ()
			{
				return m_nHandle;
			}

			operator Type()
			{
				return m_nHandle;
			}

		private:
			Type		m_nHandle;
		};

		typedef CGdiObj<HFONT>		CFont;
		typedef CGdiObj<HBRUSH>		CBrush;
		typedef CGdiObj<HBITMAP>	CBitmap;
		typedef CGdiObj<HPEN>		CPen;
	}
}

#endif
