#ifndef _SCROLLBAR_H_
#define _SCROLLBAR_H_

#include <windows.h>

namespace Framework
{
    namespace Win32
    {
        class CScrollBar
        {
        public:
                        CScrollBar(HWND, int);
            virtual     ~CScrollBar();
            
            int         GetPosition() const;
            int         GetThumbPosition() const;

            void        SetPosition(int);
            void        SetRange(int, int);

        private:
            HWND        m_hWnd;
            int         m_nBar;
        };
    }
};

#endif
