#pragma once

#include <string>
#include "Vector2.h"
#include "Vector3.h"

namespace MathStringUtils
{
	float		ParseFloat(const std::string&);
	CVector2	ParseVector2(const std::string&);
	CVector3	ParseVector3(const std::string&);

	std::string	ToString(const CVector3&);
};
