#pragma once

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
			virtual CRect	GetEdgeRect() override;
			virtual CRect	GetPaneRect(unsigned int) override;
			virtual void	UpdateEdgePosition(int, int) override;
		};
	}
}
