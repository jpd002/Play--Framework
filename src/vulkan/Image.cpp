#include <cstring>
#include "vulkan/Image.h"
#include "vulkan/StructDefs.h"
#include "vulkan/Utils.h"
#include "vulkan/Buffer.h"
#include "vulkan/CommandBufferPool.h"

using namespace Framework::Vulkan;

CImage::CImage(CDevice& device, const VkPhysicalDeviceMemoryProperties& memoryProperties,
	VkImageUsageFlags usage, VkFormat format, uint32 width, uint32 height)
: m_device(&device)
, m_format(format)
, m_width(width)
, m_height(height)
{
	Create(memoryProperties, usage, format, width, height);
}

CImage::CImage(CImage&& rhs)
{
	MoveFrom(std::move(rhs));
}

CImage::~CImage()
{
	Reset();
}

bool CImage::IsEmpty() const
{
	return (m_handle == VK_NULL_HANDLE);
}

void CImage::Reset()
{
	if(m_handle != VK_NULL_HANDLE)
	{
		assert(m_device != nullptr);
		m_device->vkDestroyImage(*m_device, m_handle, nullptr);
		m_handle = VK_NULL_HANDLE;
	}

	if(m_memory != VK_NULL_HANDLE)
	{
		assert(m_device != nullptr);
		m_device->vkFreeMemory(*m_device, m_memory, nullptr);
		m_memory = VK_NULL_HANDLE;
	}

	m_device = nullptr;
}

CImage& CImage::operator =(CImage&& rhs)
{
	Reset();
	MoveFrom(std::move(rhs));
	return (*this);
}

CImage::operator VkImage() const
{
	return m_handle;
}

uint32 CImage::GetLinearSize() const
{
	switch(m_format)
	{
	case VK_FORMAT_R32_UINT:
		return m_width * m_height * sizeof(uint32);
	default:
		assert(false);
		return 0;
	}
}

VkImageView CImage::CreateImageView()
{
	auto imageViewCreateInfo = Framework::Vulkan::ImageViewCreateInfo();
	imageViewCreateInfo.image    = m_handle;
	imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	imageViewCreateInfo.format   = m_format;
	imageViewCreateInfo.components = 
	{
		VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, 
		VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A 
	};
	imageViewCreateInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };

	VkImageView imageView = VK_NULL_HANDLE;
	auto result = m_device->vkCreateImageView(*m_device, &imageViewCreateInfo, nullptr, &imageView);
	CHECKVULKANERROR(result);

	return imageView;
}

void CImage::SetLayout(VkQueue queue, CCommandBufferPool& commandBufferPool,
	VkImageLayout layout, VkAccessFlags accessFlags)
{
	auto result = VK_SUCCESS;
	auto commandBuffer = commandBufferPool.AllocateBuffer();
	
	//Start command buffer
	{
		auto commandBufferBeginInfo = Framework::Vulkan::CommandBufferBeginInfo();
		commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		
		result = m_device->vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo);
		CHECKVULKANERROR(result);
	}

	{
		auto imageMemoryBarrier = Framework::Vulkan::ImageMemoryBarrier();
		imageMemoryBarrier.image               = m_handle;
		imageMemoryBarrier.oldLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
		imageMemoryBarrier.newLayout           = layout;
		imageMemoryBarrier.srcAccessMask       = 0;
		imageMemoryBarrier.dstAccessMask       = accessFlags;
		imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemoryBarrier.subresourceRange    = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
		
		m_device->vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
			0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
	}
	
	//Finish command buffer
	result = m_device->vkEndCommandBuffer(commandBuffer);
	CHECKVULKANERROR(result);
	
	//Submit command buffer
	{
		auto submitInfo = Framework::Vulkan::SubmitInfo();
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers    = &commandBuffer;
		
		result = m_device->vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
		CHECKVULKANERROR(result);
	}
	
	result = m_device->vkQueueWaitIdle(queue);
	CHECKVULKANERROR(result);
}

void CImage::Fill(VkQueue queue, CCommandBufferPool& commandBufferPool, 
	const VkPhysicalDeviceMemoryProperties& memoryProperties, const void* imageData)
{
	auto result = VK_SUCCESS;

	auto imageSize = GetLinearSize();
	auto stagingBuffer = CBuffer(*m_device, memoryProperties, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, imageSize);
	
	{
		void* bufferPtr = nullptr;
		result = m_device->vkMapMemory(*m_device, stagingBuffer.GetMemory(), 0, VK_WHOLE_SIZE, 0, &bufferPtr);
		CHECKVULKANERROR(result);

		memcpy(bufferPtr, imageData, imageSize);

		m_device->vkUnmapMemory(*m_device, stagingBuffer.GetMemory());
	}

	auto commandBuffer = commandBufferPool.AllocateBuffer();
	
	//Start command buffer
	{
		auto commandBufferBeginInfo = Framework::Vulkan::CommandBufferBeginInfo();
		commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		
		result = m_device->vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo);
		CHECKVULKANERROR(result);
	}
	
	//Transition image from whatever state to TRANSFER_DST_OPTIMAL
	{
		auto imageMemoryBarrier = Framework::Vulkan::ImageMemoryBarrier();
		imageMemoryBarrier.image               = m_handle;
		imageMemoryBarrier.oldLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
		imageMemoryBarrier.newLayout           = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		imageMemoryBarrier.srcAccessMask       = 0;
		imageMemoryBarrier.dstAccessMask       = VK_ACCESS_TRANSFER_WRITE_BIT;
		imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		imageMemoryBarrier.subresourceRange    = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
		
		m_device->vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
			0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
	}
	
	//CopyBufferToImage
	{
		VkBufferImageCopy bufferImageCopy = {};
		bufferImageCopy.bufferRowLength    = m_width;
		bufferImageCopy.imageSubresource   = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
		bufferImageCopy.imageExtent.width  = m_width;
		bufferImageCopy.imageExtent.height = m_height;
		bufferImageCopy.imageExtent.depth  = 1;
		
		m_device->vkCmdCopyBufferToImage(commandBuffer, stagingBuffer, m_handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1, &bufferImageCopy);
	}

	//Finish command buffer
	result = m_device->vkEndCommandBuffer(commandBuffer);
	CHECKVULKANERROR(result);
	
	//Submit command buffer
	{
		auto submitInfo = Framework::Vulkan::SubmitInfo();
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers    = &commandBuffer;
		
		result = m_device->vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
		CHECKVULKANERROR(result);
	}
	
	//Wait for queue ops to complete
	result = m_device->vkQueueWaitIdle(queue);
	CHECKVULKANERROR(result);
}

void CImage::Create(const VkPhysicalDeviceMemoryProperties& memoryProperties,
	VkImageUsageFlags usage, VkFormat format, uint32 width, uint32 height)
{
	auto result = VK_SUCCESS;

	{
		auto imageCreateInfo = Framework::Vulkan::ImageCreateInfo();
		imageCreateInfo.imageType     = VK_IMAGE_TYPE_2D;
		imageCreateInfo.format        = format;
		imageCreateInfo.extent.width  = width;
		imageCreateInfo.extent.height = height;
		imageCreateInfo.extent.depth  = 1;
		imageCreateInfo.mipLevels     = 1;
		imageCreateInfo.arrayLayers   = 1;
		imageCreateInfo.samples       = VK_SAMPLE_COUNT_1_BIT;
		imageCreateInfo.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;
		imageCreateInfo.tiling        = VK_IMAGE_TILING_OPTIMAL;
		imageCreateInfo.usage         = usage;
		imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		auto result = m_device->vkCreateImage(*m_device, &imageCreateInfo, nullptr, &m_handle);
		CHECKVULKANERROR(result);
	}

	{
		VkMemoryRequirements memoryRequirements = {};
		m_device->vkGetImageMemoryRequirements(*m_device, m_handle, &memoryRequirements);

		auto memoryAllocateInfo = Framework::Vulkan::MemoryAllocateInfo();
		memoryAllocateInfo.allocationSize  = memoryRequirements.size;
		memoryAllocateInfo.memoryTypeIndex = Framework::Vulkan::GetMemoryTypeIndex(
			memoryProperties, memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

		auto result = m_device->vkAllocateMemory(*m_device, &memoryAllocateInfo, nullptr, &m_memory);
		CHECKVULKANERROR(result);
	}
	
	m_device->vkBindImageMemory(*m_device, m_handle, m_memory, 0);
}

void CImage::MoveFrom(CImage&& rhs)
{
	std::swap(m_device, rhs.m_device);
	std::swap(m_handle, rhs.m_handle);
	std::swap(m_memory, rhs.m_memory);
	std::swap(m_format, rhs.m_format);
	std::swap(m_width, rhs.m_width);
	std::swap(m_height, rhs.m_height);
}
