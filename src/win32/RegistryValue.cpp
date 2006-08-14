#include "win32/RegistryValue.h"

using namespace Framework;
using namespace Win32;
using namespace std;

CRegistryValue::CRegistryValue(HKEY hKey, const TCHAR* sSubKey, const TCHAR* sValue)
{
	HKEY nKey;
	DWORD nLength;
	TCHAR* sBuffer;

	RegCreateKey(hKey, sSubKey, &nKey);
	RegQueryValueEx(nKey, sValue, NULL, NULL, NULL, &nLength);
	
	if(nLength != 0)
	{
		sBuffer = reinterpret_cast<TCHAR*>(_alloca(nLength));
		RegQueryValueEx(nKey, sValue, NULL, NULL, reinterpret_cast<BYTE*>(sBuffer), &nLength);

		m_sValue = sBuffer;
	}
	else
	{
		m_sValue = _T("");
	}

	RegCloseKey(nKey);
}

CRegistryValue::~CRegistryValue()
{

}

CRegistryValue::operator const TCHAR*()
{
	return m_sValue.c_str();
}
