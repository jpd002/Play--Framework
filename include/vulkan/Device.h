#pragma once

#include <vulkan/vulkan.h>
#include <functional>
#include "Instance.h"

#define DECLARE_FUNCTION(functionName) PFN_##functionName functionName = nullptr;

namespace Framework
{
	namespace Vulkan
	{
		class CDevice
		{
		public:
			        CDevice() = default;
			        CDevice(const CInstance&, VkPhysicalDevice, const VkDeviceCreateInfo&);
			        CDevice(const CDevice&) = delete;
			        CDevice(CDevice&&);
			
			virtual ~CDevice();
			
			void    Reset();
			
			CDevice& operator =(const CDevice&) = delete;
			         operator VkDevice() const;
			
			DECLARE_FUNCTION(vkAllocateCommandBuffers)
			DECLARE_FUNCTION(vkFreeCommandBuffers)
			
			DECLARE_FUNCTION(vkBeginCommandBuffer)
			DECLARE_FUNCTION(vkEndCommandBuffer)
			
			DECLARE_FUNCTION(vkCmdBeginRenderPass)
			DECLARE_FUNCTION(vkCmdClearColorImage)
			DECLARE_FUNCTION(vkCmdEndRenderPass)
			DECLARE_FUNCTION(vkCmdPipelineBarrier)
			DECLARE_FUNCTION(vkCmdSetScissor)
			DECLARE_FUNCTION(vkCmdSetViewport)
			
			DECLARE_FUNCTION(vkGetDeviceQueue)
			
			DECLARE_FUNCTION(vkQueueSubmit);
			DECLARE_FUNCTION(vkQueueWaitIdle);
			
			DECLARE_FUNCTION(vkCreateCommandPool)
			DECLARE_FUNCTION(vkCreateFramebuffer)
			DECLARE_FUNCTION(vkCreateImageView)
			DECLARE_FUNCTION(vkCreateRenderPass)
			
			DECLARE_FUNCTION(vkCreateSemaphore)
			DECLARE_FUNCTION(vkDestroySemaphore)
			
			//VK_KHR_swapchain
			DECLARE_FUNCTION(vkAcquireNextImageKHR)
			DECLARE_FUNCTION(vkCreateSwapchainKHR)
			DECLARE_FUNCTION(vkGetSwapchainImagesKHR)
			DECLARE_FUNCTION(vkQueuePresentKHR)
		
		private:
			void    Create(VkPhysicalDevice, const VkDeviceCreateInfo&);
			
			const CInstance* m_instance = nullptr;
			VkDevice         m_handle = VK_NULL_HANDLE;
		};
	}
}

#undef DECLARE_FUNCTION
