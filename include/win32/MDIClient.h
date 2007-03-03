#ifndef _MDICLIENT_H_
#define _MDICLIENT_H_

#include "Window.h"

namespace Framework
{
    namespace Win32
    {
	    class CMDIClient : public CWindow
	    {
	    public:
					    CMDIClient(HWND, HMENU);
					    ~CMDIClient();
		    void        Cascade();
		    void        TileHorizontal();
		    void        TileVertical();
            HWND        GetActiveWindow();
	    };
    }
}

#endif