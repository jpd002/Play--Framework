#ifndef _XML_NODE_H_
#define _XML_NODE_H_

#include "List.h"
#include "Str.h"
#include "StrPair.h"

namespace Framework
{

	namespace Xml
	{

		class CNode
		{
		public:
										CNode();
										CNode(const char*, bool);
										~CNode();

			void						InsertNode(CNode*);
			const char*					GetText();
			const char*					GetInnerText();
			bool						IsTag();

			void						InsertAttribute(CStrPair*);

			CNode*						GetParent();
			unsigned int				GetChildCount();
			CNode*						GetFirstChild();
			CList<CNode>::ITERATOR		GetChildIterator();

			const char*					GetAttribute(const char*);
			unsigned int				GetAttributeCount();
			CList<CStrPair>::ITERATOR	GetAttributeIterator();

			CNode*						Search(const char*);
			CNode*						Select(const char*);


		private:
			CStrA						m_sText;
			CNode*						m_pParent;
			bool						m_nIsTag;
			CList<CNode>				m_Child;
			CList<CStrPair>				m_Attribute;
		};

	}

}

#endif
