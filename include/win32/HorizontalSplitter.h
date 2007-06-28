#ifndef _HORIZONTALSPLITTER_H_
#define _HORIZONTALSPLITTER_H_

#include "Splitter.h"

namespace Framework
{
	class CHorizontalSplitter : public CSplitter
	{
	public:
						CHorizontalSplitter(HWND, RECT*);

	protected:
		virtual void	GetEdgeRect(RECT*);
		virtual void	GetPaneRect(RECT*, unsigned int);
		virtual void	UpdateEdgePosition(int, int);
	};
}

#endif
