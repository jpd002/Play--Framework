#ifndef _HORIZONTALSPLITTER_H_
#define _HORIZONTALSPLITTER_H_

#include "win32/Splitter.h"
#include "win32/Window.h"

namespace Framework
{
    namespace Win32
    {
	    class CHorizontalSplitter : public CSplitter
	    {
	    public:
						    CHorizontalSplitter(HWND, const RECT&);

	    protected:
		    virtual void	GetEdgeRect(RECT*);
		    virtual void	GetPaneRect(RECT*, unsigned int);
		    virtual void	UpdateEdgePosition(int, int);
	    };
    }
}

#endif
