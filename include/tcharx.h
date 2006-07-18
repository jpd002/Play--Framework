#ifndef _TCHARX_H_
#define _TCHARX_H_

#include <tchar.h>
#include <string>
#include <sstream>
#include "countof.h"

namespace std
{
	typedef basic_string< TCHAR, char_traits<TCHAR>, allocator<TCHAR> > tstring;
	typedef basic_stringstream< TCHAR, char_traits<TCHAR>, allocator<TCHAR> > tstringstream;
};

#endif
