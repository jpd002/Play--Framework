#include "win32/RegistryTraits.h"

using namespace Framework::Win32;

/////////////////////////////////////
//char

template <> LONG CRegistryTraits<char>::CreateKey(HKEY hKey, const char* lpSubKey, PHKEY phkResult)
{
	return RegCreateKeyA(hKey, lpSubKey, phkResult);
}

template <> LONG CRegistryTraits<char>::QueryValueEx(HKEY hKey, const char* lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	return RegQueryValueExA(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
}

/////////////////////////////////////
//wchar_t

template <> LONG CRegistryTraits<wchar_t>::CreateKey(HKEY hKey, const wchar_t* lpSubKey, PHKEY phkResult)
{
	return RegCreateKeyW(hKey, lpSubKey, phkResult);
}

template <> LONG CRegistryTraits<wchar_t>::QueryValueEx(HKEY hKey, const wchar_t* lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	return RegQueryValueExW(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
}
