#include "vulkan/VulkanDef.h"
#include "vulkan/Device.h"

#define SET_PROC_ADDR(functionName) this->functionName = reinterpret_cast<PFN_##functionName>(m_instance->vkGetDeviceProcAddr(m_handle, #functionName));

using namespace Framework::Vulkan;

CDevice::CDevice(const CInstance& instance, VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo& deviceCreateInfo)
: m_instance(&instance)
{
	Create(physicalDevice, deviceCreateInfo);
}

CDevice::~CDevice()
{
	Reset();
}

void CDevice::Reset()
{
	if(m_handle != nullptr)
	{
		assert(m_instance != nullptr);
		m_instance->vkDestroyDevice(m_handle, nullptr);
		m_handle = nullptr;
	}
}

CDevice::operator VkDevice() const
{
	return m_handle;
}

void CDevice::Create(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo& deviceCreateInfo)
{
	assert(m_handle == VK_NULL_HANDLE);
	
	auto result = m_instance->vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &m_handle);
	CHECKVULKANERROR(result);
	
	SET_PROC_ADDR(vkAllocateCommandBuffers);
	SET_PROC_ADDR(vkFreeCommandBuffers);
	
	SET_PROC_ADDR(vkBeginCommandBuffer);
	SET_PROC_ADDR(vkEndCommandBuffer);
	
	SET_PROC_ADDR(vkCmdBeginRenderPass);
	SET_PROC_ADDR(vkCmdClearColorImage);
	SET_PROC_ADDR(vkCmdEndRenderPass);
	SET_PROC_ADDR(vkCmdPipelineBarrier);
	SET_PROC_ADDR(vkCmdSetScissor);
	SET_PROC_ADDR(vkCmdSetViewport);
	
	SET_PROC_ADDR(vkGetDeviceQueue);
	
	SET_PROC_ADDR(vkQueueSubmit);
	SET_PROC_ADDR(vkQueueWaitIdle);
	
	SET_PROC_ADDR(vkCreateCommandPool);
	SET_PROC_ADDR(vkCreateFramebuffer);
	SET_PROC_ADDR(vkCreateImageView);
	SET_PROC_ADDR(vkCreateRenderPass);
	
	SET_PROC_ADDR(vkCreateSemaphore);
	SET_PROC_ADDR(vkDestroySemaphore);
	
	SET_PROC_ADDR(vkAcquireNextImageKHR);
	SET_PROC_ADDR(vkCreateSwapchainKHR);
	SET_PROC_ADDR(vkGetSwapchainImagesKHR);
	SET_PROC_ADDR(vkQueuePresentKHR);
}

