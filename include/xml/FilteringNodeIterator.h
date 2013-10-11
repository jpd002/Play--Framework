#ifndef _XML_FILTERINGNODEITERATOR_H_
#define _XML_FILTERINGNODEITERATOR_H_

#include "Node.h"

namespace Framework
{
	namespace Xml
	{
		class CFilteringNodeIterator
		{
		public:
												CFilteringNodeIterator(CNode*, const char*);
			virtual								~CFilteringNodeIterator();

			CNode*								operator *();
			CFilteringNodeIterator&				operator ++(int);
			bool								IsEnd() const;

		private:
			void								SeekToNext();

			CNode::NodeList::const_iterator		m_nodeIterator;
			CNode*								m_node;
			const char*							m_filter;
		};
	}
}

#endif
