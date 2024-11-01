#include "BitManipTest.h"
#include "BmpTest.h"
#include "SignalTest.h"
#include "StringCastTest.h"
#include "StringUtilsTest.h"
#include "MathStringUtilsTest.h"
#include "XmlTest.h"

int main(int argc, char** argv)
{
	BitManipTest_Execute();
	BmpTest_Execute();
	SignalTest_Execute();
	StringCastTest_Execute();
	StringUtilsTest_Execute();
	MathStringUtilsTest_Execute();
	XmlTest_Execute();
	return 0;
}
