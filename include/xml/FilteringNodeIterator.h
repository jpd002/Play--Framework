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
			virtual						~CFilteringNodeIterator();

			CNode*						operator *();
			CFilteringNodeIterator&		operator ++(int);
			bool						IsEnd() const;

		private:
			void						SeekToNext();
			CNode::NodeIterator			m_itNode;
			CNode*						m_pNode;
			const char*					m_sFilter;
		};
	}
}

#endif
