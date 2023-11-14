#pragma once

#include "Stream.h"
#include "Node.h"

namespace Framework
{
	namespace Xml
	{

		class CWriter final
		{
		public:
			static void			WriteDocument(CStream&, CNode*);

		private:
								CWriter(CStream&);
			void				WriteNode(CNode*, unsigned int);
			void				DumpString(const char*);
			void				DumpTabs(unsigned int);
			void				DumpAttributes(CNode*);
			CStream&			m_stream;
		};

	}
}
