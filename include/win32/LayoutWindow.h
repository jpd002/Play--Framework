#ifndef _LAYOUTWINDOW_H_
#define _LAYOUTWINDOW_H_

#include "Window.h"
#include "layout/LayoutObject.h"

namespace Framework
{
    namespace Win32
    {
        class CLayoutWindow : public CLayoutObject
        {
        public:
            virtual                 ~CLayoutWindow();

            static LayoutObjectPtr  CreateButtonBehavior(unsigned int, unsigned int, CWindow*);
            static LayoutObjectPtr  CreateTextBoxBehavior(unsigned int, unsigned int, CWindow*);
            static LayoutObjectPtr  CreateCustomBehavior(unsigned int, unsigned int, unsigned int, unsigned int, CWindow*, bool = true);

            unsigned int            GetPreferredWidth();
            unsigned int            GetPreferredHeight();
            void                    RefreshGeometry();

        private:
				                    CLayoutWindow(unsigned int, unsigned int, unsigned int, unsigned int, CWindow*, bool = true);

            CWindow*                m_pWindow;
            unsigned int            m_nPrefWidth;
            unsigned int            m_nPrefHeight;
            bool                    m_nUseNoCopy;

	    };
    }
}


#endif
