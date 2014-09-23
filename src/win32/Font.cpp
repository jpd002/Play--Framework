#include "win32/Font.h"
#include "win32/ClientDeviceContext.h"

using namespace Framework;

HFONT Win32::CreateFont(const TCHAR* faceName, unsigned int height)
{
	LOGFONT font;
	memset(&font, 0, sizeof(font));
	font.lfHeight			= -MulDiv(height, GetDeviceCaps(GetDC(NULL), LOGPIXELSY), 72);
	font.lfWidth			= 0;
	font.lfOrientation		= 0;
	font.lfWeight			= FW_NORMAL;
	font.lfItalic			= FALSE;
	font.lfUnderline		= FALSE;
	font.lfStrikeOut		= FALSE;
	font.lfCharSet			= DEFAULT_CHARSET;
	font.lfOutPrecision		= OUT_DEFAULT_PRECIS;
	font.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	font.lfQuality			= DEFAULT_QUALITY;
	font.lfPitchAndFamily	= DEFAULT_PITCH;
	_tcsncpy(font.lfFaceName, faceName, LF_FACESIZE);
	return CreateFontIndirect(&font);
}

SIZE Win32::GetFixedFontSize(HFONT font)
{
	Framework::Win32::CClientDeviceContext dc(NULL);

	dc.SelectObject(font);

	SIZE s = { 0, 0 };
	GetTextExtentPoint32(dc, _T("0"), 1, &s);
	return s;
}
