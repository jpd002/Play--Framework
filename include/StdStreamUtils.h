#pragma once

#include "StdStream.h"

namespace Framework
{
	template <typename StringType>
	constexpr const typename StringType::value_type* GetInputStdStreamMode()
	{
		if constexpr (std::is_same_v<StringType, std::wstring>)
		{
			return L"rb";
		}
		else
		{
			return "rb";
		}
	}

	template <typename StringType>
	constexpr const typename StringType::value_type* GetOutputStdStreamMode()
	{
		if constexpr (std::is_same_v<StringType, std::wstring>)
		{
			return L"wb";
		}
		else
		{
			return "wb";
		}
	}

	template <typename StringType>
	constexpr const typename StringType::value_type* GetUpdateExistingStdStreamMode()
	{
		if constexpr (std::is_same_v<StringType, std::wstring>)
		{
			return L"r+b";
		}
		else
		{
			return "r+b";
		}
	}

	template <typename StringType>
	constexpr const typename StringType::value_type* GetAppendStdStreamMode()
	{
		if constexpr (std::is_same_v<StringType, std::wstring>)
		{
			return L"ab";
		}
		else
		{
			return "ab";
		}
	}

	template <typename StringType>
	CStdStream CreateInputStdStream(const StringType& path)
	{
		return CStdStream(path.c_str(), GetInputStdStreamMode<StringType>());
	}

	template <typename StringType>
	CStdStream CreateOutputStdStream(const StringType& path)
	{
		return CStdStream(path.c_str(), GetOutputStdStreamMode<StringType>());
	}

	template <typename StringType>
	CStdStream CreateUpdateExistingStdStream(const StringType& path)
	{
		return CStdStream(path.c_str(), GetUpdateExistingStdStreamMode<StringType>());
	}
}
