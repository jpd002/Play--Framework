#include "StdStreamUtils.h"

using namespace Framework;

template <>
CStdStream Framework::CreateInputStdStream(const std::wstring& path)
{
	return CStdStream(path.c_str(), L"rb");
}

template <>
CStdStream Framework::CreateInputStdStream(const std::string& path)
{
	return CStdStream(path.c_str(), "rb");
}

template <>
CStdStream Framework::CreateOutputStdStream(const std::wstring& path)
{
	return CStdStream(path.c_str(), L"wb");
}

template <>
CStdStream Framework::CreateOutputStdStream(const std::string& path)
{
	return CStdStream(path.c_str(), "wb");
}

template <>
CStdStream Framework::CreateUpdateExistingStdStream(const std::wstring& path)
{
	return CStdStream(path.c_str(), L"r+b");
}

template <>
CStdStream Framework::CreateUpdateExistingStdStream(const std::string& path)
{
	return CStdStream(path.c_str(), "r+b");
}
