#pragma once

#include "boost_filesystem_def.h"

namespace Framework
{
	namespace PathUtils
	{
		boost::filesystem::path		GetAppResourcesPath();
		boost::filesystem::path		GetRoamingDataPath();
		boost::filesystem::path		GetPersonalDataPath();
		boost::filesystem::path		GetCachePath();
		
#ifdef _WIN32
		boost::filesystem::path		GetPathFromCsidl(int);
#endif	//WIN32
#if defined(__ANDROID__)
		void						SetFilesDirPath(const char*);
#endif

		void						EnsurePathExists(const boost::filesystem::path&);

		std::string					GetNativeStringFromPath(const boost::filesystem::path&);
		boost::filesystem::path		GetPathFromNativeString(const std::string&);
	};
};
