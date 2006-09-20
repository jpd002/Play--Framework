#include <string.h>
#include "xml/Writer.h"

using namespace Framework;
using namespace Framework::Xml;

CWriter::CWriter(CStream* pStream, CNode* pNode)
{
	m_pStream	= pStream;
	m_pNode		= pNode;
}

CWriter::~CWriter()
{

}

void CWriter::WriteDocument(CStream* pStream, CNode* pNode)
{
	CWriter* pWriter;
	
	pWriter = new CWriter(pStream, pNode);
	pWriter->WriteNode(0);
	delete pWriter;
}

void CWriter::WriteNode(unsigned int nLevel)
{
	if(strcmp(m_pNode->GetText(), "") == 0)
	{
		if(m_pNode->GetChildCount() == 1)
		{
			m_pNode = m_pNode->GetFirstChild();
			WriteNode(nLevel);
			return;
		}
	}

	if(m_pNode->GetChildCount() == 0)
	{
		if(m_pNode->IsTag())
		{
			DumpTabs(nLevel);
			DumpString("<");
			DumpString(m_pNode->GetText());
			DumpAttributes(m_pNode);
			DumpString(" />\r\n");
		}
		m_pNode = m_pNode->GetParent();
		return;
	}

	if(m_pNode->GetChildCount() == 1)
	{
		if(!m_pNode->GetFirstChild()->IsTag())
		{
			DumpTabs(nLevel);

			DumpString("<");
			DumpString(m_pNode->GetText());
			DumpAttributes(m_pNode);
			DumpString(">");

			DumpString(m_pNode->GetInnerText());

			DumpString("</");
			DumpString(m_pNode->GetText());
			DumpString(">\r\n");

			m_pNode = m_pNode->GetParent();

			return;
		}
	}

	DumpTabs(nLevel);
	DumpString("<");
	DumpString(m_pNode->GetText());
	DumpAttributes(m_pNode);
	DumpString(">\r\n");

	for(CNode::NodeIterator itNode(m_pNode->GetChildrenBegin()); 
		itNode != m_pNode->GetChildrenEnd(); itNode++)
	{
		m_pNode = (*itNode);
		WriteNode(nLevel + 1);
	}

	DumpTabs(nLevel);
	DumpString("</");
	DumpString(m_pNode->GetText());
	DumpString(">\r\n");

	m_pNode = m_pNode->GetParent();
}

void CWriter::DumpString(const char* sString)
{
	m_pStream->Write(sString, (unsigned int)strlen(sString));
}

void CWriter::DumpTabs(unsigned int nCount)
{
	unsigned int i;
	for(i = 0; i < nCount; i++)
	{
		m_pStream->Write8('\t');
	}
}

void CWriter::DumpAttributes(CNode* pNode)
{
	for(CNode::AttributeIterator itAttr(pNode->GetAttributesBegin());
		itAttr != pNode->GetAttributesEnd(); itAttr++)
	{
		const AttributeType& Attribute(*itAttr);

		DumpString(" ");
		DumpString(Attribute.first.c_str());
		DumpString("=\"");
		DumpString(Attribute.second.c_str());
		DumpString("\"");
	}
}
