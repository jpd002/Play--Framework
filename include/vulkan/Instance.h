#pragma once

#include <vulkan/vulkan.h>

#define DECLARE_FUNCTION(functionName) PFN_##functionName functionName = nullptr;

namespace Framework
{
	namespace Vulkan
	{
		class CInstance
		{
		public:
			        CInstance() = default;
			        CInstance(const VkInstanceCreateInfo&);
			        CInstance(const CInstance&) = delete;
			        CInstance(CInstance&&);
			
			virtual ~CInstance();
			
			void    Reset();
			
			CInstance& operator =(const CInstance&) = delete;
			           operator VkInstance() const;
			
			DECLARE_FUNCTION(vkDestroyInstance)
			
			DECLARE_FUNCTION(vkCreateDevice)
			DECLARE_FUNCTION(vkDestroyDevice)
			
			DECLARE_FUNCTION(vkEnumeratePhysicalDevices)
			DECLARE_FUNCTION(vkGetDeviceProcAddr)
			DECLARE_FUNCTION(vkGetPhysicalDeviceProperties)
			DECLARE_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties)
			
			//VK_EXT_debug_report
			DECLARE_FUNCTION(vkCreateDebugReportCallbackEXT)
			
			//VK_KHR_surface
			DECLARE_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
			DECLARE_FUNCTION(vkGetPhysicalDeviceSurfaceFormatsKHR)
			DECLARE_FUNCTION(vkGetPhysicalDeviceSurfacePresentModesKHR)
			DECLARE_FUNCTION(vkGetPhysicalDeviceSurfaceSupportKHR)
			
			//VK_KHR_android_surface
			DECLARE_FUNCTION(vkCreateAndroidSurfaceKHR)
			
		private:
			void    Create(const VkInstanceCreateInfo&);
			
			VkInstance m_handle = VK_NULL_HANDLE;
		};
	}
}

#undef DECLARE_FUNCTION
