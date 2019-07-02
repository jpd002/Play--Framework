#include "BmpTest.h"
#include "SignalTest.h"
#include "StringCastTest.h"
#include "StringUtilsTest.h"
#include "MathStringUtilsTest.h"

int main(int argc, char** argv)
{
	BmpTest_Execute();
	SignalTest_Execute();
	StringCastTest_Execute();
	StringUtilsTest_Execute();
	MathStringUtilsTest_Execute();
	return 0;
}
