#include "StringUtilsTest.h"
#include "StringUtils.h"
#include <string>
#include <cassert>

std::string StringUtils_Replace(std::string inputString, const std::string& replace, const std::string& replaceWith)
{
	StringUtils::replace_all(inputString, replace, replaceWith);
	return inputString;
}

std::string StringUtils_Trim(std::string inputString)
{
	StringUtils::trim(inputString);
	return inputString;
}

std::string StringUtils_TrimStart(std::string inputString)
{
	StringUtils::ltrim(inputString);
	return inputString;
}

std::string StringUtils_TrimEnd(std::string inputString)
{
	StringUtils::rtrim(inputString);
	return inputString;
}

std::vector<std::string> StringUtils_Split(std::string inputString, char delimiter, bool trim)
{
	std::vector<std::string> result;
	StringUtils::split(result, inputString, delimiter, trim);
	return result;
}

void StringUtilsTest_Execute()
{
	assert(StringUtils_Replace("123", "2", "3") == "133");
	assert(StringUtils_Replace("123", "23", "1") == "11");
	assert(StringUtils_Replace("123232323", "23", "4") == "14444");

	assert(StringUtils_Trim("") == "");
	assert(StringUtils_Trim("   ") == "");
	assert(StringUtils_Trim("   test") == "test");
	assert(StringUtils_Trim("test   ") == "test");
	assert(StringUtils_Trim("   test test   ") == "test test");

	assert(StringUtils_TrimStart("") == "");
	assert(StringUtils_TrimStart("   ") == "");
	assert(StringUtils_TrimStart("   test") == "test");
	assert(StringUtils_TrimStart("test   ") == "test   ");
	assert(StringUtils_TrimStart("   test test   ") == "test test   ");

	assert(StringUtils_TrimEnd("") == "");
	assert(StringUtils_TrimEnd("   ") == "");
	assert(StringUtils_TrimEnd("   test") == "   test");
	assert(StringUtils_TrimEnd("test  ") == "test");
	assert(StringUtils_TrimEnd("   test test   ") == "   test test");
	
	{
		auto result = StringUtils_Split("1, 2, 3, 4, 5, 6   ", ',', false);
		assert(result.size() == 6);
		assert(result[1] == " 2");
	}
	
	{
		auto result = StringUtils_Split("1, 2, 3, 4, 5, 6   ", ',', true);
		assert(result.size() == 6);
		assert(result[5] == "6");
	}
}
