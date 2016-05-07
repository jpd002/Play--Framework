#include "vulkan/VulkanDef.h"
#include "vulkan/Instance.h"
#include "vulkan/Loader.h"

#define SET_PROC_ADDR(functionName) this->functionName = reinterpret_cast<PFN_##functionName>(CLoader::GetInstance().vkGetInstanceProcAddr(m_handle, #functionName));

using namespace Framework::Vulkan;

CInstance::CInstance(const VkInstanceCreateInfo& instanceCreateInfo)
{
	Create(instanceCreateInfo);
}

CInstance::~CInstance()
{
	Reset();
}

void CInstance::Reset()
{
	if(m_handle != nullptr)
	{
		this->vkDestroyInstance(m_handle, nullptr);
		m_handle = nullptr;
	}
}

CInstance::operator VkInstance() const
{
	return m_handle;
}

void CInstance::Create(const VkInstanceCreateInfo& instanceCreateInfo)
{
	assert(m_handle == VK_NULL_HANDLE);
	
	auto result = CLoader::GetInstance().vkCreateInstance(&instanceCreateInfo, nullptr, &m_handle);
	CHECKVULKANERROR(result);
	
	SET_PROC_ADDR(vkDestroyInstance);
	
	SET_PROC_ADDR(vkCreateDevice);
	SET_PROC_ADDR(vkDestroyDevice);

	SET_PROC_ADDR(vkEnumeratePhysicalDevices);
	SET_PROC_ADDR(vkGetDeviceProcAddr);
	SET_PROC_ADDR(vkGetPhysicalDeviceProperties);
	SET_PROC_ADDR(vkGetPhysicalDeviceQueueFamilyProperties);
	
	SET_PROC_ADDR(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
	SET_PROC_ADDR(vkGetPhysicalDeviceSurfaceFormatsKHR);
	SET_PROC_ADDR(vkGetPhysicalDeviceSurfacePresentModesKHR);
	SET_PROC_ADDR(vkGetPhysicalDeviceSurfaceSupportKHR);

	SET_PROC_ADDR(vkCreateDebugReportCallbackEXT);
	
#if defined(__ANDROID__)
	SET_PROC_ADDR(vkCreateAndroidSurfaceKHR);
#endif
#if defined(__linux__)
	SET_PROC_ADDR(vkCreateXcbSurfaceKHR);
#endif
}
