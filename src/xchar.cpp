#include <string.h>
#include <stdlib.h>
#include "xchar.h"

#ifdef XCHAR_IS_WCHAR

void xconvert(wchar_t* pDst, const char* pSrc, size_t nCount)
{
	mbstowcs(pDst, pSrc, nCount);
}

void xconvert(wchar_t* pDst, const wchar_t* pSrc, size_t nCount)
{
	wcsncpy(pDst, pSrc, nCount);
}

void xconvert(char* pDst, const wchar_t* pSrc, size_t nCount)
{
	wcstombs(pDst, pSrc, nCount);
}

const wchar_t* xcond(const char* pChar, const wchar_t* pWide)
{
	return pWide;
}

#else if XCHAR_IS_CHAR

void xconvert(char* pDst, const char* pSrc, size_t nCount)
{
	strncpy(pDst, pSrc, nCount);
}

const char* xcond(const char* pChar, const wchar_t* pWide)
{
	return pChar;
}

#endif
