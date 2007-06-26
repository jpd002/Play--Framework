#ifndef _TOOLTIP_H_
#define _TOOLTIP_H_

#include "win32/Window.h"

namespace Framework
{
	class CToolTip : public CWindow
	{
	public:
						CToolTip(HWND);
		void			Activate(BOOL);
		void			AddTool(HWND, const xchar*);
		void			AddTool(RECT*, const xchar*);
		unsigned int	GetToolCount();
		void			DeleteTool(unsigned int);
		void			DeleteAllTools();

	private:
		HWND			m_hParent;
	};
}

#endif
