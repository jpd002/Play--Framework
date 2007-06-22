#ifndef _RICHTEXTEDIT_H_
#define _RICHTEXTEDIT_H_

#include "win32/Window.h"
#include <richedit.h>

namespace Framework
{
    namespace Win32
    {
        class CRichTextEdit : public CWindow
        {
        public:
                        CRichTextEdit(HWND, const RECT&, DWORD, DWORD);
            virtual     ~CRichTextEdit();

            void        SetSelection(int, int);
            void        SetSelectionAsLink(bool = true);
            void        SetEventMask(unsigned int);

        private:

        };

    }
}

#endif
