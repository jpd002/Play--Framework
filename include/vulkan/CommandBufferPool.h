#pragma once

#include <vector>
#include "Types.h"
#include "Device.h"

namespace Framework
{
	namespace Vulkan
	{
		class CCommandBufferPool
		{
		public:
				CCommandBufferPool() = default;
			        CCommandBufferPool(CDevice&, uint32_t);
				CCommandBufferPool(const CCommandBufferPool&) = delete;
				CCommandBufferPool(CCommandBufferPool&&);

			virtual ~CCommandBufferPool();

			bool IsEmpty() const;
			void Reset();

			CCommandBufferPool& operator =(const CCommandBufferPool&) = delete;
			CCommandBufferPool& operator =(CCommandBufferPool&&);

			VkCommandBuffer AllocateBuffer();
			void            ResetBuffers();

		private:
			typedef std::vector<VkCommandBuffer> CommandBufferArray;

			void Create(uint32_t);

			const CDevice* m_device = nullptr;
			VkCommandPool m_handle = VK_NULL_HANDLE;
			CommandBufferArray m_buffers;
			uint32 m_bufferIndex = 0;
		};
	}
}

