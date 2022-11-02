#pragma once

#include <thread>

namespace Framework
{
	namespace ThreadUtils
	{
		void SetThreadName(std::thread&, const char*);
	};
}
