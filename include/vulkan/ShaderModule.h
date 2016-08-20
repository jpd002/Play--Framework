#pragma once

#include "Stream.h"
#include "Device.h"

namespace Framework 
{ 
	namespace Vulkan 
	{
		class CShaderModule
		{
		public:
			        CShaderModule() = default;
			        CShaderModule(CDevice&, Framework::CStream&);
			        CShaderModule(const CShaderModule&) = delete;
			virtual ~CShaderModule();
			
			bool IsEmpty() const;
			void Reset();
			
			CShaderModule& operator =(const CShaderModule&) = delete;
			               operator VkShaderModule() const;
			
		private:
			void Create(Framework::CStream&);
			
			const CDevice* m_device = nullptr;
			VkShaderModule m_handle = VK_NULL_HANDLE;
		};
	}
}
