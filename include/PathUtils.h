#pragma once

#include "filesystem_def.h"

namespace Framework
{
	namespace PathUtils
	{
		fs::path GetAppResourcesPath();
		fs::path GetRoamingDataPath();
		fs::path GetPersonalDataPath();
		fs::path GetCachePath();
		
#ifdef _WIN32
		fs::path GetPathFromCsidl(int);
#endif	//WIN32
#if defined(__ANDROID__)
		void SetFilesDirPath(const char*);
#endif

		void EnsurePathExists(const fs::path&);

		std::string GetNativeStringFromPath(const fs::path&);
		fs::path    GetPathFromNativeString(const std::string&);
	};
};
