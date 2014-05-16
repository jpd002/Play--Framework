#pragma once

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
			virtual RECT	GetEdgeRect() override;
			virtual RECT	GetPaneRect(unsigned int) override;
			virtual void	UpdateEdgePosition(int, int) override;
		};
	}
}
