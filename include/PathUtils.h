#pragma once

#include "boost_filesystem_def.h"

namespace Framework
{
	namespace PathUtils
	{
		boost::filesystem::path		GetAppResourcesPath();
		boost::filesystem::path		GetRoamingDataPath();
		boost::filesystem::path		GetPersonalDataPath();
		
#ifdef _WIN32
		boost::filesystem::path		GetPathFromCsidl(int);
#endif	//WIN32
#if defined(__APPLE__)
		boost::filesystem::path		GetSettingsPath();
#endif // DEFINED(__APPLE__)
#if defined(__ANDROID__)
		void						SetFilesDirPath(const char*);
#endif

		void						EnsurePathExists(const boost::filesystem::path&);
	};
};
