#include <assert.h>
#include "win32/DefaultFonts.h"

using namespace Framework;
using namespace Framework::Win32;

CFont CDefaultFonts::m_messageFont(CreateMessageFont());

HFONT CDefaultFonts::GetMessageFont()
{
	return m_messageFont;
}

void CDefaultFonts::GetNonClientMetrics(NONCLIENTMETRICS& metrics)
{
	memset(&metrics, 0, sizeof(NONCLIENTMETRICS));
	//SDK 6.0 is broken... so we need to do that to make it work on previous Windows versions
	metrics.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(metrics.iPaddedBorderWidth);

	assert(sizeof(NONCLIENTMETRICS) >= metrics.cbSize);

	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &metrics, 0);
}

HFONT CDefaultFonts::CreateMessageFont()
{
	NONCLIENTMETRICS metrics;
	GetNonClientMetrics(metrics);
	return CreateFontIndirect(&metrics.lfMessageFont);
}
