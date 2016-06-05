#include "vulkan/ShaderModule.h"
#include "vulkan/StructDefs.h"

using namespace Framework::Vulkan;

CShaderModule::CShaderModule(Framework::Vulkan::CDevice& device, Framework::CStream& stream)
: m_device(&device)
{
	Create(stream);
}

bool CShaderModule::IsEmpty() const
{
	return (m_handle == VK_NULL_HANDLE);
}

void CShaderModule::Reset()
{
	if(m_handle != VK_NULL_HANDLE)
	{
		assert(m_device != nullptr);
		m_device->vkDestroyShaderModule(*m_device, m_handle, nullptr);
		m_device = nullptr;
		m_handle = VK_NULL_HANDLE;
	}
}

CShaderModule::operator VkShaderModule() const
{
	return m_handle;
}

void CShaderModule::Create(Framework::CStream& stream)
{
	auto shaderLength = stream.GetLength();
	assert((shaderLength & 0x03) == 0);
	uint32* shader = new uint32[shaderLength / 4];
	stream.Read(shader, shaderLength);
	
	auto shaderModuleCreateInfo = Framework::Vulkan::ShaderModuleCreateInfo();
	shaderModuleCreateInfo.codeSize = shaderLength;
	shaderModuleCreateInfo.pCode    = shader;

	auto result = m_device->vkCreateShaderModule(*m_device, &shaderModuleCreateInfo, nullptr, &m_handle);
	CHECKVULKANERROR(result);
	
	delete [] shader;
}
