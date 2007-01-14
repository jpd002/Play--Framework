#ifndef _WIN32_TOOLBAR_H_
#define _WIN32_TOOLBAR_H_

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		class CToolBar : public CWindow
		{
		public:
						CToolBar(HWND, unsigned int, HINSTANCE, unsigned int, unsigned int, unsigned int);
						CToolBar(HWND);
			virtual		~CToolBar();

			void		LoadStandardImageList(unsigned int);
			void		InsertImageButton(unsigned int, unsigned int);
			void		InsertTextButton(const TCHAR*, unsigned int);
			void		Resize();

		private:

		};
	}
}

#endif
