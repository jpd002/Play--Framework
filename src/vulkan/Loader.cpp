#include <dlfcn.h>
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
	assert(m_vulkanDl == nullptr);
	
	m_vulkanDl = dlopen("libvulkan.so", RTLD_NOW | RTLD_LOCAL);
	if(!m_vulkanDl)
	{
		throw std::runtime_error(string_format("Failed to load Vulkan library: %s.", dlerror()));
	}
	
	vkCreateInstance      = reinterpret_cast<PFN_vkCreateInstance>(dlsym(m_vulkanDl, "vkCreateInstance"));
	vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(dlsym(m_vulkanDl, "vkGetInstanceProcAddr"));
}
