#ifndef _CUSTOMDRAWN_H_
#define _CUSTOMDRAWN_H_

#include "win32/Window.h"

namespace Framework
{
    namespace Win32
    {
        class CCustomDrawn : public CWindow
        {
	    protected:
                            CCustomDrawn();
            virtual         ~CCustomDrawn();
            virtual void    Paint(HDC) = 0;
            virtual long    OnEraseBkgnd();
            virtual long    OnPaint();
            virtual long    OnSize(unsigned int, unsigned int, unsigned int);

        private:
            void            RecreateBitmap(HDC);
            void            InvalidateBitmap();
            HBITMAP         m_Bitmap;
            HDC             m_MemDc;
	    };
    }
}

#endif