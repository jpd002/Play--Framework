#pragma once

#include <cassert>

#ifdef _DEBUG
#define CHECKVULKANERROR(errorCode) { assert(errorCode == VK_SUCCESS); }
#else
#define CHECKVULKANERROR(errorCode)
#endif
