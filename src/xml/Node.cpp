#include <assert.h>
#include "xml/Node.h"

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
	while(m_Child.Count() != 0)
	{
		delete m_Child.Pull();
	}
	while(m_Attribute.Count() != 0)
	{
		delete m_Attribute.Pull();
	}
}

void CNode::InsertNode(CNode* pNode)
{
	assert(pNode->m_pParent == NULL);
	pNode->m_pParent = this;
	m_Child.Insert(pNode);
}

const char* CNode::GetText()
{
	return m_sText;
}

const char* CNode::GetInnerText()
{
	if(m_Child.Count() != 1) return NULL;
	return m_Child.Find(0)->GetText();
}

bool CNode::IsTag()
{
	return m_nIsTag;
}

void CNode::InsertAttribute(CStrPair* pAttribute)
{
	m_Attribute.Insert(pAttribute);
}

CNode* CNode::GetParent()
{
	return m_pParent;
}

unsigned int CNode::GetChildCount()
{
	return m_Child.Count();
}

CNode* CNode::GetFirstChild()
{
	CList<CNode>::ITERATOR itNode;
	itNode = m_Child.Begin();
	return (*itNode);
}

CList<CNode>::ITERATOR CNode::GetChildIterator()
{
	CList<CNode>::ITERATOR itNode;
	itNode = m_Child.Begin();
	return itNode;
}

const char* CNode::GetAttribute(const char* sName)
{
	CList<CStrPair>::ITERATOR itAttribute;
	CStrPair* pAttribute;

	for(itAttribute = m_Attribute.Begin(); itAttribute.HasNext(); itAttribute++)
	{
		pAttribute = (*itAttribute);
		if(!strcmp(sName, (*pAttribute)[0]))
		{
			return (*pAttribute)[1];
		}
	}

	return NULL;
}

unsigned int CNode::GetAttributeCount()
{
	return m_Attribute.Count();
}

CList<CStrPair>::ITERATOR CNode::GetAttributeIterator()
{
	CList<CStrPair>::ITERATOR itAttribute;
	itAttribute = m_Attribute.Begin();
	return itAttribute;
}

CNode* CNode::Search(const char* sName)
{
	CList<CNode>::ITERATOR itNode;
	CNode* pNode;

	for(itNode = m_Child.Begin(); itNode.HasNext(); itNode++)
	{
		pNode = (*itNode);
		if(!pNode->IsTag()) continue;
		if(!_stricmp(pNode->GetText(), sName))
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
