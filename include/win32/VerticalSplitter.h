#ifndef _VERTICALSPLITTER_H_
#define _VERTICALSPLITTER_H_

#include "Splitter.h"

namespace Framework
{
	class CVerticalSplitter : public CSplitter
	{
	public:
						CVerticalSplitter(HWND, RECT*);

	protected:
		virtual void	GetEdgeRect(RECT*);
		virtual void	GetPaneRect(RECT*, unsigned int);
		virtual void	UpdateEdgePosition(int, int);
	};
}

#endif
