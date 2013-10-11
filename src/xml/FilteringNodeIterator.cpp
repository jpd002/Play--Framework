#include "xml/FilteringNodeIterator.h"
#include "stricmp.h"

using namespace Framework::Xml;

CFilteringNodeIterator::CFilteringNodeIterator(CNode* node, const char* filter)
: m_nodeIterator(std::begin(node->GetChildren()))
, m_node(node)
, m_filter(filter)
{
	SeekToNext();
}

CFilteringNodeIterator::~CFilteringNodeIterator()
{

}

CNode* CFilteringNodeIterator::operator *()
{
	if(m_nodeIterator == std::end(m_node->GetChildren())) return nullptr;
	return (*m_nodeIterator);
}

CFilteringNodeIterator& CFilteringNodeIterator::operator ++(int nAmount)
{
	m_nodeIterator++;
	SeekToNext();
	return (*this);
}

bool CFilteringNodeIterator::IsEnd() const
{
	return (m_nodeIterator == std::end(m_node->GetChildren()));
}

void CFilteringNodeIterator::SeekToNext()
{
	for(; m_nodeIterator != std::end(m_node->GetChildren()); m_nodeIterator++)
	{
		const CNode* node = (*m_nodeIterator);
		if(!node->IsTag()) continue;
		if(stricmp(node->GetText(), m_filter)) continue;
		break;
	}
}
