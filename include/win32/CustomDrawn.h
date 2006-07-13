#ifndef _CUSTOMDRAWN_H_
#define _CUSTOMDRAWN_H_

#include "win32/Window.h"

namespace Framework
{
	class CCustomDrawn : public CWindow
	{
	protected:
		virtual void	Paint(HDC) = 0;
		virtual long	OnEraseBkgnd();
		virtual long	OnPaint();
		virtual long	OnSize(unsigned int, unsigned int, unsigned int);
	};
}

#endif