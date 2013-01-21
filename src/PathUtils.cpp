#include "PathUtils.h"

using namespace Framework;

#ifdef _WIN32

#include <shlobj.h>

boost::filesystem::path PathUtils::GetPathFromCsidl(int csidl)
{
	wchar_t userPathString[MAX_PATH];
	if(FAILED(SHGetFolderPathW(NULL, csidl, NULL, 0, userPathString)))
	{
		throw std::runtime_error("Couldn't get path from csidl.");
	}
	return boost::filesystem::wpath(userPathString, boost::filesystem::native);
}

boost::filesystem::path PathUtils::GetRoamingDataPath()
{
	return GetPathFromCsidl(CSIDL_APPDATA);
}

boost::filesystem::path PathUtils::GetPersonalDataPath()
{
	return GetPathFromCsidl(CSIDL_PERSONAL);
}

boost::filesystem::path PathUtils::GetAppResourcesPath()
{
	return boost::filesystem::path(".");
}

#endif

#if defined(__APPLE__)

#include <pwd.h>
#include <CoreFoundation/CoreFoundation.h>
#include <Foundation/Foundation.h>

boost::filesystem::path PathUtils::GetSettingsPath()
{
	NSArray* paths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
	std::string directory = [[paths objectAtIndex: 0] UTF8String];
	return boost::filesystem::path(directory);
}

boost::filesystem::path PathUtils::GetRoamingDataPath()
{
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	std::string directory = [[paths objectAtIndex: 0] UTF8String];
	return boost::filesystem::path(directory);
}

boost::filesystem::path PathUtils::GetPersonalDataPath()
{
	passwd* userInfo = getpwuid(getuid());
	return boost::filesystem::path(userInfo->pw_dir);
}

boost::filesystem::path PathUtils::GetAppResourcesPath()
{
	NSBundle* bundle = [NSBundle mainBundle];
	NSString* bundlePath = [bundle resourcePath];
	return boost::filesystem::path([bundlePath UTF8String]);
}

#endif

void PathUtils::EnsurePathExists(const boost::filesystem::path& path)
{
	typedef boost::filesystem::path PathType;
	PathType buildPath;
	for(PathType::iterator pathIterator(path.begin());
		pathIterator != path.end(); pathIterator++)
	{
		buildPath /= (*pathIterator);
		if(!boost::filesystem::exists(buildPath))
		{
			boost::filesystem::create_directory(buildPath);
		}
	}
}
