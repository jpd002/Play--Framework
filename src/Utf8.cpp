#include "Utf8.h"

using namespace std;
using namespace Framework;

wstring Utf8::ConvertFrom(const string& sString)
{
    return ConvertFrom(sString.begin(), sString.end());
}

wstring Utf8::ConvertFromSafe(const string& inputString)
{
	try
	{
		return ConvertFrom(inputString);
	}
	catch(...)
	{

	}
	return wstring();
}
