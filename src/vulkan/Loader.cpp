#ifdef _WIN32
#include <Windows.h>
#include <tchar.h>
#else
#include <dlfcn.h>
#endif
#include <stdexcept>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>
#include "vulkan/Loader.h"
#include "string_format.h"

using namespace Framework::Vulkan;

CLoader::CLoader()
{
	LoadLibrary();
}

void* CLoader::GetLibraryProcAddr(const char* procName)
{
#ifdef _WIN32
	return GetProcAddress(m_vulkanModule, procName);
#else
	return dlsym(m_vulkanDl, procName);
#endif
}

bool CLoader::IsInstanceLayerPresent(const char* layerName)
{
	uint32_t layerCount = 0;
	auto result = vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	CHECKVULKANERROR(result);

	std::vector<VkLayerProperties> layers;
	layers.resize(layerCount);
	result = vkEnumerateInstanceLayerProperties(&layerCount, layers.data());
	CHECKVULKANERROR(result);

	auto layer = std::find_if(std::begin(layers), std::end(layers), [&](const auto& layer) { return !strcmp(layerName, layer.layerName); });
	return layer != std::end(layers);
}

bool CLoader::IsInstanceExtensionPresent(const char* extensionName)
{
	uint32_t extensionCount = 0;
	auto result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	CHECKVULKANERROR(result);

	std::vector<VkExtensionProperties> extensions;
	extensions.resize(extensionCount);
	result = vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
	CHECKVULKANERROR(result);

	auto extension = std::find_if(std::begin(extensions), std::end(extensions), [&](const auto& extension) { return !strcmp(extensionName, extension.extensionName); });
	return extension != std::end(extensions);
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

#else
	assert(m_vulkanDl == nullptr);
	
	std::vector<const char*> libPaths;
#ifdef __APPLE__
	libPaths.push_back("@executable_path/../Resources/libMoltenVK.dylib");
	libPaths.push_back("@executable_path/libMoltenVK.dylib");
	libPaths.push_back("@executable_path/Frameworks/MoltenVK.framework/MoltenVK");
	libPaths.push_back("@executable_path/Contents/Frameworks/MoltenVK.framework/MoltenVK");
#else
	libPaths.push_back("libvulkan.so");
	libPaths.push_back("libvulkan.so.1");
#endif
	
	for(const auto& libPath : libPaths)
	{
		m_vulkanDl = dlopen(libPath, RTLD_NOW | RTLD_LOCAL);
		if(m_vulkanDl)
		{
			break;
		}
		printf("Warning: Failed attempt to load Vulkan library from '%s': %s.\n", libPath, dlerror());
	}

	if(!m_vulkanDl)
	{
		throw std::runtime_error("Failed to find an appropriate Vulkan library to load.");
	}
#endif

	vkCreateInstance                       = reinterpret_cast<PFN_vkCreateInstance>(GetLibraryProcAddr("vkCreateInstance"));
	vkGetInstanceProcAddr                  = reinterpret_cast<PFN_vkGetInstanceProcAddr>(GetLibraryProcAddr("vkGetInstanceProcAddr"));
	vkEnumerateInstanceLayerProperties     = reinterpret_cast<PFN_vkEnumerateInstanceLayerProperties>(GetLibraryProcAddr("vkEnumerateInstanceLayerProperties"));
	vkEnumerateInstanceExtensionProperties = reinterpret_cast<PFN_vkEnumerateInstanceExtensionProperties>(GetLibraryProcAddr("vkEnumerateInstanceExtensionProperties"));
}
