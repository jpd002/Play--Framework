#include "string_cast_win1252.h"
#include "alloca_def.h"
#ifdef _WIN32
#include <windows.h>
#elif defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#else
#include <unicode/ucnv.h>
#endif

std::wstring string_cast_win1252(const std::string& input)
{
#ifdef _WIN32
	UINT codePage = 1252;
	int reqLength = MultiByteToWideChar(codePage, 0, input.c_str(), input.length(), NULL, 0);
	wchar_t* output = reinterpret_cast<wchar_t*>(alloca((reqLength + 1) * sizeof(wchar_t)));
	MultiByteToWideChar(codePage, 0, input.c_str(), input.length(), output, reqLength);
	output[reqLength] = 0;
	return std::wstring(output);
#elif defined(__APPLE__)
	assert(sizeof(wchar_t) == 4);
	CFStringEncoding srcEncoding = kCFStringEncodingWindowsLatin1;
	CFStringEncoding dstEncoding = kCFStringEncodingUTF32;
	CFStringRef stringRef = CFStringCreateWithBytes(NULL, reinterpret_cast<const UInt8*>(input.c_str()), input.length(), srcEncoding, false);
	if(stringRef == NULL)
	{
		return std::wstring(L"(cast failed)");
	}
	CFIndex length = CFStringGetLength(stringRef);
	CFIndex bufferSize = length * sizeof(wchar_t);
	wchar_t* output = reinterpret_cast<wchar_t*>(alloca((length + 1) * sizeof(wchar_t)));
	CFRange getRange = { 0, length };
	CFStringGetBytes(stringRef, getRange, dstEncoding, '?', false, reinterpret_cast<UInt8*>(output), bufferSize, NULL);
	output[length] = 0;
	CFRelease(stringRef);
	return std::wstring(output);
#else
	assert(0);
#endif
}
