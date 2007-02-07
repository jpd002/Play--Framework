#ifndef _TRAYICON_H_
#define _TRAYICON_H_

#include "win32/Window.h"

namespace Framework
{
    namespace Win32
    {
	    class CTrayIcon
	    {
	    public:
						    CTrayIcon(HWND, unsigned int);
						    ~CTrayIcon();
		    void			SetTip(TCHAR*);
		    void			SetIcon(HICON);
		    void			SetMessage(unsigned int);
		    unsigned int	GetID();
	    private:
		    void			Add();
		    void			Delete();
		    void			InitStructure(NOTIFYICONDATA*);
		    HWND			m_hWnd;
		    unsigned int	m_nID;
	    };
    }
}


#endif
