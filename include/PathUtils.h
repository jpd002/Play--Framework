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
#endif
#if defined(__APPLE__)
		boost::filesystem::path		GetHomePath();
#endif

		void EnsurePathExists(const boost::filesystem::path&);
    };
};

#endif
