#pragma once

#include "filesystem_def.h"

namespace Framework
{
	time_t ConvertFsTimeToSystemTime(const fs::file_time_type&);
}
