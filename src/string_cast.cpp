#include <string>
#include <stdlib.h>
#include "string_cast.h"

using namespace std;

template <>
string string_cast<string>(const wchar_t* src)
{
	unsigned int maxCharSize = MB_CUR_MAX;

	size_t srcSize = wcslen(src);
	char* dst = reinterpret_cast<char*>(alloca((srcSize * maxCharSize) + 1));
	char* dstPtr = dst;
	for(unsigned int i = 0; i < srcSize; i++)
	{
		int charSize = wctomb(dstPtr, src[i]);
		if(charSize < 0)
		{
			(*dstPtr) = '?';
			dstPtr++;
		}
		else
		{
			dstPtr += charSize;
		}
	}
	(*dstPtr) = 0;

	return string(dst);
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
	return string_cast<string, wchar_t>(sSource.c_str());
}

template <>
string string_cast<string>(wchar_t* const& source)
{
	return string_cast<string, wchar_t>(source);
}

template <>
wstring string_cast<wstring>(const string& sSource)
{
	return string_cast<wstring, char>(sSource.c_str());
}

template <>
wstring string_cast<wstring>(const wstring& sSource)
{
	return sSource;
}
