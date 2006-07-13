#ifndef _LAYOUTWINDOW_H_
#define _LAYOUTWINDOW_H_

#include "Window.h"
#include "LayoutObject.h"

namespace Framework
{

	class CLayoutWindow : public CLayoutObject
	{
	public:
								CLayoutWindow(unsigned int, unsigned int, unsigned int, unsigned int, CWindow*, bool = true);
		virtual					~CLayoutWindow();

		static CLayoutWindow*	CreateButtonBehavior(unsigned int, unsigned int, CWindow*);
		static CLayoutWindow*	CreateTextBoxBehavior(unsigned int, unsigned int, CWindow*);

		unsigned int			GetPreferredWidth();
		unsigned int			GetPreferredHeight();
		void					RefreshGeometry();

	private:
		CWindow*				m_pWindow;
		unsigned int			m_nPrefWidth;
		unsigned int			m_nPrefHeight;
		bool					m_nUseNoCopy;

	};

}


#endif
