#ifndef _SPLITTER_H_
#define _SPLITTER_H_

#include "win32/CustomDrawn.h"

namespace Framework
{
	class CSplitter : public CCustomDrawn
	{
	public:
						CSplitter(HWND, RECT*, HCURSOR, unsigned int);
		virtual			~CSplitter();

		void			SetChild(unsigned int, HWND);
		void			SetEdgePosition(double);

	protected:
		long			OnSize(unsigned int, unsigned int, unsigned int);
		long			OnMouseMove(WPARAM, int, int);
		long			OnLeftButtonDown(int, int);
		long			OnLeftButtonUp(int, int);
		long			OnNotify(WPARAM, NMHDR*);

		virtual void	GetPaneRect(RECT*, unsigned int) = 0;
		virtual void	GetEdgeRect(RECT*) = 0;
		virtual void	UpdateEdgePosition(int, int) = 0;

		unsigned int	m_nEdgePosition;
		HWND			m_nChild[2];

		enum EDGESIZE
		{
			EDGESIZE = 4,
		};

	private:
		void			Paint(HDC);
		void			ResizeChild(unsigned int);

		HCURSOR			m_nCursor;
	};
}

#endif
