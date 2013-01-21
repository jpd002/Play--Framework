#include <string.h>
#include "xml/Writer.h"
#include "xml/Utils.h"

using namespace Framework;
using namespace Framework::Xml;

CWriter::CWriter(CStream& stream, CNode* node)
: m_stream(stream)
, m_node(node)
{

}

CWriter::~CWriter()
{

}

void CWriter::WriteDocument(CStream& stream, CNode* node)
{
	CWriter writer(stream, node);
	writer.WriteNode(0);
}

void CWriter::WriteNode(unsigned int nLevel)
{
	if(strcmp(m_node->GetText(), "") == 0)
	{
		if(m_node->GetChildCount() == 1)
		{
			m_node = m_node->GetFirstChild();
			WriteNode(nLevel);
			return;
		}
	}

	if(m_node->GetChildCount() == 0)
	{
		if(m_node->IsTag())
		{
			DumpTabs(nLevel);
			DumpString("<");
			DumpString(m_node->GetText());
			DumpAttributes(m_node);
			DumpString(" />\r\n");
		}
		m_node = m_node->GetParent();
		return;
	}

	if(m_node->GetChildCount() == 1)
	{
		if(!m_node->GetFirstChild()->IsTag())
		{
			DumpTabs(nLevel);

			DumpString("<");
			DumpString(m_node->GetText());
			DumpAttributes(m_node);
			DumpString(">");

			DumpString(EscapeText(m_node->GetInnerText()).c_str());

			DumpString("</");
			DumpString(m_node->GetText());
			DumpString(">\r\n");

			m_node = m_node->GetParent();

			return;
		}
	}

	DumpTabs(nLevel);
	DumpString("<");
	DumpString(m_node->GetText());
	DumpAttributes(m_node);
	DumpString(">\r\n");

	for(CNode::NodeIterator itNode(m_node->GetChildrenBegin()); 
		itNode != m_node->GetChildrenEnd(); itNode++)
	{
		m_node = (*itNode);
		WriteNode(nLevel + 1);
	}

	DumpTabs(nLevel);
	DumpString("</");
	DumpString(m_node->GetText());
	DumpString(">\r\n");

	m_node = m_node->GetParent();
}

void CWriter::DumpString(const char* sString)
{
	m_stream.Write(sString, (unsigned int)strlen(sString));
}

void CWriter::DumpTabs(unsigned int nCount)
{
	unsigned int i;
	for(i = 0; i < nCount; i++)
	{
		m_stream.Write8('\t');
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
		DumpString(EscapeText(Attribute.second).c_str());
		DumpString("\"");
	}
}
