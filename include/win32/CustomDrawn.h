#pragma once

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		class CCustomDrawn : public virtual CWindow
		{
		protected:
							CCustomDrawn();
			virtual			~CCustomDrawn();

			virtual void	Paint(HDC) = 0;

			virtual long	OnEraseBkgnd() override;
			virtual long	OnPaint() override;
			virtual long	OnSize(unsigned int, unsigned int, unsigned int) override;

		private:
			void			RecreateBitmap(HDC);
			void			InvalidateBitmap();
			HBITMAP			m_Bitmap;
			HDC				m_MemDc;
		};
	}
}
