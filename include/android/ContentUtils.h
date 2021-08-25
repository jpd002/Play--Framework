#pragma once

#include "filesystem_def.h"

namespace Framework
{
	namespace Android
	{
		class CContentUtils
		{
		public:
			static bool IsContentPath(const fs::path&);

			static std::string BuildUriFromPath(const fs::path&);
			static bool DoesFileExist(const fs::path&);
		};
	}
}
