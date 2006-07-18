#include <string>
#include <malloc.h>
#include "string_cast.h"

using namespace std;

template <>
string string_cast<string>(const wchar_t* sSource)
{
	char* sConvert;
	size_t nSize;

	nSize = wcslen(sSource) + 1;
	sConvert = (char*)_alloca(nSize);
	wcstombs(sConvert, sSource, nSize);

	return string(sConvert);	
}

template <>
wstring string_cast<wstring>(const char* sSource)
{
	size_t nSize;
	wchar_t* sConvert;

	nSize = strlen(sSource) + 1;
	sConvert = (wchar_t*)_alloca(nSize * sizeof(wchar_t));

	mbstowcs(sConvert, sSource, nSize);

	return wstring(sConvert);
}

template <>
string string_cast<string>(const wstring& sSource)
{
	return string_cast<string>(sSource.c_str());
}

template <>
wstring string_cast<wstring>(const string& sSource)
{
	return string_cast<wstring>(sSource.c_str());
}
