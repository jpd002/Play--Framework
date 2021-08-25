#include "Url.h"
#include "string_format.h"
#include <set>

std::string Framework::UrlEncode(const std::string& input)
{
	static const std::set<char> allowedSymbols = {'-', '_', '.', '~', '/'};

	std::string result;
	for(auto inputChar : input)
	{
		if(isalnum(inputChar) || allowedSymbols.find(inputChar) != allowedSymbols.end())
		{
			result += inputChar;
		}
		else
		{
			result += string_format("%%%02X", inputChar);
		}
	}
	return result;
}
