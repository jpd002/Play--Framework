#ifndef _XCHAR_H_
#define _XCHAR_H_

#include "Str.h"
#include <string>

#define countof(a) (sizeof(a) / sizeof(a[0]))

#if (defined(WIN32) && defined(UNICODE))

//xchar == wchar_t support

#include <wchar.h>

typedef wchar_t xchar;

#define _X(x)		L ## x

#define XCHAR_IS_WCHAR

#define xprintf		wprintf
#define xsnprintf	swprintf
#define xvsnprintf	_vsnwprintf
#define xstrcpy		wcscpy
#define xstrncpy	wcsncpy
#define xstrlen		wcslen
#define xstrcat		wcscat
#define xsscanf		swscanf
#define xstrcmp		wcscmp
#define xstrchr		wcschr
#define xfopen		_wfopen

#else

typedef char xchar;

#define _X(x)		x

#define XCHAR_IS_CHAR

#define xprintf		printf
#define	xsprintf	sprintf
#define xsnprintf	_snprintf
#define xvsnprintf	_vsnprintf
#define xstrcpy		strcpy
#define xstrncpy	strncpy
#define xstrlen		strlen
#define xstrcat		strcat
#define xsscanf		sscanf
#define xstrcmp		strcmp
#define xstrchr		strchr
#define xfopen		fopen

#endif

#ifdef XCHAR_IS_WCHAR

void			xconvert(wchar_t*, const char*, size_t);
void			xconvert(char*, const wchar_t*, size_t);
void			xconvert(wchar_t*, const wchar_t*, size_t);
const wchar_t*	xcond(const char*, const wchar_t*);

#else if XCHAR_IS_CHAR

void			xconvert(char*, const char*, size_t);
const char*		xcond(const char*, const wchar_t*);

#endif

namespace Framework
{
	typedef CStr<xchar> CStrX;
};

namespace std
{
	typedef basic_string< xchar, char_traits<xchar>, allocator<xchar> > xstring;
};

#endif
