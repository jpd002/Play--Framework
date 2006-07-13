#ifndef _DEVICECONTEXT_H_
#define _DEVICECONTEXT_H_

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		class CDeviceContext
		{
		public:
							CDeviceContext(HDC);
			virtual			~CDeviceContext();
							operator HDC();

			unsigned int	GetFontHeight(HFONT);
			void			FillRect(RECT*, COLORREF);
			void			DrawLine(int, int, int, int);
			void			DrawLine(int, int, int, int, COLORREF);
			void			TextOut(int, int, const xchar*);

		protected:
			HDC				m_nDC;
		};
	}
}

#endif
