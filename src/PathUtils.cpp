#include "PathUtils.h"

using namespace Framework;
using namespace boost;
using namespace std;

#ifdef WIN32

#include <shlobj.h>

filesystem::wpath PathUtils::GetPathFromCsidl(int csidl)
{
    wchar_t userPathString[MAX_PATH];
    if(FAILED(SHGetFolderPathW(NULL, csidl, NULL, 0, userPathString)))
    {
        throw runtime_error("Couldn't get path from csidl.");
    }
    return filesystem::wpath(userPathString, filesystem::native);
}

filesystem::wpath PathUtils::GetRoamingDataPath()
{
    return GetPathFromCsidl(CSIDL_APPDATA);
}

#endif

#ifdef MACOSX

#include <pwd.h>

filesystem::path PathUtils::GetHomePath()
{
	passwd* userInfo = getpwuid(getuid());
    return filesystem::path(userInfo->pw_dir);
}

#endif
