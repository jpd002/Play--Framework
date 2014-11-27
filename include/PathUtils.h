#ifndef _PATHUTILS_H_
#define _PATHUTILS_H_

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace Framework
{
	namespace PathUtils
	{
		boost::filesystem::path		GetAppResourcesPath();
		boost::filesystem::path		GetRoamingDataPath();
		boost::filesystem::path		GetPersonalDataPath();
		
#ifdef _WIN32
		boost::filesystem::path		GetPathFromCsidl(int);
#endif
#if defined(__APPLE__)
		boost::filesystem::path		GetSettingsPath();
#endif // DEFINED(__APPLE__)

		void						EnsurePathExists(const boost::filesystem::path&);
	};
};

#endif
