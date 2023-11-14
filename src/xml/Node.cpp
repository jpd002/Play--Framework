#include <assert.h>
#include "xml/Node.h"
#include "xml/FilteringNodeIterator.h"
#include "stricmp.h"
#include <string>

using namespace Framework;
using namespace Framework::Xml;

CNode::CNode(std::string text, bool isTag)
: m_text(std::move(text))
, m_isTag(isTag)
{

}

CNode* CNode::InsertNode(OwningNodePtr node)
{
	assert(node->m_parent == nullptr);
	node->m_parent = this;
	auto result = node.get();
	m_children.push_back(std::move(node));
	return result;
}

CNode* CNode::InsertTextNode(const char* text)
{
	return InsertNode(std::make_unique<CNode>(text, false));
}

CNode* CNode::InsertTagNode(const char* name)
{
	return InsertNode(std::make_unique<CNode>(name, true));
}

void CNode::InsertNodeAt(OwningNodePtr node, OwningNodeIterator itPosition)
{
	assert(node->m_parent == nullptr);
	node->m_parent = this;
	m_children.insert(itPosition, std::move(node));
}

const char* CNode::GetText() const
{
	return m_text.c_str();
}

const char* CNode::GetInnerText() const
{
	if(m_children.size() != 1) return NULL;
	return (*m_children.begin())->GetText();
}

bool CNode::IsTag() const
{
	return m_isTag;
}

CNode* CNode::InsertAttribute(AttributeType attribute)
{
	m_attributes.insert(std::move(attribute));
	return this;
}

CNode* CNode::InsertAttribute(const char* name, const char* value)
{
	return InsertAttribute(AttributeType(name, value));
}

CNode* CNode::GetParent() const
{
	return m_parent;
}

unsigned int CNode::GetChildCount() const
{
	return static_cast<unsigned int>(m_children.size());
}

CNode* CNode::GetFirstChild()
{
	assert(!m_children.empty());
	return m_children.begin()->get();
}

const CNode::OwningNodeList& CNode::GetChildren() const
{
	return m_children;
}

void CNode::RemoveChild(OwningNodeIterator nodeIterator)
{
	m_children.erase(nodeIterator);
}

const char* CNode::GetAttribute(const char* name) const
{
	auto attributeIterator = m_attributes.find(name);
	return (attributeIterator == m_attributes.end()) ? nullptr : (*attributeIterator).second.c_str();
}

unsigned int CNode::GetAttributeCount() const
{
	return static_cast<unsigned int>(m_attributes.size());
}

const CNode::AttributeList& CNode::GetAttributes() const
{
	return m_attributes;
}

CNode* CNode::Search(const char* name)
{
	for(const auto& node : m_children)
	{
		if(!node->IsTag()) continue;
		if(!stricmp(node->GetText(), name))
		{
			return node.get();
		}
	}
	return nullptr;
}

template <bool nSingle>
CNode::NodeList CNode::SelectNodesImpl(const char* sPath)
{
	CNode* node(this);
	std::string sCurr(sPath);

	while(1)
	{
		//Check if we're at the end of an expression
		size_t nPosition;
		nPosition = sCurr.find('/');
		if(nPosition == std::string::npos)
		{
			//We are.
			break;
		}

		std::string sNext(sCurr.begin(), sCurr.begin() + nPosition);
		node = node->Search(sNext.c_str());

		if(node == nullptr)
		{
			return NodeList();
		}

		sCurr = std::string(sCurr.begin() + nPosition + 1, sCurr.end());
	}

	NodeList TempList;

	for(CFilteringNodeIterator itNode(node, sCurr.c_str()); !itNode.IsEnd(); itNode++)
	{
		TempList.push_back(*itNode);
		if(nSingle) break;
	}

	return TempList;
}

CNode* CNode::Select(const char* sPath)
{
	auto nodes(SelectNodesImpl<true>(sPath));
	if(nodes.size() == 0) return nullptr;
	return *nodes.begin();
}

CNode::NodeList CNode::SelectNodes(const char* sPath)
{
	return SelectNodesImpl<false>(sPath);
}
