#include "android/ContentUtils.h"
#include <cassert>
#include "Url.h"
#include "android/ContentResolver.h"
#include "android/android_net_Uri.h"

using namespace Framework;
using namespace Framework::Android;

bool CContentUtils::IsContentPath(const fs::path& filePath)
{
	return filePath.string().find("content:/") == 0;
}

std::string CContentUtils::BuildUriFromPath(const fs::path& filePath)
{
	assert(IsContentPath(filePath));
	auto uriPath = filePath.string().substr(9);
	auto uri = "content://" + uriPath;
	return uri;
}

bool CContentUtils::DoesFileExist(const fs::path& filePath)
{
	assert(IsContentPath(filePath));
	auto env = CJavaVM::GetEnv();
	auto uri = BuildUriFromPath(filePath);
	auto& contentResolver = CContentResolver::GetInstance().GetContentResolver();
	auto pathUri = android::net::Uri::parse(env->NewStringUTF(uri.c_str()));
	try
	{
		auto cursor = contentResolver.query(pathUri, NULL, NULL, NULL, NULL, NULL);
		bool exists = cursor.getCount() > 0;
		cursor.close();
		return exists;
	}
	catch(const std::exception& e)
	{
		return false;
	}
}
