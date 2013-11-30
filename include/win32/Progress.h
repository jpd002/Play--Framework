#pragma once

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		class CProgress : public CWindow
		{
		public:
							CProgress(HWND = 0);

			CProgress&		operator =(CProgress&&);

			void			SetState(uint32);
			void			SetPosition(uint32);
			void			SetRange(uint32, uint32);
		};
	}
}
