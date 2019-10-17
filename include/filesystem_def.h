#pragma once

#if defined(__has_include) && __has_include(<filesystem>) && !defined(__APPLE__)
	#include <filesystem>
	namespace fs = std::filesystem;
#else
	#include <ghc/filesystem.hpp>
	namespace fs = ghc::filesystem;
#endif
