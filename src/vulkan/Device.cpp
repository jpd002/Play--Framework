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
	vkCmdBindDescriptorSets = nullptr;
	vkCmdBindIndexBuffer = nullptr;
	vkCmdBindPipeline = nullptr;
	vkCmdBindVertexBuffers = nullptr;
	vkCmdClearColorImage = nullptr;
	vkCmdCopyBuffer = nullptr;
	vkCmdCopyBufferToImage = nullptr;
	vkCmdDispatch = nullptr;
	vkCmdDraw = nullptr;
	vkCmdDrawIndexed = nullptr;
	vkCmdEndRenderPass = nullptr;
	vkCmdNextSubpass = nullptr;
	vkCmdPipelineBarrier = nullptr;
	vkCmdPushConstants = nullptr;
	vkCmdSetScissor = nullptr;
	vkCmdSetViewport = nullptr;
	vkCmdUpdateBuffer = nullptr;
	
	vkGetDeviceQueue = nullptr;
	
	vkQueueSubmit = nullptr;
	vkQueueWaitIdle = nullptr;
	
	vkBindBufferMemory = nullptr;
	vkCreateBuffer = nullptr;
	vkDestroyBuffer = nullptr;
	vkGetBufferMemoryRequirements = nullptr;
	
	vkAllocateCommandBuffers = nullptr;
	vkFreeCommandBuffers = nullptr;
	vkResetCommandBuffer = nullptr;
	
	vkCreateCommandPool = nullptr;
	vkDestroyCommandPool = nullptr;
	
	vkCreateDescriptorPool = nullptr;
	vkDestroyDescriptorPool = nullptr;
	vkResetDescriptorPool = nullptr;
	
	vkAllocateDescriptorSets = nullptr;
	vkUpdateDescriptorSets = nullptr;
	
	vkCreateDescriptorSetLayout = nullptr;
	vkDestroyDescriptorSetLayout = nullptr;
	
	vkCreateFence = nullptr;
	vkDestroyFence = nullptr;
	vkGetFenceStatus = nullptr;
	vkResetFences = nullptr;
	vkWaitForFences = nullptr;

	vkCreateFramebuffer = nullptr;
	vkDestroyFramebuffer = nullptr;
	
	vkBindImageMemory = nullptr;
	vkCreateImage = nullptr;
	vkDestroyImage = nullptr;
	vkGetImageMemoryRequirements = nullptr;
	
	vkCreateImageView = nullptr;
	vkDestroyImageView = nullptr;
	
	vkAllocateMemory = nullptr;
	vkFreeMemory = nullptr;
	vkMapMemory = nullptr;
	vkUnmapMemory = nullptr;
	
	vkCreateGraphicsPipelines = nullptr;
	vkCreateComputePipelines = nullptr;
	vkDestroyPipeline = nullptr;
	
	vkCreatePipelineCache = nullptr;
	vkDestroyPipelineCache = nullptr;
	
	vkCreatePipelineLayout = nullptr;
	vkDestroyPipelineLayout = nullptr;
	
	vkCreateRenderPass = nullptr;
	vkDestroyRenderPass = nullptr;
	
	vkCreateSampler = nullptr;
	vkDestroySampler = nullptr;
	
	vkCreateSemaphore = nullptr;
	vkDestroySemaphore = nullptr;
	
	vkCreateShaderModule = nullptr;
	vkDestroyShaderModule = nullptr;
	
	vkAcquireNextImageKHR = nullptr;
	vkCreateSwapchainKHR = nullptr;
	vkDestroySwapchainKHR = nullptr;
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
	std::swap(vkCmdBindDescriptorSets, rhs.vkCmdBindDescriptorSets);
	std::swap(vkCmdBindIndexBuffer, rhs.vkCmdBindIndexBuffer);
	std::swap(vkCmdBindPipeline, rhs.vkCmdBindPipeline);
	std::swap(vkCmdBindVertexBuffers, rhs.vkCmdBindVertexBuffers);
	std::swap(vkCmdClearColorImage, rhs.vkCmdClearColorImage);
	std::swap(vkCmdCopyBuffer, rhs.vkCmdCopyBuffer);
	std::swap(vkCmdCopyBufferToImage, rhs.vkCmdCopyBufferToImage);
	std::swap(vkCmdDispatch, rhs.vkCmdDispatch);
	std::swap(vkCmdDraw, rhs.vkCmdDraw);
	std::swap(vkCmdDrawIndexed, rhs.vkCmdDrawIndexed);
	std::swap(vkCmdEndRenderPass, rhs.vkCmdEndRenderPass);
	std::swap(vkCmdNextSubpass, rhs.vkCmdNextSubpass);
	std::swap(vkCmdPipelineBarrier, rhs.vkCmdPipelineBarrier);
	std::swap(vkCmdPushConstants, rhs.vkCmdPushConstants);
	std::swap(vkCmdSetScissor, rhs.vkCmdSetScissor);
	std::swap(vkCmdSetViewport, rhs.vkCmdSetViewport);
	std::swap(vkCmdUpdateBuffer, rhs.vkCmdUpdateBuffer);
	
	std::swap(vkGetDeviceQueue, rhs.vkGetDeviceQueue);
	
	std::swap(vkQueueSubmit, rhs.vkQueueSubmit);
	std::swap(vkQueueWaitIdle, rhs.vkQueueWaitIdle);
	
	std::swap(vkBindBufferMemory, rhs.vkBindBufferMemory);
	std::swap(vkCreateBuffer, rhs.vkCreateBuffer);
	std::swap(vkDestroyBuffer, rhs.vkDestroyBuffer);
	std::swap(vkGetBufferMemoryRequirements, rhs.vkGetBufferMemoryRequirements);
	
	std::swap(vkAllocateCommandBuffers, rhs.vkAllocateCommandBuffers);
	std::swap(vkFreeCommandBuffers, rhs.vkFreeCommandBuffers);
	std::swap(vkResetCommandBuffer, rhs.vkResetCommandBuffer);
	
	std::swap(vkCreateCommandPool, rhs.vkCreateCommandPool);
	std::swap(vkDestroyCommandPool, rhs.vkDestroyCommandPool);
	
	std::swap(vkCreateDescriptorPool, rhs.vkCreateDescriptorPool);
	std::swap(vkDestroyDescriptorPool, rhs.vkDestroyDescriptorPool);
	std::swap(vkResetDescriptorPool, rhs.vkResetDescriptorPool);
	
	std::swap(vkAllocateDescriptorSets, rhs.vkAllocateDescriptorSets);
	std::swap(vkUpdateDescriptorSets, rhs.vkUpdateDescriptorSets);
	
	std::swap(vkCreateDescriptorSetLayout, rhs.vkCreateDescriptorSetLayout);
	std::swap(vkDestroyDescriptorSetLayout, rhs.vkDestroyDescriptorSetLayout);
	
	std::swap(vkCreateFence, rhs.vkCreateFence);
	std::swap(vkDestroyFence, rhs.vkDestroyFence);
	std::swap(vkGetFenceStatus, rhs.vkGetFenceStatus);
	std::swap(vkResetFences, rhs.vkResetFences);
	std::swap(vkWaitForFences, rhs.vkWaitForFences);

	std::swap(vkCreateFramebuffer, rhs.vkCreateFramebuffer);
	std::swap(vkDestroyFramebuffer, rhs.vkDestroyFramebuffer);
	
	std::swap(vkBindImageMemory, rhs.vkBindImageMemory);
	std::swap(vkCreateImage, rhs.vkCreateImage);
	std::swap(vkDestroyImage, rhs.vkDestroyImage);
	std::swap(vkGetImageMemoryRequirements, rhs.vkGetImageMemoryRequirements);
	
	std::swap(vkCreateImageView, rhs.vkCreateImageView);
	std::swap(vkDestroyImageView, rhs.vkDestroyImageView);
	
	std::swap(vkAllocateMemory, rhs.vkAllocateMemory);
	std::swap(vkFreeMemory, rhs.vkFreeMemory);
	std::swap(vkMapMemory, rhs.vkMapMemory);
	std::swap(vkUnmapMemory, rhs.vkUnmapMemory);
	
	std::swap(vkCreateGraphicsPipelines, rhs.vkCreateGraphicsPipelines);
	std::swap(vkCreateComputePipelines, rhs.vkCreateComputePipelines);
	std::swap(vkDestroyPipeline, rhs.vkDestroyPipeline);
	
	std::swap(vkCreatePipelineCache, rhs.vkCreatePipelineCache);
	std::swap(vkDestroyPipelineCache, rhs.vkDestroyPipelineCache);
	
	std::swap(vkCreatePipelineLayout, rhs.vkCreatePipelineLayout);
	std::swap(vkDestroyPipelineLayout, rhs.vkDestroyPipelineLayout);
	
	std::swap(vkCreateRenderPass, rhs.vkCreateRenderPass);
	std::swap(vkDestroyRenderPass, rhs.vkDestroyRenderPass);
	
	std::swap(vkCreateSampler, rhs.vkCreateSampler);
	std::swap(vkDestroySampler, rhs.vkDestroySampler);
	
	std::swap(vkCreateSemaphore, rhs.vkCreateSemaphore);
	std::swap(vkDestroySemaphore, rhs.vkDestroySemaphore);
	
	std::swap(vkCreateShaderModule, rhs.vkCreateShaderModule);
	std::swap(vkDestroyShaderModule, rhs.vkDestroyShaderModule);
	
	std::swap(vkAcquireNextImageKHR, rhs.vkAcquireNextImageKHR);
	std::swap(vkCreateSwapchainKHR, rhs.vkCreateSwapchainKHR);
	std::swap(vkDestroySwapchainKHR, rhs.vkDestroySwapchainKHR);
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
	SET_PROC_ADDR(vkCmdBindDescriptorSets);
	SET_PROC_ADDR(vkCmdBindIndexBuffer);
	SET_PROC_ADDR(vkCmdBindPipeline);
	SET_PROC_ADDR(vkCmdBindVertexBuffers);
	SET_PROC_ADDR(vkCmdClearColorImage);
	SET_PROC_ADDR(vkCmdCopyBuffer);
	SET_PROC_ADDR(vkCmdCopyBufferToImage);
	SET_PROC_ADDR(vkCmdDispatch);
	SET_PROC_ADDR(vkCmdDraw);
	SET_PROC_ADDR(vkCmdDrawIndexed);
	SET_PROC_ADDR(vkCmdEndRenderPass);
	SET_PROC_ADDR(vkCmdNextSubpass);
	SET_PROC_ADDR(vkCmdPipelineBarrier);
	SET_PROC_ADDR(vkCmdPushConstants);
	SET_PROC_ADDR(vkCmdSetScissor);
	SET_PROC_ADDR(vkCmdSetViewport);
	SET_PROC_ADDR(vkCmdUpdateBuffer);
	
	SET_PROC_ADDR(vkGetDeviceQueue);
	
	SET_PROC_ADDR(vkQueueSubmit);
	SET_PROC_ADDR(vkQueueWaitIdle);
	
	SET_PROC_ADDR(vkBindBufferMemory);
	SET_PROC_ADDR(vkCreateBuffer);
	SET_PROC_ADDR(vkDestroyBuffer);
	SET_PROC_ADDR(vkGetBufferMemoryRequirements);
	
	SET_PROC_ADDR(vkAllocateCommandBuffers);
	SET_PROC_ADDR(vkFreeCommandBuffers);
	SET_PROC_ADDR(vkResetCommandBuffer);
	
	SET_PROC_ADDR(vkCreateCommandPool);
	SET_PROC_ADDR(vkDestroyCommandPool);
	
	SET_PROC_ADDR(vkCreateDescriptorPool);
	SET_PROC_ADDR(vkDestroyDescriptorPool);
	SET_PROC_ADDR(vkResetDescriptorPool);
	
	SET_PROC_ADDR(vkAllocateDescriptorSets);
	SET_PROC_ADDR(vkUpdateDescriptorSets);
	
	SET_PROC_ADDR(vkCreateDescriptorSetLayout);
	SET_PROC_ADDR(vkDestroyDescriptorSetLayout);
	
	SET_PROC_ADDR(vkCreateFence);
	SET_PROC_ADDR(vkDestroyFence);
	SET_PROC_ADDR(vkGetFenceStatus);
	SET_PROC_ADDR(vkResetFences);
	SET_PROC_ADDR(vkWaitForFences);

	SET_PROC_ADDR(vkCreateFramebuffer);
	SET_PROC_ADDR(vkDestroyFramebuffer);
	
	SET_PROC_ADDR(vkBindImageMemory);
	SET_PROC_ADDR(vkCreateImage);
	SET_PROC_ADDR(vkDestroyImage);
	SET_PROC_ADDR(vkGetImageMemoryRequirements);
	
	SET_PROC_ADDR(vkCreateImageView);
	SET_PROC_ADDR(vkDestroyImageView);
	
	SET_PROC_ADDR(vkAllocateMemory);
	SET_PROC_ADDR(vkFreeMemory);
	SET_PROC_ADDR(vkMapMemory);
	SET_PROC_ADDR(vkUnmapMemory);
	
	SET_PROC_ADDR(vkCreateGraphicsPipelines);
	SET_PROC_ADDR(vkCreateComputePipelines);
	SET_PROC_ADDR(vkDestroyPipeline);
	
	SET_PROC_ADDR(vkCreatePipelineCache);
	SET_PROC_ADDR(vkDestroyPipelineCache);
	
	SET_PROC_ADDR(vkCreatePipelineLayout);
	SET_PROC_ADDR(vkDestroyPipelineLayout);
	
	SET_PROC_ADDR(vkCreateRenderPass);
	SET_PROC_ADDR(vkDestroyRenderPass);
	
	SET_PROC_ADDR(vkCreateSampler);
	SET_PROC_ADDR(vkDestroySampler);
	
	SET_PROC_ADDR(vkCreateSemaphore);
	SET_PROC_ADDR(vkDestroySemaphore);
	
	SET_PROC_ADDR(vkCreateShaderModule);
	SET_PROC_ADDR(vkDestroyShaderModule);
	
	SET_PROC_ADDR(vkAcquireNextImageKHR);
	SET_PROC_ADDR(vkCreateSwapchainKHR);
	SET_PROC_ADDR(vkDestroySwapchainKHR);
	SET_PROC_ADDR(vkGetSwapchainImagesKHR);
	SET_PROC_ADDR(vkQueuePresentKHR);
}

