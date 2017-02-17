#include "string_cast_sjis.h"
#include "alloca_def.h"
#if defined(_WIN32)
#include <windows.h>
#elif defined(HAS_ICU)
#include <unicode/ucnv.h>
#endif

using namespace std;

wstring string_cast_sjis(const string& input)
{
#if defined(_WIN32)
	UINT codePage = 932;
	int reqLength = MultiByteToWideChar(codePage, 0, input.c_str(), input.length(), NULL, 0);
	wchar_t* output = reinterpret_cast<wchar_t*>(alloca((reqLength + 1) * sizeof(wchar_t)));
	MultiByteToWideChar(codePage, 0, input.c_str(), input.length(), output, reqLength);
	output[reqLength] = 0;
	return wstring(output);
#elif defined(HAS_ICU)
	int32_t length = static_cast<int32_t>(input.length());
	UErrorCode nStatus = U_ZERO_ERROR;
	UChar* output = reinterpret_cast<UChar*>(alloca(length * sizeof(UChar)));

	UConverter* pConverter = ucnv_open("shift_jis", &nStatus);
	ucnv_toUChars(pConverter, output, length, input.c_str(), length, &nStatus);
	ucnv_close(pConverter);

	return wstring(output, output + length);
#else
	return wstring(L"???");
#endif
}
