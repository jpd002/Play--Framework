#pragma once

#include <Windows.h>

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#define FRAMEWORK_WIN_DESKTOP
#else
#define FRAMEWORK_WIN_APP
#endif
