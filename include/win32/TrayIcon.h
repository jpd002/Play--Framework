#pragma once

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		class CTrayIcon
		{
		public:
							CTrayIcon(HWND, unsigned int);
			virtual			~CTrayIcon();

			void			SetTip(const TCHAR*);
			void			SetIcon(HICON);
			void			SetMessage(unsigned int);
			unsigned int	GetID() const;
			void			Rebuild();

		private:
			void			Add();
			void			Delete();
			void			InitStructure(NOTIFYICONDATA*);

			std::tstring	m_tip;
			HICON			m_icon;
			unsigned int	m_message;

			HWND			m_wnd;
			unsigned int	m_id;
		};
	}
}
