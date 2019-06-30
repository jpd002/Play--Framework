#include "MathStringUtilsTest.h"
#include "math/MathStringUtils.h"
#include <string>
#include <cassert>
#include <cfloat>

void MathStringUtilsTest_Execute()
{
	assert(MathStringUtils::ParseFloat("0.25") == 0.25);
	assert(MathStringUtils::ParseVector2("0.25, 0.5") == CVector2(0.25, 0.5));
	assert(MathStringUtils::ParseVector3("0.25, 0.5, 0.125") == CVector3(0.25, 0.5, 0.125));
}
