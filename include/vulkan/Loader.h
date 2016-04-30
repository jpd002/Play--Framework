#pragma once

#include <vulkan/vulkan.h>
#include "Singleton.h"

#define DECLARE_FUNCTION(functionName) PFN_##functionName functionName = nullptr;

namespace Framework
{
	namespace Vulkan
	{
		class CLoader : public CSingleton<CLoader>
		{
		public:
			CLoader();
			
			DECLARE_FUNCTION(vkCreateInstance)
			DECLARE_FUNCTION(vkGetInstanceProcAddr);
			
		private:
			void    LoadLibrary();
			
			void*   m_vulkanDl = nullptr;
		};
	}
}

#undef DECLARE_FUNCTION
