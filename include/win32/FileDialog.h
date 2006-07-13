#ifndef _FILEDIALOG_H_
#define _FILEDIALOG_H_

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		class CFileDialog
		{
		public:
							CFileDialog();
							~CFileDialog();
			int				Summon(HWND);
			OPENFILENAME	m_OFN;
			xchar			m_sFile[MAX_PATH];

		private:

		};
	}
}

#endif