#include <string>
#include <malloc.h>
//#include <alloca.h>
#include "string_cast.h"

using namespace std;

template <>
string string_cast<string>(const wchar_t* sSource)
{
	char* sConvert;
	size_t nSize;

	nSize = wcslen(sSource) + 1;
	sConvert = (char*)alloca(nSize);
	wcstombs(sConvert, sSource, nSize);

	return string(sConvert);	
}

template <>
wstring string_cast<wstring>(const char* sSource)
{
	size_t nSize;
	wchar_t* sConvert;

	nSize = strlen(sSource) + 1;
	sConvert = (wchar_t*)alloca(nSize * sizeof(wchar_t));

	mbstowcs(sConvert, sSource, nSize);

	return wstring(sConvert);
}

template <>
wstring string_cast<wstring>(const wchar_t* sSource)
{
	return wstring(sSource);
}

template <>
string string_cast<string>(const wstring& sSource)
{
	return string_cast<string, const wchar_t*>(sSource.c_str());
}

template <>
wstring string_cast<wstring>(const string& sSource)
{
	return string_cast<wstring, const char*>(sSource.c_str());
}
