#include "FilesystemUtils.h"
#ifdef _MSC_VER
#include <Windows.h>
#endif

time_t Framework::ConvertFsTimeToSystemTime(const fs::file_time_type& fileTime)
{
	//This is temporary till we get clock_cast in C++20
	//https://developercommunity.visualstudio.com/content/problem/251213/stdfilesystemfile-time-type-does-not-allow-easy-co.html
#ifdef _MSC_VER
	FILETIME ft;
	SYSTEMTIME st;
	memcpy(&ft, &fileTime, sizeof(FILETIME));
	if(FileTimeToSystemTime(&ft, &st))
	{
		std::tm convTime = {};
		convTime.tm_sec = st.wSecond;
		convTime.tm_min = st.wMinute;
		convTime.tm_hour = st.wHour;
		convTime.tm_mday = st.wDay;
		convTime.tm_mon = st.wMonth - 1;
		convTime.tm_year = st.wYear - 1900;
		convTime.tm_isdst = -1;
		return mktime(&convTime);
	}
	else
	{
		return 0;
	}
#else
	return fs::file_time_type::clock::to_time_t(fileTime);
#endif
}

