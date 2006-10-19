#ifndef _REGISTRYTRAITS_H_
#define _REGISTRYTRAITS_H_

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		template <typename CharType> class CRegistryTraits
		{
		public:
			static LONG CreateKey(HKEY, const CharType*, PHKEY);
			static LONG QueryValueEx(HKEY, const CharType*, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
			
		private:

		};
	}
}

#endif
