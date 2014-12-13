#pragma once

#include <boost/signals2.hpp>
#include "win32/ListBox.h"

namespace Framework
{
	namespace Win32
	{
		class CPropertyGridListBox : public Framework::Win32::CListBox
		{
		public:
			typedef boost::signals2::signal<void (unsigned int)> StartEditionEvent;

								CPropertyGridListBox(HWND);
			virtual				~CPropertyGridListBox();

			StartEditionEvent	StartEdition;

		protected:
			long				OnWndProc(UINT, WPARAM, LPARAM) override;
			long				OnLeftButtonDown(int, int) override;
			long				OnLeftButtonUp(int, int) override;
		};
	}
}
