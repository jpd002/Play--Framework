#pragma once

#include <string>
#include <vector>

namespace StringUtils
{
	std::string ReplaceAll(const std::string&, const std::string, const std::string);
	std::string EraseAll(const std::string&, const std::string);
	std::vector<std::string> Split(const std::string&,  char = ' ', bool = false);

	std::string TrimStart(const std::string&);
	std::string TrimEnd(const std::string&);
	std::string Trim(const std::string&);
}