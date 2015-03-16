#pragma once

#include "OpenGlDef.h"

namespace Framework
{
	namespace OpenGl
	{
		template <typename ResourceTraits>
		class CResource
		{
		public:
			CResource() = default;
			CResource(const CResource&) = delete;

			CResource(CResource&& rhs)
			{
				MoveFrom(std::move(rhs));
			}

			~CResource()
			{
				Reset();
			}

			static CResource Create()
			{
				CResource resource;
				ResourceTraits::Creator(1, &resource.m_handle);
				return resource;
			}

			CResource& operator =(const CResource&) = delete;

			CResource& operator =(CResource&& rhs)
			{
				Reset();
				MoveFrom(std::move(rhs));
				return (*this);
			}

			operator GLuint() const
			{
				return m_handle;
			}

			void Reset()
			{
				if(m_handle != 0)
				{
					ResourceTraits::Deletor(1, &m_handle);
				}
				m_handle = 0;
			}

		private:
			void MoveFrom(CResource&& rhs)
			{
				assert(m_handle == 0);
				std::swap(m_handle, rhs.m_handle);
			}

			GLuint	m_handle = 0;
		};

		struct BufferTraits
		{
			static void Creator(GLsizei amount, GLuint* values)
			{
				glGenBuffers(amount, values);
			}

			static void Deletor(GLsizei amount, GLuint* values)
			{
				glDeleteBuffers(amount, values);
			}
		};

		struct VertexArrayTraits
		{
			static void Creator(GLsizei amount, GLuint* values)
			{
				glGenVertexArrays(amount, values);
			}

			static void Deletor(GLsizei amount, GLuint* values)
			{
				glDeleteVertexArrays(amount, values);
			}
		};

		typedef CResource<BufferTraits> CBuffer;
		typedef CResource<VertexArrayTraits> CVertexArray;
	}
};
