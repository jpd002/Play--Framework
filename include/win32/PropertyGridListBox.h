#pragma once

#include "win32/ListBox.h"
#include "signal/Signal.h"

namespace Framework
{
	namespace Win32
	{
		class CPropertyGridListBox : public Framework::Win32::CListBox
		{
		public:
			typedef CSignal<void (unsigned int)> StartEditionEvent;

								CPropertyGridListBox(HWND);
			virtual				~CPropertyGridListBox();

			StartEditionEvent	StartEdition;

		protected:
			LRESULT				OnWndProc(UINT, WPARAM, LPARAM) override;
			long				OnLeftButtonDown(int, int) override;
			long				OnLeftButtonUp(int, int) override;
		};
	}
}
