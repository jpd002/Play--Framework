#pragma once

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		class CSplitter : public CWindow
		{
		public:
							CSplitter(HWND, const RECT&, HCURSOR, unsigned int);
			virtual			~CSplitter();

			void			SetChild(unsigned int, HWND);
			void			SetMasterChild(unsigned int);

			void			SetEdgePosition(double);
			void			SetFixed(bool);

		protected:
			long			OnSize(unsigned int, unsigned int, unsigned int) override;
			long			OnMouseMove(WPARAM, int, int) override;
			long			OnLeftButtonDown(int, int) override;
			long			OnLeftButtonUp(int, int) override;
			LRESULT			OnNotify(WPARAM, NMHDR*) override;

			virtual CRect	GetPaneRect(unsigned int) = 0;
			virtual CRect	GetEdgeRect() = 0;
			virtual void	UpdateEdgePosition(int, int) = 0;

			unsigned int	m_edgePosition = 0;
			unsigned int	m_masterChild = 0;
			HWND			m_child[2];

			enum EDGESIZE
			{
				EDGESIZE = 4,
			};

		private:
			void			ResizeChild(unsigned int);

			HCURSOR			m_cursor;
			bool			m_fixed = false;
		};
	}
}
