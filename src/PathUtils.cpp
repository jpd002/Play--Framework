#include "PathUtils.h"
#include "Utf8.h"

using namespace Framework;

#ifdef _WIN32

#if WINAPI_FAMILY_ONE_PARTITION(WINAPI_FAMILY, WINAPI_PARTITION_APP)

fs::path PathUtils::GetPersonalDataPath()
{
	auto localFolder = Windows::Storage::ApplicationData::Current->LocalFolder;
	return fs::path(localFolder->Path->Data());
}

#else	// !WINAPI_PARTITION_APP

#include <shlobj.h>

fs::path PathUtils::GetPathFromCsidl(int csidl)
{
	wchar_t userPathString[MAX_PATH];
	if(FAILED(SHGetFolderPathW(NULL, csidl | CSIDL_FLAG_CREATE, NULL, 0, userPathString)))
	{
		throw std::runtime_error("Couldn't get path from csidl.");
	}
	return fs::path(userPathString, fs::path::native_format);
}

fs::path PathUtils::GetRoamingDataPath()
{
	return GetPathFromCsidl(CSIDL_APPDATA);
}

fs::path PathUtils::GetPersonalDataPath()
{
	return GetPathFromCsidl(CSIDL_PERSONAL);
}

fs::path PathUtils::GetAppResourcesPath()
{
	return fs::path(".");
}

fs::path PathUtils::GetCachePath()
{
	return GetPathFromCsidl(CSIDL_LOCAL_APPDATA);
}

#endif	// !WINAPI_PARTITION_APP

#elif defined(__APPLE__)

#include <CoreFoundation/CoreFoundation.h>
#include <Foundation/Foundation.h>

fs::path PathUtils::GetRoamingDataPath()
{
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	std::string directory = [[paths objectAtIndex: 0] fileSystemRepresentation];
	return fs::path(directory);
}

fs::path PathUtils::GetAppResourcesPath()
{
	NSBundle* bundle = [NSBundle mainBundle];
	NSString* bundlePath = [bundle resourcePath];
	return fs::path([bundlePath fileSystemRepresentation]);
}

fs::path PathUtils::GetPersonalDataPath()
{
	return GetRoamingDataPath();
}

fs::path PathUtils::GetCachePath()
{
	NSArray* paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
	std::string directory = [[paths objectAtIndex: 0] fileSystemRepresentation];
	return fs::path(directory);
}

#elif defined(__ANDROID__)

static fs::path s_filesDirPath;

fs::path PathUtils::GetAppResourcesPath()
{
	//This won't work for Android
	return fs::path();
}

fs::path PathUtils::GetRoamingDataPath()
{
	return s_filesDirPath;
}

fs::path PathUtils::GetPersonalDataPath()
{
	return s_filesDirPath;
}

fs::path PathUtils::GetCachePath()
{
	throw std::runtime_error("Not implemented.");
}

void PathUtils::SetFilesDirPath(const char* filesDirPath)
{
	s_filesDirPath = filesDirPath;
}

#elif defined(__linux__) || defined(__FreeBSD__)

// TODO: is this an appropriate translation?
fs::path PathUtils::GetAppResourcesPath()
{
	return fs::path(getenv("HOME")) / ".local/share";
}

fs::path PathUtils::GetRoamingDataPath()
{
	return fs::path(getenv("HOME")) / ".local/share";
}

fs::path PathUtils::GetPersonalDataPath()
{
	return fs::path(getenv("HOME")) / ".local/share";
}

fs::path PathUtils::GetCachePath()
{
	return fs::path(getenv("HOME")) / ".cache";
}

#else	// !DEFINED(__ANDROID__) || !DEFINED(__APPLE__) || !DEFINED(__linux__) || !DEFINED(__FreeBSD__)

#include <pwd.h>

fs::path PathUtils::GetPersonalDataPath()
{
	passwd* userInfo = getpwuid(getuid());
	return fs::path(userInfo->pw_dir);
}

#endif

void PathUtils::EnsurePathExists(const fs::path& path)
{
	typedef fs::path PathType;
	PathType buildPath;
	for(PathType::iterator pathIterator(path.begin());
		pathIterator != path.end(); pathIterator++)
	{
		buildPath /= (*pathIterator);
		std::error_code existsErrorCode;
		bool exists = fs::exists(buildPath, existsErrorCode);
		if(existsErrorCode)
		{
#ifdef _WIN32
			if(existsErrorCode.value() == ERROR_ACCESS_DENIED)
			{
				//No problem, it exists, but we just don't have access
				continue;
			}
			else if(existsErrorCode.value() == ERROR_FILE_NOT_FOUND)
			{
				exists = false;
			}
#else
			if(existsErrorCode.value() == ENOENT)
			{
				exists = false;
			}
#endif
			else
			{
				throw std::runtime_error("Couldn't ensure that path exists.");
			}
		}
		if(!exists)
		{
			fs::create_directory(buildPath);
		}
	}
}

////////////////////////////////////////////
//NativeString <-> Path Function Utils
////////////////////////////////////////////

template <typename StringType>
static std::string GetNativeStringFromPathInternal(const StringType&);

template <>
std::string GetNativeStringFromPathInternal(const std::string& str)
{
	return str;
}

template <>
std::string GetNativeStringFromPathInternal(const std::wstring& str)
{
	return Framework::Utf8::ConvertTo(str);
}

template <typename StringType>
static StringType GetPathFromNativeStringInternal(const std::string&);

template <>
std::string GetPathFromNativeStringInternal(const std::string& str)
{
	return str;
}

template <>
std::wstring GetPathFromNativeStringInternal(const std::string& str)
{
	return Framework::Utf8::ConvertFrom(str);
}

////////////////////////////////////////////
//NativeString <-> Path Function Implementations
////////////////////////////////////////////

std::string PathUtils::GetNativeStringFromPath(const fs::path& path)
{
	return GetNativeStringFromPathInternal(path.native());
}

fs::path PathUtils::GetPathFromNativeString(const std::string& str)
{
	auto cvtStr = GetPathFromNativeStringInternal<fs::path::string_type>(str);
	return fs::path(cvtStr);
}
