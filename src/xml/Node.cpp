#include <assert.h>
#include "xml/Node.h"
#include "stricmp.h"

using namespace Framework;
using namespace Framework::Xml;

CNode::CNode()
{
	m_pParent = NULL;
}

CNode::CNode(const char* sText, bool nIsTag)
{
	m_pParent = NULL;
	m_sText = sText;
	m_nIsTag = nIsTag;
}

CNode::~CNode()
{
	while(m_Children.size() != 0)
	{
		delete (*m_Children.rbegin());
		m_Children.pop_back();
	}
}

CNode* CNode::InsertNode(CNode* pNode)
{
	assert(pNode->m_pParent == NULL);
	pNode->m_pParent = this;
	m_Children.push_back(pNode);
    return pNode;
}

void CNode::InsertNodeAt(CNode* pNode, NodeIterator& itPosition)
{
	assert(pNode->m_pParent == NULL);
	pNode->m_pParent = this;
	m_Children.insert(itPosition, pNode);
}

const char* CNode::GetText() const
{
	return m_sText.c_str();
}

const char* CNode::GetInnerText() const
{
	if(m_Children.size() != 1) return NULL;
	return (*m_Children.begin())->GetText();
}

bool CNode::IsTag() const
{
	return m_nIsTag;
}

CNode* CNode::InsertAttribute(const AttributeType& Attribute)
{
	m_Attributes[Attribute.first] = Attribute.second;
    return this;
}

CNode* CNode::InsertAttribute(const char* sName, const char* sValue)
{
    return InsertAttribute(AttributeType(sName, sValue));
}

CNode* CNode::GetParent()
{
	return m_pParent;
}

unsigned int CNode::GetChildCount() const
{
	return static_cast<unsigned int>(m_Children.size());
}

CNode* CNode::GetFirstChild()
{
	assert(m_Children.size() > 0);
	return *m_Children.begin();
}

CNode::NodeIterator CNode::GetChildrenBegin()
{
	return m_Children.begin();
}

CNode::NodeIterator CNode::GetChildrenEnd()
{
	return m_Children.end();
}

void CNode::RemoveChild(NodeIterator itNode)
{
	m_Children.erase(itNode);
}

const char* CNode::GetAttribute(const char* sName) const
{
	AttributeList::const_iterator itAttribute;
	itAttribute = m_Attributes.find(sName);

	return (itAttribute == m_Attributes.end()) ? NULL : (*itAttribute).second.c_str();
}

unsigned int CNode::GetAttributeCount() const
{
	return static_cast<unsigned int>(m_Attributes.size());
}

CNode::AttributeIterator CNode::GetAttributesBegin()
{
	return m_Attributes.begin();
}

CNode::AttributeIterator CNode::GetAttributesEnd()
{
	return m_Attributes.end();
}

CNode* CNode::Search(const char* sName)
{
	for(NodeList::iterator itNode(m_Children.begin()); itNode != m_Children.end(); itNode++)
	{
		CNode* pNode;
		pNode = (*itNode);

		if(!pNode->IsTag()) continue;
		if(!stricmp(pNode->GetText(), sName))
		{
			return pNode;
		}
	}

	return NULL;
}

CNode* CNode::Select(const char* sPath)
{
	const char* sCurr;
	const char* sNext;
	char sName[256];
	CNode* pNode;

	sCurr = sPath;
	sNext = strchr(sCurr, '/');
	if(sNext == NULL)
	{
		return Search(sPath);
	}
	else
	{
		strncpy(sName, sPath, (sNext - sCurr));
		sName[(sNext - sCurr)] = '\0';
		pNode = Search(sName);
		if(pNode != NULL)
		{
			return pNode->Select(sNext + 1);
		}
		return NULL;
	}	
}
