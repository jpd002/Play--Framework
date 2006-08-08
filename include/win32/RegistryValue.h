#ifndef _REGISTRYVALUE_H_
#define _REGISTRYVALUE_H_

#include "win32/Window.h"

namespace Framework
{
	namespace Win32
	{
		class CRegistryValue
		{
		public:
							CRegistryValue(HKEY, const TCHAR*, const TCHAR*);
			virtual			~CRegistryValue();

							operator const TCHAR*();

		private:
			std::tstring	m_sValue;
		};
	}
}

#endif
