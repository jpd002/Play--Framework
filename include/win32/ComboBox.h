#pragma once

#include "Window.h"
#include "Types.h"

namespace Framework
{
	namespace Win32
	{
		class CComboBox : public CWindow
		{
		public:
							CComboBox(HWND = 0);
							CComboBox(HWND, const RECT&, unsigned long = 0);
			
			CComboBox&		operator =(CComboBox&&);

			unsigned int	AddString(const TCHAR*);
			int				GetSelection();
			void			SetSelection(int);
			unsigned int	GetItemCount();
			void			SetItemData(unsigned int, uint32);
			uint32			GetItemData(unsigned int);
			int				FindItemData(uint32);
			void			FixHeight(unsigned int);
			void			ResetContent();
		};
	}
}
