#pragma once

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
			void            FreeBuffer(VkCommandBuffer);

			void            ResetBuffers();

		private:
			typedef std::vector<VkCommandBuffer> CommandBufferArray;

			void Create(uint32_t);

			const CDevice* m_device = nullptr;
			VkCommandPool m_handle = VK_NULL_HANDLE;
		};
	}
}

