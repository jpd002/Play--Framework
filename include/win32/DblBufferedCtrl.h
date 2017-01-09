#pragma once

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		template <typename Control>
		class CDblBufferedCtrl : public CWindow
		{
		public:
			CDblBufferedCtrl(Control* control)
			: m_control(control)
			{
				m_hWnd = m_control->m_hWnd;
				SubClass();
			}

			virtual ~CDblBufferedCtrl()
			{
				delete m_control;
			}

			Control* GetControl() const
			{
				return m_control;
			}

		protected:
			LRESULT OnWndProc(unsigned int nMsg, WPARAM wParam, LPARAM lParam) override
			{
				switch(nMsg)
				{
				case WM_ERASEBKGND:
					return FALSE;
					break;

				case WM_PAINT:
					{
						PAINTSTRUCT ps;
						HDC hWDC, hDC;
						RECT rwin;
						HBITMAP hBM;

						BeginPaint(m_hWnd, &ps);
						hWDC = ps.hdc;

						rwin = m_control->GetClientRect();

						hDC = CreateCompatibleDC(hWDC);
						hBM = CreateCompatibleBitmap(hWDC, rwin.right, rwin.bottom);
						SelectObject(hDC, hBM);

						CallWindowProc(m_baseWndProc, m_hWnd, WM_PRINT, (WPARAM)hDC, PRF_CLIENT | PRF_ERASEBKGND);

						BitBlt(hWDC, 0, 0, rwin.right, rwin.bottom, hDC, 0, 0, SRCCOPY);

						DeleteObject(hBM);
						DeleteDC(hDC);

						EndPaint(m_hWnd, &ps);

						return TRUE;
					}

					break;
				}

				return CallWindowProc(m_baseWndProc, m_hWnd, nMsg, wParam, lParam);
			}

		private:
			Control* m_control = nullptr;
		};
	}
}
