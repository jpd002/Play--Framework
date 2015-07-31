#ifndef _STRICMP_H_
#define _STRICMP_H_

#ifdef WIN32
#define stricmp _stricmp
#define strnicmp _strnicmp
#define wcsicmp _wcsicmp
#else
#include <strings.h> // POSIX
#define stricmp strcasecmp
#define strnicmp strncasecmp
#define wcsicmp wcscasecmp
#endif

#endif
