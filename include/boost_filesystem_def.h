#pragma once

//This is required on UWP because 'generic' is a keyword

#ifdef _WIN32

#define generic boost_generic
#include <boost/filesystem.hpp>
#undef generic

#else

#include <boost/filesystem.hpp>

#endif
