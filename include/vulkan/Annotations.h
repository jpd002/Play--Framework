#pragma once

#include <cassert>
#include "StructDefs.h"
#include "Instance.h"
#include "Device.h"

namespace Framework
{
	namespace Vulkan
	{
		template<bool enabled>
		class CAnnotations
		{
		public:
			CAnnotations(CInstance* instance = nullptr, CDevice* device = nullptr)
			    : m_instance(instance)
				, m_device(device)
			{
			}

			void PushCommandLabel(VkCommandBuffer commandBuffer, const char* labelName)
			{
				if constexpr(!enabled)
				{
					return;
				}

				assert(m_instance);
				if(!m_instance->vkCmdBeginDebugUtilsLabelEXT)
				{
					return;
				}

				auto labelInfo = Framework::Vulkan::DebugUtilsLabelEXT();
				labelInfo.pLabelName = labelName;
				labelInfo.color[0] = 1.0f;
				labelInfo.color[1] = 1.0f;
				labelInfo.color[2] = 1.0f;
				labelInfo.color[3] = 1.0f;
				m_instance->vkCmdBeginDebugUtilsLabelEXT(commandBuffer, &labelInfo);
			}

			void PopCommandLabel(VkCommandBuffer commandBuffer)
			{
				if constexpr (!enabled)
				{
					return;
				}

				assert(m_instance);
				if(!m_instance->vkCmdEndDebugUtilsLabelEXT)
				{
					return;
				}

				m_instance->vkCmdEndDebugUtilsLabelEXT(commandBuffer);
			}

			void SetBufferName(VkBuffer buffer, const char* name)
			{
				SetObjectName((uint64_t)buffer, name, VK_OBJECT_TYPE_BUFFER);
			}

			void SetImageName(VkImage image, const char* name)
			{
				SetObjectName((uint64_t)image, name, VK_OBJECT_TYPE_IMAGE);
			}

			void SetImageViewName(VkImageView imageView, const char* name)
			{
				SetObjectName((uint64_t)imageView, name, VK_OBJECT_TYPE_IMAGE_VIEW);
			}

		private:
			void SetObjectName(uint64_t objectHandle, const char* objectName, VkObjectType objectType)
			{
				if constexpr(!enabled)
				{
					return;
				}

				assert(m_instance);
				assert(m_device);
				if(!m_instance->vkSetDebugUtilsObjectNameEXT)
				{
					return;
				}

				auto objectNameInfo = Framework::Vulkan::DebugUtilsObjectNameInfoEXT();
				objectNameInfo.objectType = objectType;
				objectNameInfo.objectHandle = objectHandle;
				objectNameInfo.pObjectName = objectName;

				VkResult result = m_instance->vkSetDebugUtilsObjectNameEXT(*m_device, &objectNameInfo);
				CHECKVULKANERROR(result);
			}

			CInstance* m_instance = nullptr;
			CDevice* m_device = nullptr;
		};
	}
}
