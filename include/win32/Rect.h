#ifndef _RECT_H_
#define _RECT_H_

#include "Window.h"
#include "Types.h"

namespace Framework
{
	namespace Win32
	{
		class CRect
		{
		public:
						CRect(int, int, int, int);
                        CRect(RECT);
			virtual		~CRect();

						operator RECT*();
                        operator RECT&();

			CRect&		Adjust(uint32, bool = false);
            CRect&      Inflate(int, int);

		private:
			RECT		m_Rect;
		};
	}
}

#endif
