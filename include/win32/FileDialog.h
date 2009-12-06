#ifndef _FILEDIALOG_H_
#define _FILEDIALOG_H_

#include "win32/Window.h"
#include <list>

namespace Framework
{
	namespace Win32
	{
		class CFileDialog
		{
		public:
            typedef std::list<std::tstring> PathList;

							CFileDialog(unsigned int bufferSize = MAX_PATH);
			virtual         ~CFileDialog();

            const TCHAR*    GetPath() const;
            PathList        GetMultiPaths() const;

			int				SummonOpen(HWND);
            int             SummonSave(HWND);

            OPENFILENAME	m_OFN;

		private:
            TCHAR*          m_sFile;
		};
	}
}

#endif
