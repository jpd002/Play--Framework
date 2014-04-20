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

			CNode* 						InsertNode(CNode*);
			CNode*						InsertTextNode(const char*);
			CNode*						InsertTagNode(const char*);
			void						InsertNodeAt(CNode*, NodeIterator&);
			const char*					GetText() const;
			const char*					GetInnerText() const;
			bool						IsTag() const;

			CNode*						InsertAttribute(const AttributeType&);
			CNode*						InsertAttribute(const char*, const char*);

			CNode*						GetParent() const;
			CNode*						GetFirstChild();
			unsigned int				GetChildCount() const;
			const NodeList&				GetChildren() const;
			void						RemoveChild(NodeIterator);

			const char*					GetAttribute(const char*) const;
			unsigned int				GetAttributeCount() const;
			const AttributeList&		GetAttributes() const;

			CNode*						Search(const char*);
			CNode*						Select(const char*);
			NodeList					SelectNodes(const char*);

		private:
			template <bool> NodeList	SelectNodesImpl(const char*);

			std::string					m_text;
			CNode*						m_parent = nullptr;
			bool						m_isTag = false;
			NodeList					m_children;
			AttributeList				m_attributes;
		};

	}

}

#endif
