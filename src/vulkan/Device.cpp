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
	
	vkBeginCommandBuffer = nullptr;
	vkEndCommandBuffer = nullptr;
	
	vkCmdBeginRenderPass = nullptr;
	vkCmdBindPipeline = nullptr;
	vkCmdBindVertexBuffers = nullptr;
	vkCmdClearColorImage = nullptr;
	vkCmdDraw = nullptr;
	vkCmdEndRenderPass = nullptr;
	vkCmdPipelineBarrier = nullptr;
	vkCmdPushConstants = nullptr;
	vkCmdSetScissor = nullptr;
	vkCmdSetViewport = nullptr;
	
	vkGetDeviceQueue = nullptr;
	
	vkQueueSubmit = nullptr;
	vkQueueWaitIdle = nullptr;
	
	vkCreateFramebuffer = nullptr;
	vkCreateImageView = nullptr;
	vkCreateRenderPass = nullptr;
	
	vkCreateBuffer = nullptr;
	vkBindBufferMemory = nullptr;
	vkDestroyBuffer = nullptr;
	vkGetBufferMemoryRequirements = nullptr;
	
	vkAllocateCommandBuffers = nullptr;
	vkFreeCommandBuffers = nullptr;
	vkResetCommandBuffer = nullptr;
	
	vkCreateCommandPool = nullptr;
	vkDestroyCommandPool = nullptr;

	vkAllocateMemory = nullptr;
	vkFreeMemory = nullptr;
	vkMapMemory = nullptr;
	vkUnmapMemory = nullptr;
	
	vkCreateGraphicsPipelines = nullptr;
	vkDestroyPipeline = nullptr;
	
	vkCreatePipelineCache = nullptr;
	vkDestroyPipelineCache = nullptr;
	
	vkCreatePipelineLayout = nullptr;
	vkDestroyPipelineLayout = nullptr;
	
	vkCreateSemaphore = nullptr;
	vkDestroySemaphore = nullptr;
	
	vkCreateShaderModule = nullptr;
	vkDestroyShaderModule = nullptr;
	
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
	
	std::swap(vkBeginCommandBuffer, rhs.vkBeginCommandBuffer);
	std::swap(vkEndCommandBuffer, rhs.vkEndCommandBuffer);
	
	std::swap(vkCmdBeginRenderPass, rhs.vkCmdBeginRenderPass);
	std::swap(vkCmdBindPipeline, rhs.vkCmdBindPipeline);
	std::swap(vkCmdBindVertexBuffers, rhs.vkCmdBindVertexBuffers);
	std::swap(vkCmdClearColorImage, rhs.vkCmdClearColorImage);
	std::swap(vkCmdDraw, rhs.vkCmdDraw);
	std::swap(vkCmdEndRenderPass, rhs.vkCmdEndRenderPass);
	std::swap(vkCmdPipelineBarrier, rhs.vkCmdPipelineBarrier);
	std::swap(vkCmdPushConstants, rhs.vkCmdPushConstants);
	std::swap(vkCmdSetScissor, rhs.vkCmdSetScissor);
	std::swap(vkCmdSetViewport, rhs.vkCmdSetViewport);
	
	std::swap(vkGetDeviceQueue, rhs.vkGetDeviceQueue);
	
	std::swap(vkQueueSubmit, rhs.vkQueueSubmit);
	std::swap(vkQueueWaitIdle, rhs.vkQueueWaitIdle);
	
	std::swap(vkCreateFramebuffer, rhs.vkCreateFramebuffer);
	std::swap(vkCreateImageView, rhs.vkCreateImageView);
	std::swap(vkCreateRenderPass, rhs.vkCreateRenderPass);
	
	std::swap(vkCreateBuffer, rhs.vkCreateBuffer);
	std::swap(vkBindBufferMemory, rhs.vkBindBufferMemory);
	std::swap(vkDestroyBuffer, rhs.vkDestroyBuffer);
	std::swap(vkGetBufferMemoryRequirements, rhs.vkGetBufferMemoryRequirements);
	
	std::swap(vkAllocateCommandBuffers, rhs.vkAllocateCommandBuffers);
	std::swap(vkFreeCommandBuffers, rhs.vkFreeCommandBuffers);
	std::swap(vkResetCommandBuffer, rhs.vkResetCommandBuffer);
	
	std::swap(vkCreateCommandPool, rhs.vkCreateCommandPool);
	std::swap(vkDestroyCommandPool, rhs.vkDestroyCommandPool);

	std::swap(vkAllocateMemory, rhs.vkAllocateMemory);
	std::swap(vkFreeMemory, rhs.vkFreeMemory);
	std::swap(vkMapMemory, rhs.vkMapMemory);
	std::swap(vkUnmapMemory, rhs.vkUnmapMemory);
	
	std::swap(vkCreateGraphicsPipelines, rhs.vkCreateGraphicsPipelines);
	std::swap(vkDestroyPipeline, rhs.vkDestroyPipeline);
	
	std::swap(vkCreatePipelineCache, rhs.vkCreatePipelineCache);
	std::swap(vkDestroyPipelineCache, rhs.vkDestroyPipelineCache);
	
	std::swap(vkCreatePipelineLayout, rhs.vkCreatePipelineLayout);
	std::swap(vkDestroyPipelineLayout, rhs.vkDestroyPipelineLayout);
	
	std::swap(vkCreateSemaphore, rhs.vkCreateSemaphore);
	std::swap(vkDestroySemaphore, rhs.vkDestroySemaphore);
	
	std::swap(vkCreateShaderModule, rhs.vkCreateShaderModule);
	std::swap(vkDestroyShaderModule, rhs.vkDestroyShaderModule);
	
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
	
	SET_PROC_ADDR(vkBeginCommandBuffer);
	SET_PROC_ADDR(vkEndCommandBuffer);
	
	SET_PROC_ADDR(vkCmdBeginRenderPass);
	SET_PROC_ADDR(vkCmdBindPipeline);
	SET_PROC_ADDR(vkCmdBindVertexBuffers);
	SET_PROC_ADDR(vkCmdClearColorImage);
	SET_PROC_ADDR(vkCmdDraw);
	SET_PROC_ADDR(vkCmdEndRenderPass);
	SET_PROC_ADDR(vkCmdPipelineBarrier);
	SET_PROC_ADDR(vkCmdPushConstants);
	SET_PROC_ADDR(vkCmdSetScissor);
	SET_PROC_ADDR(vkCmdSetViewport);
	
	SET_PROC_ADDR(vkGetDeviceQueue);
	
	SET_PROC_ADDR(vkQueueSubmit);
	SET_PROC_ADDR(vkQueueWaitIdle);
	
	SET_PROC_ADDR(vkCreateFramebuffer);
	SET_PROC_ADDR(vkCreateImageView);
	SET_PROC_ADDR(vkCreateRenderPass);
	
	SET_PROC_ADDR(vkCreateBuffer);
	SET_PROC_ADDR(vkBindBufferMemory);
	SET_PROC_ADDR(vkDestroyBuffer);
	SET_PROC_ADDR(vkGetBufferMemoryRequirements);
	
	SET_PROC_ADDR(vkAllocateCommandBuffers);
	SET_PROC_ADDR(vkFreeCommandBuffers);
	SET_PROC_ADDR(vkResetCommandBuffer);
	
	SET_PROC_ADDR(vkCreateCommandPool);
	SET_PROC_ADDR(vkDestroyCommandPool);

	SET_PROC_ADDR(vkAllocateMemory);
	SET_PROC_ADDR(vkFreeMemory);
	SET_PROC_ADDR(vkMapMemory);
	SET_PROC_ADDR(vkUnmapMemory);
	
	SET_PROC_ADDR(vkCreateGraphicsPipelines);
	SET_PROC_ADDR(vkDestroyPipeline);
	
	SET_PROC_ADDR(vkCreatePipelineCache);
	SET_PROC_ADDR(vkDestroyPipelineCache);
	
	SET_PROC_ADDR(vkCreatePipelineLayout);
	SET_PROC_ADDR(vkDestroyPipelineLayout);
	
	SET_PROC_ADDR(vkCreateSemaphore);
	SET_PROC_ADDR(vkDestroySemaphore);
	
	SET_PROC_ADDR(vkCreateShaderModule);
	SET_PROC_ADDR(vkDestroyShaderModule);
	
	SET_PROC_ADDR(vkAcquireNextImageKHR);
	SET_PROC_ADDR(vkCreateSwapchainKHR);
	SET_PROC_ADDR(vkGetSwapchainImagesKHR);
	SET_PROC_ADDR(vkQueuePresentKHR);
}

