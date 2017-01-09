#ifndef _COLUMNTREEVIEW_H_
#define _COLUMNTREEVIEW_H_

#include "win32/TreeView.h"
#include "win32/Header.h"
#include "win32/DblBufferedCtrl.h"

namespace Framework
{

	namespace Win32
	{

		class CColumnTreeView : public CWindow
		{
		public:
			struct MESSAGE : public NMHDR
			{
				NMHDR* pOriginalMsg;
			};
											CColumnTreeView(HWND, const RECT&, unsigned long = 0);
			virtual							~CColumnTreeView();
			CHeader*						GetHeader();
			CTreeView*						GetTreeView();

		protected:
			long							OnSize(unsigned int, unsigned int, unsigned int);
			long							OnEraseBkgnd() override;
			LRESULT							OnNotify(WPARAM, NMHDR*) override;

		private:
			void							UpdateLayout();
			void							ComputeHeaderHeight();
			void							DrawColumnLines(HDC);
			void							DrawItem(NMTVCUSTOMDRAW*);

			unsigned int					m_nHeaderHeight;
			CDblBufferedCtrl<CTreeView>*	m_pTreeView;
			CHeader*						m_pHeader;
		};

	}

}

#endif
