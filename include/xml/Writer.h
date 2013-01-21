#ifndef _XML_WRITER_H_
#define _XML_WRITER_H_

#include "Stream.h"
#include "Node.h"

namespace Framework
{
	namespace Xml
	{

		class CWriter
		{
		public:
			static void			WriteDocument(CStream&, CNode*);

		private:
								CWriter(CStream&, CNode*);
								~CWriter();
			void				WriteNode(unsigned int);
			void				DumpString(const char*);
			void				DumpTabs(unsigned int);
			void				DumpAttributes(CNode*);
			CNode*				m_node;
			CStream&			m_stream;
		};

	}
}

#endif
