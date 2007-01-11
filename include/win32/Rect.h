#ifndef _RECT_H_
#define _RECT_H_

#include "Window.h"

namespace Framework
{
	namespace Win32
	{
		class CRect
		{
		public:
						CRect(int, int, int, int);
			virtual		~CRect();

						operator RECT*();

		private:
			RECT		m_Rect;
		};
	}
}

#endif
