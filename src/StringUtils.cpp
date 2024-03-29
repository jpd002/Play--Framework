#include "StringUtils.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iostream>

std::string StringUtils::ReplaceAll(const std::string& str, const std::string replace, const std::string replaceWith)
{
	std::string ret = str;
	std::string::size_type pos = 0;
	while((pos = ret.find(replace, pos)) != std::string::npos)
	{
		ret = ret.substr(0, pos)
		+ replaceWith
		+ ret.substr(pos + replace.size());
		pos += replaceWith.size();
	}
	return ret;
}

std::string StringUtils::EraseAll(const std::string& str, const std::string remove)
{
	return StringUtils::ReplaceAll(str, remove, "");
}

std::string StringUtils::TrimStart(const std::string& str)
{
	std::string ret = str;
	auto itr = ret.begin();
	while(itr != ret.end() && std::isspace((*itr)))
	{
		++itr;
	}
	ret.erase(ret.begin(), itr);
	return ret;
}

std::string StringUtils::TrimEnd(const std::string& str)
{
	std::string ret = str;
	auto itr = ret.rbegin();
	while(itr != ret.rend() && std::isspace((*itr)))
	{
		++itr;
	}
	ret.erase(itr.base(), ret.end());
	return ret;
}

std::string StringUtils::Trim(const std::string& str)
{
	std::string ret = str;
	ret = TrimStart(ret);
	ret = TrimEnd(ret);
	return ret;
}

// split function based on https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
std::vector<std::string> StringUtils::Split(const std::string& s, char delimiter, bool trim)
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
			tokens[i] = StringUtils::Trim(tokens[i]);
		}
	}
	return tokens;
}

std::string StringUtils::Join(const std::vector<std::string>& strings, const std::string& delimiter)
{
	std::string result;
	for(int i = 0; i < strings.size(); i++)
	{
		result += strings[i];
		if(i != strings.size() - 1)
		{
			result += delimiter;
		}
	}
	return result;
}

std::string StringUtils::ToLower(const std::string& str)
{
	std::string ret = str;
	std::transform(ret.begin(), ret.end(), ret.begin(), [](auto c) { return std::tolower(c); });
	return ret;
}
