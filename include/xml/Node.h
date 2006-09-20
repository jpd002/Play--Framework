#ifndef _XML_NODE_H_
#define _XML_NODE_H_

#include <string>
#include <list>
#include <map>

namespace Framework
{

	namespace Xml
	{

		typedef std::pair<std::string, std::string> AttributeType;

		class CNode
		{
		public:
			typedef std::list<CNode*>					NodeList;
			typedef std::map<std::string, std::string>	AttributeList;
			typedef NodeList::iterator					NodeIterator;
			typedef AttributeList::iterator				AttributeIterator;

										CNode();
										CNode(const char*, bool);
										~CNode();

			void						InsertNode(CNode*);
			const char*					GetText() const;
			const char*					GetInnerText() const;
			bool						IsTag() const;

			void						InsertAttribute(const AttributeType&);

			CNode*						GetParent();
			CNode*						GetFirstChild();
			unsigned int				GetChildCount() const;
			NodeIterator				GetChildrenBegin();
			NodeIterator				GetChildrenEnd();

			const char*					GetAttribute(const char*) const;
			unsigned int				GetAttributeCount() const;
			AttributeIterator			GetAttributesBegin();
			AttributeIterator			GetAttributesEnd();

			CNode*						Search(const char*);
			CNode*						Select(const char*);


		private:
			std::string					m_sText;
			CNode*						m_pParent;
			bool						m_nIsTag;
			NodeList					m_Children;
			AttributeList				m_Attributes;
		};

	}

}

#endif
