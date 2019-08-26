#pragma once

#include "win32/Edit.h"
#include "signal/Signal.h"

namespace Framework
{
	namespace Win32
	{
		class CPropertyGridEdit : public CEdit
		{
		public:
			typedef CSignal<void (bool)> EditCompletedEvent;

								CPropertyGridEdit(HWND);
			virtual				~CPropertyGridEdit();

			EditCompletedEvent	EditCompleted;

		protected:
			LRESULT				OnWndProc(UINT, WPARAM, LPARAM) override;

		private:

		};
	}
}
