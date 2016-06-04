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

bool CDevice::IsEmpty() const
{
	return (m_handle == VK_NULL_HANDLE);
}

void CDevice::Reset()
{
	if(m_handle != VK_NULL_HANDLE)
	{
		assert(m_instance != nullptr);
		m_instance->vkDestroyDevice(m_handle, nullptr);
		m_instance = nullptr;
		m_handle = VK_NULL_HANDLE;
	}
	
	vkAllocateCommandBuffers = nullptr;
	vkFreeCommandBuffers = nullptr;
	
	vkBeginCommandBuffer = nullptr;
	vkEndCommandBuffer = nullptr;
	
	vkCmdBeginRenderPass = nullptr;
	vkCmdClearColorImage = nullptr;
	vkCmdEndRenderPass = nullptr;
	vkCmdPipelineBarrier = nullptr;
	vkCmdSetScissor = nullptr;
	vkCmdSetViewport = nullptr;
	
	vkGetDeviceQueue = nullptr;
	
	vkQueueSubmit = nullptr;
	vkQueueWaitIdle = nullptr;
	
	vkCreateCommandPool = nullptr;
	vkCreateFramebuffer = nullptr;
	vkCreateImageView = nullptr;
	vkCreateRenderPass = nullptr;
	vkCreateShaderModule = nullptr;
	
	vkCreateSemaphore = nullptr;
	vkDestroySemaphore = nullptr;
	
	vkAcquireNextImageKHR = nullptr;
	vkCreateSwapchainKHR = nullptr;
	vkGetSwapchainImagesKHR = nullptr;
	vkQueuePresentKHR = nullptr;
}

CDevice& CDevice::operator =(CDevice&& rhs)
{
	Reset();
	
	std::swap(m_handle, rhs.m_handle);
	std::swap(m_instance, rhs.m_instance);
	
	std::swap(vkAllocateCommandBuffers, rhs.vkAllocateCommandBuffers);
	std::swap(vkFreeCommandBuffers, rhs.vkFreeCommandBuffers);
	
	std::swap(vkBeginCommandBuffer, rhs.vkBeginCommandBuffer);
	std::swap(vkEndCommandBuffer, rhs.vkEndCommandBuffer);
	
	std::swap(vkCmdBeginRenderPass, rhs.vkCmdBeginRenderPass);
	std::swap(vkCmdClearColorImage, rhs.vkCmdClearColorImage);
	std::swap(vkCmdEndRenderPass, rhs.vkCmdEndRenderPass);
	std::swap(vkCmdPipelineBarrier, rhs.vkCmdPipelineBarrier);
	std::swap(vkCmdSetScissor, rhs.vkCmdSetScissor);
	std::swap(vkCmdSetViewport, rhs.vkCmdSetViewport);
	
	std::swap(vkGetDeviceQueue, rhs.vkGetDeviceQueue);
	
	std::swap(vkQueueSubmit, rhs.vkQueueSubmit);
	std::swap(vkQueueWaitIdle, rhs.vkQueueWaitIdle);
	
	std::swap(vkCreateCommandPool, rhs.vkCreateCommandPool);
	std::swap(vkCreateFramebuffer, rhs.vkCreateFramebuffer);
	std::swap(vkCreateImageView, rhs.vkCreateImageView);
	std::swap(vkCreateRenderPass, rhs.vkCreateRenderPass);
	std::swap(vkCreateShaderModule, rhs.vkCreateShaderModule);
	
	std::swap(vkCreateSemaphore, rhs.vkCreateSemaphore);
	std::swap(vkDestroySemaphore, rhs.vkDestroySemaphore);
	
	std::swap(vkAcquireNextImageKHR, rhs.vkAcquireNextImageKHR);
	std::swap(vkCreateSwapchainKHR, rhs.vkCreateSwapchainKHR);
	std::swap(vkGetSwapchainImagesKHR, rhs.vkGetSwapchainImagesKHR);
	std::swap(vkQueuePresentKHR, rhs.vkQueuePresentKHR);
	
	return (*this);
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
	SET_PROC_ADDR(vkCreateShaderModule);
	
	SET_PROC_ADDR(vkCreateSemaphore);
	SET_PROC_ADDR(vkDestroySemaphore);
	
	SET_PROC_ADDR(vkAcquireNextImageKHR);
	SET_PROC_ADDR(vkCreateSwapchainKHR);
	SET_PROC_ADDR(vkGetSwapchainImagesKHR);
	SET_PROC_ADDR(vkQueuePresentKHR);
}

