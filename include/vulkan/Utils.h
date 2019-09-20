#pragma once

#include "Types.h"
#include "VulkanDef.h"

namespace Framework
{
	namespace Vulkan
	{
		enum
		{
			VULKAN_MEMORY_TYPE_INVALID = -1
		};
	
		uint32 GetMemoryTypeIndex(const VkPhysicalDeviceMemoryProperties&, uint32, uint32);
	}
}
