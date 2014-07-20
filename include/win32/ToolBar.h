#pragma once

#include <map>
#include "win32/Window.h"
#include <commctrl.h>

namespace Framework
{
	namespace Win32
	{
		class CToolBar : public CWindow
		{
		public:
								CToolBar();
								CToolBar(HWND, unsigned int, HINSTANCE, unsigned int, unsigned int, unsigned int);
								CToolBar(HWND, DWORD style = TBSTYLE_TOOLTIPS);
								CToolBar(const CToolBar&) = delete;
			virtual				~CToolBar();

			CToolBar&			operator =(CToolBar&&);
			CToolBar&			operator =(const CToolBar&) = delete;

			void				LoadStandardImageList(unsigned int);
			void				InsertImageButton(unsigned int, unsigned int);
			void				InsertTextButton(const TCHAR*, unsigned int);
			void				Resize();
			HWND				GetToolTips();
			void				SetButtonChecked(unsigned int, bool);
			void				SetButtonToolTipText(unsigned int, const TCHAR*);
			void				ProcessNotify(WPARAM, NMHDR*);

		private:
			typedef std::map<unsigned int, std::tstring> ButtonToolTipMap;

			void				Reset();
			void				MoveFrom(CToolBar&&);

			ButtonToolTipMap	m_buttonToolTips;
		};
	}
}
