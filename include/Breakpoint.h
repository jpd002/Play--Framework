#pragma once

#ifdef _MSC_VER
	#define FRAMEWORK_BREAKPOINT __debugbreak();
#else
	#define FRAMEWORK_BREAKPOINT __builtin_trap();
#endif
