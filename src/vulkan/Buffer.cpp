#include "vulkan/Buffer.h"
#include "vulkan/StructDefs.h"
#include "vulkan/Utils.h"

using namespace Framework::Vulkan;

CBuffer::CBuffer(CDevice& device, const VkPhysicalDeviceMemoryProperties& memoryProperties, VkBufferUsageFlags usage, uint32 size)
: m_device(&device)
{
	Create(memoryProperties, usage, size);
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

void CBuffer::Create(const VkPhysicalDeviceMemoryProperties& memoryProperties, VkBufferUsageFlags usage, uint32 size)
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
	memoryAllocateInfo.memoryTypeIndex = GetMemoryTypeIndex(memoryProperties, memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	assert(memoryAllocateInfo.memoryTypeIndex != Framework::Vulkan::VULKAN_MEMORY_TYPE_INVALID);

	result = m_device->vkAllocateMemory(*m_device, &memoryAllocateInfo, nullptr, &m_memory);
	CHECKVULKANERROR(result);
	
	result = m_device->vkBindBufferMemory(*m_device, m_handle, m_memory, 0);
	CHECKVULKANERROR(result);
}

void CBuffer::MoveFrom(CBuffer&& rhs)
{
	std::swap(m_device, rhs.m_device);
	std::swap(m_handle, rhs.m_handle);
	std::swap(m_memory, rhs.m_memory);
}
