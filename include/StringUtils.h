#pragma once

#include <string>
#include <vector>

namespace StringUtils
{
	std::string ReplaceAll(const std::string&, const std::string, const std::string);
	std::string EraseAll(const std::string&, const std::string);
	std::vector<std::string> Split(const std::string&,  char = ' ', bool = false);
	std::string Join(const std::vector<std::string>&, const std::string& delimiter);

	std::string TrimStart(const std::string&);
	std::string TrimEnd(const std::string&);
	std::string Trim(const std::string&);

	std::string ToLower(const std::string&);
}
