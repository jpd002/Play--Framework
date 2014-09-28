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

			void			FillRect(RECT*, COLORREF);
			void			DrawLine(int, int, int, int);
			void			DrawLine(int, int, int, int, COLORREF);
			void			TextOut(int, int, const TCHAR*);
			void			TextOut(int, int, const TCHAR*, COLORREF);
			HGDIOBJ			SelectObject(HGDIOBJ);

		protected:
			HDC				m_dc;
		};
	}
}

#endif
