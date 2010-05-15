#include "string_cast_win1252.h"
#include "alloca_def.h"
#ifdef WIN32
#include <windows.h>
#else
#include <unicode/ucnv.h>
#endif

using namespace std;

wstring string_cast_win1252(const string& input)
{
#ifdef WIN32
	UINT codePage = 1252;
	int reqLength = MultiByteToWideChar(codePage, 0, input.c_str(), input.length(), NULL, 0);
	wchar_t* output = reinterpret_cast<wchar_t*>(alloca((reqLength + 1) * sizeof(wchar_t)));
	MultiByteToWideChar(codePage, 0, input.c_str(), input.length(), output, reqLength);
	output[reqLength] = 0;
	return wstring(output);
#else
	assert(0);
#endif
}
