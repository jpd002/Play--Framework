#include "xml/FilteringNodeIterator.h"
#include "stricmp.h"

using namespace Framework::Xml;

CFilteringNodeIterator::CFilteringNodeIterator(CNode* pNode, const char* sFilter) :
m_itNode(pNode->GetChildrenBegin())
{
	m_sFilter = sFilter;
	m_pNode = pNode;
	SeekToNext();
}

CFilteringNodeIterator::~CFilteringNodeIterator()
{

}

CNode* CFilteringNodeIterator::operator *()
{
	if(m_itNode == m_pNode->GetChildrenEnd()) return NULL;
	return (*m_itNode);
}

CFilteringNodeIterator& CFilteringNodeIterator::operator ++(int nAmount)
{
	m_itNode++;
	SeekToNext();
	return (*this);
}

bool CFilteringNodeIterator::IsEnd() const
{
	return (m_itNode == m_pNode->GetChildrenEnd());
}

void CFilteringNodeIterator::SeekToNext()
{
	for(; m_itNode != m_pNode->GetChildrenEnd(); m_itNode++)
	{
		const CNode* pNode;
		pNode = (*m_itNode);
		if(!pNode->IsTag()) continue;
		if(stricmp(pNode->GetText(), m_sFilter)) continue;
		break;
	}
}
