#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif
#include "Singleton.h"
#include "VulkanDef.h"

#define DECLARE_FUNCTION(functionName) PFN_##functionName functionName = nullptr;

namespace Framework
{
	namespace Vulkan
	{
		class CLoader : public CSingleton<CLoader>
		{
		public:
			CLoader();
			
			void* GetLibraryProcAddr(const char*);
			bool IsInstanceLayerPresent(const char*);
			bool IsInstanceExtensionPresent(const char*);

			DECLARE_FUNCTION(vkCreateInstance)
			DECLARE_FUNCTION(vkGetInstanceProcAddr)
			DECLARE_FUNCTION(vkEnumerateInstanceLayerProperties)
			DECLARE_FUNCTION(vkEnumerateInstanceExtensionProperties)
			
		private:
			void    LoadLibrary();
#ifdef _WIN32
			HMODULE m_vulkanModule = NULL;
#else
			void*   m_vulkanDl = nullptr;
#endif
		};
	}
}

#undef DECLARE_FUNCTION
