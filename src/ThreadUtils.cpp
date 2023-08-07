#include "ThreadUtils.h"

#include <cassert>
#include <string>
#include <mutex>

#if defined(WIN32)
#include <Windows.h>
#include <tchar.h>
#include "string_cast.h"

typedef HRESULT (WINAPI *SetThreadDescriptionFuncType)(HANDLE, PCWSTR);
static SetThreadDescriptionFuncType SetThreadDescriptionFunc = nullptr;
#endif

using namespace Framework;

void ThreadUtils::SetThreadName(std::thread& thread, const char* name)
{
#if defined(WIN32)
	static std::once_flag initFlag;
	std::call_once(initFlag,
	               []() {
		               HMODULE library = LoadLibrary(_T("kernel32.dll"));
		               if(library)
		               {
			               SetThreadDescriptionFunc = reinterpret_cast<SetThreadDescriptionFuncType>(GetProcAddress(library, "SetThreadDescription"));
		               }
	               });
	if(SetThreadDescriptionFunc)
	{
		auto wideName = string_cast<std::wstring>(name);
		SetThreadDescriptionFunc(thread.native_handle(), wideName.c_str());
	}
#elif defined(__ANDROID__)
	pthread_setname_np(thread.native_handle(), name);
#endif
}
