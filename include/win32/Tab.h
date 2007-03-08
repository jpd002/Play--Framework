#ifndef _TAB_H_
#define _TAB_H_

#include "win32/Window.h"
#include <commctrl.h>

namespace Framework
{
    namespace Win32
    {
        class CTab : public CWindow
        {
        public:
                            CTab(HWND, RECT*, unsigned long = 0, unsigned long = 0);
            virtual         ~CTab();

            int             InsertTab(const TCHAR*);
            int             GetSelection();
            unsigned int    GetItemCount();
            RECT            GetDisplayAreaRect();

        private:

        };
    }
}

#endif
