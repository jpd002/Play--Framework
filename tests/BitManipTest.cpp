#include "BitManipTest.h"
#include "BitManip.h"
#include "TestDefs.h"

void BitManipTest_Execute()
{
	//Results are undefined if 0 is provided to ctz/clz

	int result = 0;

	//rotateleft32 ---------------
	result = __builtin_rotateleft32(0xF0000000, 4);
	TEST_VERIFY(result == 0x0000000F);

	//ctzll ----------------------
	result = __builtin_ctzll(1ULL << 36);
	TEST_VERIFY(result == 36);

	result = __builtin_ctzll(1ULL << 25);
	TEST_VERIFY(result == 25);

	result = __builtin_ctzll(~0ULL);
	TEST_VERIFY(result == 0);

	//clzll ----------------------
	result = __builtin_clzll(1ULL << 43);
	TEST_VERIFY(result == (63 - 43));

	result = __builtin_clzll(1ULL << 14);
	TEST_VERIFY(result == (63 - 14));

	result = __builtin_clzll(~0ULL);
	TEST_VERIFY(result == 0);
}
