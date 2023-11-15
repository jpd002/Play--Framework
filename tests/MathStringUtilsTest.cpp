#include "MathStringUtilsTest.h"
#include <string>
#include <cfloat>
#include "math/MathStringUtils.h"
#include "TestDefs.h"

void MathStringUtilsTest_Execute()
{
	TEST_VERIFY(MathStringUtils::ParseFloat("0.25") == 0.25);
	TEST_VERIFY(MathStringUtils::ParseVector2("0.25, 0.5") == CVector2(0.25, 0.5));
	TEST_VERIFY(MathStringUtils::ParseVector3("0.25, 0.5, 0.125") == CVector3(0.25, 0.5, 0.125));
}
