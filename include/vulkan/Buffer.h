#pragma once

#include "Types.h"
#include "Device.h"

namespace Framework
{
	namespace Vulkan
	{
		class CBuffer
		{
		public:
			        CBuffer() = default;
			        CBuffer(CDevice&, const VkPhysicalDeviceMemoryProperties&, VkBufferUsageFlags, uint32);
			        CBuffer(const CBuffer&) = delete;
			virtual ~CBuffer();
			
			bool IsEmpty() const;
			void Reset();
			
			CBuffer& operator =(const CBuffer&) = delete;
			CBuffer& operator =(CBuffer&&);
			         operator VkBuffer() const;

			VkDeviceMemory GetMemory() const;
			
		private:
			void Create(const VkPhysicalDeviceMemoryProperties&, VkBufferUsageFlags, uint32);
			void MoveFrom(CBuffer&&);
			
			const CDevice* m_device = nullptr;
			VkBuffer m_handle = VK_NULL_HANDLE;
			VkDeviceMemory m_memory = VK_NULL_HANDLE;
		};
	}
}
