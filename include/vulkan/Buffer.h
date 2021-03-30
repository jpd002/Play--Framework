#pragma once

#include "Types.h"
#include "Device.h"

namespace Framework
{
	namespace Vulkan
	{
		class CCommandBufferPool;

		class CBuffer
		{
		public:
			        CBuffer() = default;
			        CBuffer(CDevice&, const VkPhysicalDeviceMemoryProperties&, VkBufferUsageFlags, VkMemoryPropertyFlags, uint32);
			        CBuffer(const CBuffer&) = delete;
			virtual ~CBuffer();
			
			bool IsEmpty() const;
			void Reset();
			
			CBuffer& operator =(const CBuffer&) = delete;
			CBuffer& operator =(CBuffer&&);
			         operator VkBuffer() const;

			VkDeviceMemory GetMemory() const;

			void Read(VkQueue, CCommandBufferPool&, const VkPhysicalDeviceMemoryProperties&, void*);
			void Write(VkQueue, CCommandBufferPool&, const VkPhysicalDeviceMemoryProperties&, const void*);
			
		private:
			void Create(const VkPhysicalDeviceMemoryProperties&, VkBufferUsageFlags, VkMemoryPropertyFlags, uint32);
			void MoveFrom(CBuffer&&);
			
			CDevice* m_device = nullptr;
			VkBuffer m_handle = VK_NULL_HANDLE;
			VkDeviceMemory m_memory = VK_NULL_HANDLE;

			uint32 m_size = 0;
		};
	}
}
