#pragma once

#include "Node.h"

namespace Framework
{
	namespace Xml
	{
		class CFilteringNodeIterator final
		{
		public:
												CFilteringNodeIterator(CNode*, const char*);

			CNode*								operator *();
			CFilteringNodeIterator&				operator ++(int);
			bool								IsEnd() const;

		private:
			void								SeekToNext();

			CNode::OwningNodeList::const_iterator	m_nodeIterator;
			CNode*									m_node;
			const char*								m_filter;
		};
	}
}
