#pragma once

#include <Windows.h>

#if defined(WINAPI_FAMILY_PARTITION)
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#define FRAMEWORK_WIN_DESKTOP
#else
#define FRAMEWORK_WIN_APP
#endif
#else // defined(WINAPI_FAMILY_PARTITION)
#define FRAMEWORK_WIN_DESKTOP
#endif // !defined(WINAPI_FAMILY_PARTITION)
