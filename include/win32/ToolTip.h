#ifndef _TOOLTIP_H_
#define _TOOLTIP_H_

#include "win32/Window.h"
#include <commctrl.h>

namespace Framework
{
    namespace Win32
    {
	    class CToolTip : public CWindow
	    {
	    public:
						    CToolTip(HWND);
		    void			Activate(bool);
            void            TrackActivate(unsigned int, bool);
            void            TrackPosition(int, int);
            void			AddTool(HWND, const TCHAR*);
		    unsigned int	AddTool(const RECT&, const TCHAR*);
            unsigned int    AddTrackTool(const TCHAR*);
            unsigned int	GetToolCount();
            void            SetToolText(UINT_PTR, const TCHAR*);
		    void			DeleteTool(unsigned int);
		    void			DeleteAllTools();

	    private:
            TOOLINFO        GetTool(UINT_PTR);
		    HWND			m_hParent;
	    };
    }
}

#endif
