#ifndef _REGISTRYVALUE_H_
#define _REGISTRYVALUE_H_

#include "win32/Window.h"
#include "win32/RegistryTraits.h"

namespace Framework
{
	namespace Win32
	{
		template <typename CharType, typename Traits = CRegistryTraits<CharType> > class CBasicRegistryValue
		{
		public:
			CBasicRegistryValue(HKEY hKey, const CharType* sSubKey, const CharType* sValue)
			{
				HKEY nKey;
				DWORD nLength;
				CharType* sBuffer;

				Traits::CreateKey(hKey, sSubKey, &nKey);
				Traits::QueryValueEx(nKey, sValue, NULL, NULL, NULL, &nLength);
				
				if(nLength != 0)
				{
					sBuffer = reinterpret_cast<CharType*>(_alloca(nLength));
					Traits::QueryValueEx(nKey, sValue, NULL, NULL, reinterpret_cast<BYTE*>(sBuffer), &nLength);

					m_sValue = sBuffer;
				}
				else
				{
					m_sValue = _T("");
				}

				RegCloseKey(nKey);
			}

			virtual ~CBasicRegistryValue()
			{
				
			}

			operator const CharType*() const
			{
				return m_sValue.c_str();
			}

			std::basic_string<CharType> m_sValue;

		};

		typedef CBasicRegistryValue<TCHAR> CRegistryValue;
	}
}

#endif
