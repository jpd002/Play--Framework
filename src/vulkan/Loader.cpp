#ifdef _WIN32
#include <Windows.h>
#include <tchar.h>
#else
#include <dlfcn.h>
#endif
#include <stdexcept>
#include <cassert>
#include "vulkan/Loader.h"
#include "string_format.h"

using namespace Framework::Vulkan;

CLoader::CLoader()
{
	LoadLibrary();
}

void CLoader::LoadLibrary()
{
#ifdef _WIN32
	assert(m_vulkanModule == NULL);

	m_vulkanModule = ::LoadLibrary(_T("vulkan-1.dll"));
	if(m_vulkanModule == NULL)
	{
		throw std::runtime_error("Failed to load Vulkan library.");
	}

	vkCreateInstance      = reinterpret_cast<PFN_vkCreateInstance>(GetProcAddress(m_vulkanModule, "vkCreateInstance"));
	vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(GetProcAddress(m_vulkanModule, "vkGetInstanceProcAddr"));
#else
	assert(m_vulkanDl == nullptr);
	
#ifdef __APPLE__
	const char* libPath = "@executable_path/../Resources/libMoltenVK.dylib";
#else
	const char* libPath = "libvulkan.so";
#endif
	
	m_vulkanDl = dlopen(libPath, RTLD_NOW | RTLD_LOCAL);
	if(!m_vulkanDl)
	{
		throw std::runtime_error(string_format("Failed to load Vulkan library: %s.", dlerror()));
	}
	
	vkCreateInstance      = reinterpret_cast<PFN_vkCreateInstance>(dlsym(m_vulkanDl, "vkCreateInstance"));
	vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(dlsym(m_vulkanDl, "vkGetInstanceProcAddr"));
#endif
}
