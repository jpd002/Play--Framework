#include <assert.h>
#include "win32/DefaultFonts.h"

using namespace Framework;
using namespace Framework::Win32;

CFont CDefaultFonts::m_MessageFont(CreateMessageFont());

HFONT CDefaultFonts::GetMessageFont()
{
	return m_MessageFont;
}

HFONT CDefaultFonts::CreateMessageFont()
{
	NONCLIENTMETRICS Metrics;
	memset(&Metrics, 0, sizeof(NONCLIENTMETRICS));
    //SDK 6.0 is broken... so we need to do that
//	Metrics.cbSize = sizeof(NONCLIENTMETRICS);
    Metrics.cbSize = 500;

    assert(sizeof(NONCLIENTMETRICS) >= Metrics.cbSize);

	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &Metrics, 0);
	return CreateFontIndirect(&Metrics.lfMessageFont);
}
