#include "StringUtils.h"
#include <algorithm>
#include <sstream>

void StringUtils::replace_all(std::string& str, const std::string replace, std::string replaceWith)
{
	auto str2 = str;
	std::string::size_type pos = 0;
	while((pos = str2.find(replace, pos)) != std::string::npos)
	{
		str2 = str2.substr(0, pos)
		+ replaceWith
		+ str2.substr(pos + replace.size());
		pos += replaceWith.size();
	}
	str.clear();
	str += str2;
}

void StringUtils::erase_all(std::string& str, std::string remove)
{
	StringUtils::replace_all(str, remove, "");
}

// split function based on https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
void StringUtils::split(std::vector<std::string>& ret, const std::string& s, char delimiter, bool trim)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	if(trim)
	{
		for(int i = 0; i < tokens.size(); i++)
		{
			std::remove_if(tokens[i].begin(), tokens[i].end(), isspace);
		}
	}
	ret.insert(ret.end(), tokens.begin(), tokens.end());
}
