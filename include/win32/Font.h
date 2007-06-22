#ifndef _FONT_H_
#define _FONT_H_

#include "win32/Window.h"

namespace Framework
{
    namespace Win32
    {
        HFONT CreateFont(const TCHAR*, unsigned int);
    }
}

#endif
