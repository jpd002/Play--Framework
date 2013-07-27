#ifndef _PATHUTILS_H_
#define _PATHUTILS_H_

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace Framework
{
	namespace PathUtils
	{
#ifdef _WIN32
		boost::filesystem::path		GetPathFromCsidl(int);
		boost::filesystem::path		GetRoamingDataPath();
		boost::filesystem::path		GetPersonalDataPath();
		boost::filesystem::path		GetAppResourcesPath();
#endif
#if defined(_POSIX_VERSION)
#if defined(__APPLE__)
		boost::filesystem::path		GetSettingsPath();
		boost::filesystem::path		GetRoamingDataPath();
		boost::filesystem::path		GetAppResourcesPath();
#endif	// DEFINED(__APPLE__)
		boost::filesystem::path		GetPersonalDataPath();
#endif	// DEFINED(_POSIX_VERSION)

		void						EnsurePathExists(const boost::filesystem::path&);
	};
};

#endif
