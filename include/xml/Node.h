#pragma once

#include <string>
#include <list>
#include <map>
#include <memory>

namespace Framework
{

	namespace Xml
	{
		class CNode;

		typedef std::pair<std::string, std::string> AttributeType;
		typedef std::unique_ptr<CNode> OwningNodePtr;

		class CNode final
		{
		public:
			typedef std::list<CNode*>					NodeList;
			typedef std::list<OwningNodePtr>			OwningNodeList;
			typedef std::map<std::string, std::string>	AttributeList;
			typedef NodeList::iterator					NodeIterator;
			typedef OwningNodeList::iterator			OwningNodeIterator;
			typedef AttributeList::iterator				AttributeIterator;

										CNode() = default;
										CNode(std::string, bool);

			CNode* 						InsertNode(OwningNodePtr);
			CNode*						InsertTextNode(const char*);
			CNode*						InsertTagNode(const char*);
			void						InsertNodeAt(OwningNodePtr, OwningNodeIterator);
			const char*					GetText() const;
			const char*					GetInnerText() const;
			bool						IsTag() const;

			CNode*						InsertAttribute(AttributeType);
			CNode*						InsertAttribute(const char*, const char*);

			CNode*						GetParent() const;
			CNode*						GetFirstChild();
			unsigned int				GetChildCount() const;
			const OwningNodeList&		GetChildren() const;
			void						RemoveChild(OwningNodeIterator);

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
			OwningNodeList				m_children;
			AttributeList				m_attributes;
		};

	}

}
