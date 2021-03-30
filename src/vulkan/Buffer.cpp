#include <cstring>
#include "vulkan/Buffer.h"
#include "vulkan/StructDefs.h"
#include "vulkan/Utils.h"
#include "vulkan/CommandBufferPool.h"

using namespace Framework::Vulkan;

CBuffer::CBuffer(CDevice& device, const VkPhysicalDeviceMemoryProperties& memoryProperties, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, uint32 size)
: m_device(&device)
, m_size(size)
{
	Create(memoryProperties, usage, properties, size);
}

CBuffer::~CBuffer()
{
	Reset();
}

bool CBuffer::IsEmpty() const
{
	return (m_handle == VK_NULL_HANDLE);
}

void CBuffer::Reset()
{
	if(m_handle != VK_NULL_HANDLE)
	{
		assert(m_device != nullptr);
		m_device->vkDestroyBuffer(*m_device, m_handle, nullptr);
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

CBuffer& CBuffer::operator =(CBuffer&& rhs)
{
	Reset();
	MoveFrom(std::move(rhs));
	return (*this);
}

CBuffer::operator VkBuffer() const
{
	return m_handle;
}

VkDeviceMemory CBuffer::GetMemory() const
{
	return m_memory;
}

void CBuffer::Create(const VkPhysicalDeviceMemoryProperties& memoryProperties, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, uint32 size)
{
	auto result = VK_SUCCESS;

	auto bufferCreateInfo = Framework::Vulkan::BufferCreateInfo();
	bufferCreateInfo.usage = usage;
	bufferCreateInfo.size  = size;
	result = m_device->vkCreateBuffer(*m_device, &bufferCreateInfo, nullptr, &m_handle);
	CHECKVULKANERROR(result);
	
	VkMemoryRequirements memoryRequirements = {};
	m_device->vkGetBufferMemoryRequirements(*m_device, m_handle, &memoryRequirements);

	auto memoryAllocateInfo = Framework::Vulkan::MemoryAllocateInfo();
	memoryAllocateInfo.allocationSize = memoryRequirements.size;
	memoryAllocateInfo.memoryTypeIndex = GetMemoryTypeIndex(memoryProperties, memoryRequirements.memoryTypeBits, properties);
	assert(memoryAllocateInfo.memoryTypeIndex != Framework::Vulkan::VULKAN_MEMORY_TYPE_INVALID);

	result = m_device->vkAllocateMemory(*m_device, &memoryAllocateInfo, nullptr, &m_memory);
	CHECKVULKANERROR(result);
	
	result = m_device->vkBindBufferMemory(*m_device, m_handle, m_memory, 0);
	CHECKVULKANERROR(result);
}

void CBuffer::Read(VkQueue queue, CCommandBufferPool& commandBufferPool, 
	const VkPhysicalDeviceMemoryProperties& memoryProperties, void* bufferData)
{
	auto result = VK_SUCCESS;

	auto stagingBuffer = CBuffer(*m_device, memoryProperties,
		VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, m_size);
	
	auto commandBuffer = commandBufferPool.AllocateBuffer();
	
	//Start command buffer
	{
		auto commandBufferBeginInfo = Framework::Vulkan::CommandBufferBeginInfo();
		commandBufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		
		result = m_device->vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo);
		CHECKVULKANERROR(result);
	}
	
	//CopyBufferToImage
	{
		VkBufferCopy bufferCopy = {};
		bufferCopy.size = m_size;
		
		m_device->vkCmdCopyBuffer(commandBuffer, m_handle, stagingBuffer, 1, &bufferCopy);
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

	{
		void* bufferPtr = nullptr;
		result = m_device->vkMapMemory(*m_device, stagingBuffer.GetMemory(), 0, VK_WHOLE_SIZE, 0, &bufferPtr);
		CHECKVULKANERROR(result);

		memcpy(bufferData, bufferPtr, m_size);

		m_device->vkUnmapMemory(*m_device, stagingBuffer.GetMemory());
	}
}

void CBuffer::Write(VkQueue queue, CCommandBufferPool& commandBufferPool, 
	const VkPhysicalDeviceMemoryProperties& memoryProperties, const void* bufferData)
{
	auto result = VK_SUCCESS;

	auto stagingBuffer = CBuffer(*m_device, memoryProperties,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, m_size);
	
	{
		void* bufferPtr = nullptr;
		result = m_device->vkMapMemory(*m_device, stagingBuffer.GetMemory(), 0, VK_WHOLE_SIZE, 0, &bufferPtr);
		CHECKVULKANERROR(result);

		memcpy(bufferPtr, bufferData, m_size);

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
	
	//CopyBufferToImage
	{
		VkBufferCopy bufferCopy = {};
		bufferCopy.size = m_size;
		
		m_device->vkCmdCopyBuffer(commandBuffer, stagingBuffer, m_handle, 1, &bufferCopy);
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

void CBuffer::MoveFrom(CBuffer&& rhs)
{
	std::swap(m_device, rhs.m_device);
	std::swap(m_handle, rhs.m_handle);
	std::swap(m_memory, rhs.m_memory);
	std::swap(m_size, rhs.m_size);
}
