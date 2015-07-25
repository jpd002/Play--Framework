#ifndef _STDSTREAMUTILS_H_
#define _STDSTREAMUTILS_H_

#include "StdStream.h"

namespace Framework
{
	template <typename StringType>
	static CStdStream CreateInputStdStream(const StringType&);

	template <typename StringType>
	static CStdStream CreateOutputStdStream(const StringType&);

	template <>
	CStdStream CreateInputStdStream(const std::wstring& path)
	{
		return CStdStream(path.c_str(), L"rb");
	}

	template <>
	CStdStream CreateInputStdStream(const std::string& path)
	{
		return CStdStream(path.c_str(), "rb");
	}

	template <>
	CStdStream CreateOutputStdStream(const std::wstring& path)
	{
		return CStdStream(path.c_str(), L"wb");
	}

	template <>
	CStdStream CreateOutputStdStream(const std::string& path)
	{
		return CStdStream(path.c_str(), "wb");
	}
}

#endif
