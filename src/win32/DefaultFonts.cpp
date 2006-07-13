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
	Metrics.cbSize = sizeof(NONCLIENTMETRICS);

	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &Metrics, 0);
	return CreateFontIndirect(&Metrics.lfMessageFont);
}
