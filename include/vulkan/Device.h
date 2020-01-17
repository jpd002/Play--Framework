#pragma once

#include <functional>
#include "VulkanDef.h"
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
			
			bool    IsEmpty() const;
			void    Reset();
			
			CDevice& operator =(const CDevice&) = delete;
			CDevice& operator =(CDevice&&);
			         operator VkDevice() const;
			
			DECLARE_FUNCTION(vkBeginCommandBuffer)
			DECLARE_FUNCTION(vkEndCommandBuffer)
			
			DECLARE_FUNCTION(vkCmdBeginRenderPass)
			DECLARE_FUNCTION(vkCmdBindDescriptorSets)
			DECLARE_FUNCTION(vkCmdBindIndexBuffer)
			DECLARE_FUNCTION(vkCmdBindPipeline)
			DECLARE_FUNCTION(vkCmdBindVertexBuffers)
			DECLARE_FUNCTION(vkCmdClearColorImage)
			DECLARE_FUNCTION(vkCmdCopyBufferToImage)
			DECLARE_FUNCTION(vkCmdDispatch)
			DECLARE_FUNCTION(vkCmdDraw)
			DECLARE_FUNCTION(vkCmdDrawIndexed)
			DECLARE_FUNCTION(vkCmdEndRenderPass)
			DECLARE_FUNCTION(vkCmdNextSubpass)
			DECLARE_FUNCTION(vkCmdPipelineBarrier)
			DECLARE_FUNCTION(vkCmdPushConstants)
			DECLARE_FUNCTION(vkCmdSetScissor)
			DECLARE_FUNCTION(vkCmdSetViewport)
			DECLARE_FUNCTION(vkCmdUpdateBuffer)
			
			DECLARE_FUNCTION(vkGetDeviceQueue)
			
			DECLARE_FUNCTION(vkQueueSubmit);
			DECLARE_FUNCTION(vkQueueWaitIdle);
			
			//Buffer
			DECLARE_FUNCTION(vkBindBufferMemory)
			DECLARE_FUNCTION(vkCreateBuffer)
			DECLARE_FUNCTION(vkDestroyBuffer)
			DECLARE_FUNCTION(vkGetBufferMemoryRequirements)
			
			//Command Buffer
			DECLARE_FUNCTION(vkAllocateCommandBuffers)
			DECLARE_FUNCTION(vkFreeCommandBuffers)
			DECLARE_FUNCTION(vkResetCommandBuffer)
			
			//Command Pool
			DECLARE_FUNCTION(vkCreateCommandPool)
			DECLARE_FUNCTION(vkDestroyCommandPool)
			
			//Descriptor Pool
			DECLARE_FUNCTION(vkCreateDescriptorPool)
			DECLARE_FUNCTION(vkDestroyDescriptorPool)
			DECLARE_FUNCTION(vkResetDescriptorPool)
			
			//Descriptor Set
			DECLARE_FUNCTION(vkAllocateDescriptorSets)
			DECLARE_FUNCTION(vkUpdateDescriptorSets)
			
			//Descriptor Set Layout
			DECLARE_FUNCTION(vkCreateDescriptorSetLayout)
			DECLARE_FUNCTION(vkDestroyDescriptorSetLayout)
			
			//Fence
			DECLARE_FUNCTION(vkCreateFence)
			DECLARE_FUNCTION(vkDestroyFence)
			DECLARE_FUNCTION(vkGetFenceStatus)
			DECLARE_FUNCTION(vkResetFences)
			DECLARE_FUNCTION(vkWaitForFences)

			//Framebuffer
			DECLARE_FUNCTION(vkCreateFramebuffer)
			DECLARE_FUNCTION(vkDestroyFramebuffer)
			
			//Image
			DECLARE_FUNCTION(vkBindImageMemory)
			DECLARE_FUNCTION(vkCreateImage)
			DECLARE_FUNCTION(vkDestroyImage)
			DECLARE_FUNCTION(vkGetImageMemoryRequirements)
			
			//Image View
			DECLARE_FUNCTION(vkCreateImageView)
			DECLARE_FUNCTION(vkDestroyImageView)
			
			//Memory
			DECLARE_FUNCTION(vkAllocateMemory)
			DECLARE_FUNCTION(vkFreeMemory)
			DECLARE_FUNCTION(vkMapMemory)
			DECLARE_FUNCTION(vkUnmapMemory)
			
			//Pipeline
			DECLARE_FUNCTION(vkCreateGraphicsPipelines)
			DECLARE_FUNCTION(vkCreateComputePipelines)
			DECLARE_FUNCTION(vkDestroyPipeline)
			
			//Pipeline Cache
			DECLARE_FUNCTION(vkCreatePipelineCache)
			DECLARE_FUNCTION(vkDestroyPipelineCache)
			
			//Pipeline Layout
			DECLARE_FUNCTION(vkCreatePipelineLayout)
			DECLARE_FUNCTION(vkDestroyPipelineLayout)
			
			//Render Pass
			DECLARE_FUNCTION(vkCreateRenderPass)
			DECLARE_FUNCTION(vkDestroyRenderPass)
			
			//Sampler
			DECLARE_FUNCTION(vkCreateSampler)
			DECLARE_FUNCTION(vkDestroySampler)
			
			//Semaphore
			DECLARE_FUNCTION(vkCreateSemaphore)
			DECLARE_FUNCTION(vkDestroySemaphore)
			
			//Shader Module
			DECLARE_FUNCTION(vkCreateShaderModule)
			DECLARE_FUNCTION(vkDestroyShaderModule)
			
			//VK_KHR_swapchain
			DECLARE_FUNCTION(vkAcquireNextImageKHR)
			DECLARE_FUNCTION(vkCreateSwapchainKHR)
			DECLARE_FUNCTION(vkDestroySwapchainKHR)
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
