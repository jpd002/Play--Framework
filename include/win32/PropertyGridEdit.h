#pragma once

#include "win32/Edit.h"
#include <boost/signals2.hpp>

namespace Framework
{
	namespace Win32
	{
		class CPropertyGridEdit : public CEdit
		{
		public:
			typedef boost::signals2::signal<void (bool)> EditCompletedEvent;

								CPropertyGridEdit(HWND);
			virtual				~CPropertyGridEdit();

			EditCompletedEvent	EditCompleted;

		protected:
			LRESULT				OnWndProc(UINT, WPARAM, LPARAM) override;

		private:

		};
	}
}
