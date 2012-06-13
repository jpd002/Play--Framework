#include "win32/Font.h"

using namespace Framework;

HFONT Win32::CreateFont(const TCHAR* sFaceName, unsigned int nHeight)
{
	LOGFONT Font;
	memset(&Font, 0, sizeof(Font));
	Font.lfHeight			= -MulDiv(nHeight, GetDeviceCaps(GetDC(NULL), LOGPIXELSY), 72);
	Font.lfWidth			= 0;
	Font.lfOrientation		= 0;
	Font.lfWeight			= FW_NORMAL;
	Font.lfItalic			= FALSE;
	Font.lfUnderline		= FALSE;
	Font.lfStrikeOut		= FALSE;
	Font.lfCharSet			= OEM_CHARSET;
	Font.lfOutPrecision		= OUT_DEFAULT_PRECIS;
	Font.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	Font.lfQuality			= DEFAULT_QUALITY;
	Font.lfPitchAndFamily	= DEFAULT_PITCH;
	_tcsncpy(Font.lfFaceName, sFaceName, LF_FACESIZE);
	return CreateFontIndirect(&Font);
}
