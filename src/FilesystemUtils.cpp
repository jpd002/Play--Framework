#include "FilesystemUtils.h"
#ifdef _MSC_VER
#include <Windows.h>
#endif

namespace
{
	//From https://stackoverflow.com/a/58237530
	template <typename TP>
	std::time_t to_time_t(TP tp)
	{
		using namespace std::chrono;
		auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
		return system_clock::to_time_t(sctp);
	}
}

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
	return to_time_t(fileTime);
#endif
}

