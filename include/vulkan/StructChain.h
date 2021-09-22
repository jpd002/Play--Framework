#pragma once

#include <vector>
#include <list>
#include "Types.h"

namespace Framework
{
	namespace Vulkan
	{
		class CStructChain
		{
		public:
			template <typename StructType>
			void AddStruct(StructType& str)
			{
				str.pNext = m_next;
				{
					auto structStart = reinterpret_cast<uint8*>(&str);
					auto structEnd = reinterpret_cast<uint8*>(&str) + sizeof(str);
					auto structBytes = Struct(structStart, structEnd);
					m_structs.push_back(std::move(structBytes));
				}
				auto lastStructIterator = m_structs.rbegin();
				m_next = lastStructIterator->data();
			}

			void* GetNext() const
			{
				return m_next;
			}

		private:
			typedef std::vector<uint8> Struct;
			std::list<Struct> m_structs;
			void* m_next = nullptr;
		};
	}
}
