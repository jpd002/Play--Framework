#include "vulkan/CommandBufferPool.h"
#include "vulkan/StructDefs.h"

using namespace Framework::Vulkan;

CCommandBufferPool::CCommandBufferPool(CDevice& device, uint32_t queueFamilyIndex)
: m_device(&device)
{
	Create(queueFamilyIndex);
}

CCommandBufferPool::~CCommandBufferPool()
{
	Reset();
}

bool CCommandBufferPool::IsEmpty() const
{
	return (m_handle == VK_NULL_HANDLE);
}

void CCommandBufferPool::Reset()
{
	if(m_handle != VK_NULL_HANDLE)
	{
		assert(m_device != nullptr);
		m_device->vkFreeCommandBuffers(*m_device, m_handle, m_buffers.size(), m_buffers.data());
		m_buffers.clear();
		m_bufferIndex = 0;
		m_device->vkDestroyCommandPool(*m_device, m_handle, nullptr);
		m_device = nullptr;
		m_handle = VK_NULL_HANDLE;
	}
}

CCommandBufferPool& CCommandBufferPool::operator =(CCommandBufferPool&& rhs)
{
	Reset();

	std::swap(m_device, rhs.m_device);
	std::swap(m_handle, rhs.m_handle);
	
	std::swap(m_buffers, rhs.m_buffers);
	std::swap(m_bufferIndex, rhs.m_bufferIndex);
	
	return (*this);
}

VkCommandBuffer CCommandBufferPool::AllocateBuffer()
{
	VkCommandBuffer buffer = VK_NULL_HANDLE;
	if(m_bufferIndex < m_buffers.size())
	{
		buffer = m_buffers[m_bufferIndex++];
		auto result = m_device->vkResetCommandBuffer(buffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
		CHECKVULKANERROR(result);
	}
	else
	{
		auto bufferAllocateInfo = Framework::Vulkan::CommandBufferAllocateInfo();
		bufferAllocateInfo.commandPool        = m_handle;
		bufferAllocateInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		bufferAllocateInfo.commandBufferCount = 1;

		auto result = m_device->vkAllocateCommandBuffers(*m_device, &bufferAllocateInfo, &buffer);
		CHECKVULKANERROR(result);
		
		m_buffers.push_back(buffer);
		m_bufferIndex++;
	}
	return buffer;
}

void CCommandBufferPool::ResetBuffers()
{
	m_bufferIndex = 0;
}

void CCommandBufferPool::Create(uint32_t queueFamilyIndex)
{
	auto commandPoolCreateInfo = Framework::Vulkan::CommandPoolCreateInfo();
	commandPoolCreateInfo.queueFamilyIndex = queueFamilyIndex;
	commandPoolCreateInfo.flags            = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	auto result = m_device->vkCreateCommandPool(*m_device, &commandPoolCreateInfo, nullptr, &m_handle);
	CHECKVULKANERROR(result);
}
