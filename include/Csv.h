#pragma once

#include <vector>
#include <string>
#include "Stream.h"

namespace Framework
{
	namespace Csv
	{
		typedef std::vector<std::string> Line;
		typedef std::vector<Line> Contents;

		Contents Parse(CStream&, char separator = ',');
		void Write(const Contents&, CStream&, char separator = ',');
	}
}
