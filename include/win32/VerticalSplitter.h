#ifndef _VERTICALSPLITTER_H_
#define _VERTICALSPLITTER_H_

#include "win32/Splitter.h"

namespace Framework
{
    namespace Win32
    {
	    class CVerticalSplitter : public CSplitter
	    {
	    public:
						    CVerticalSplitter(HWND, const RECT&);

	    protected:
		    virtual void	GetEdgeRect(RECT*);
		    virtual void	GetPaneRect(RECT*, unsigned int);
		    virtual void	UpdateEdgePosition(int, int);
	    };
    }
}

#endif
