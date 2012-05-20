#ifndef _MODALWINDOW_H_
#define _MODALWINDOW_H_

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		class CModalWindow : public virtual CWindow
		{
		public:
							CModalWindow(HWND);
			virtual			~CModalWindow();
			void			DoModal();

		protected:
			virtual void	OnEscPressed();

			unsigned int	Destroy();
			long			OnSysCommand(unsigned int, LPARAM);
			void			UnModalWindow();
		};
	}
}

#endif
