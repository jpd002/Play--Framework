#ifndef _DEFAULTFONTS_H_
#define _DEFAULTFONTS_H_

#include "GdiObj.h"

namespace Framework
{
	namespace Win32
	{
		class CDefaultFonts
		{
		public:
			static HFONT		GetMessageFont();
			static void			GetNonClientMetrics(NONCLIENTMETRICS&);

		private:
			static HFONT		CreateMessageFont();
			static CFont		m_messageFont;
		};
	}
}

#endif
