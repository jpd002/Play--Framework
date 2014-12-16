#include "string_format.h"
#include "math/MathStringUtils.h"
#include <vector>
#include <sstream>
#include <boost/algorithm/string.hpp>

float MathStringUtils::ParseFloat(const std::string& valueString)
{
	float result = 0;
	std::stringstream ss;
	ss.imbue(std::locale::classic());
	ss << valueString;
	ss >> result;
	return result;
}

CVector2 MathStringUtils::ParseVector2(const std::string& vectorString)
{
	std::vector<std::string> components;
	boost::split(components, vectorString, boost::is_any_of(", "), boost::algorithm::token_compress_on);
	CVector2 result(0, 0);
	if(components.size() != 2) return result;
	result.x = ParseFloat(components[0]);
	result.y = ParseFloat(components[1]);
	return result;
}

CVector3 MathStringUtils::ParseVector3(const std::string& vectorString)
{
	std::vector<std::string> components;
	boost::split(components, vectorString, boost::is_any_of(", "), boost::algorithm::token_compress_on);
	CVector3 result(0, 0, 0);
	if(components.size() != 3) return result;
	result.x = ParseFloat(components[0]);
	result.y = ParseFloat(components[1]);
	result.z = ParseFloat(components[2]);
	return result;
}

std::string MathStringUtils::ToString(const CVector3& vector)
{
	return string_format("%f, %f, %f", vector.x, vector.y, vector.z);
}
