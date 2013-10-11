#include <string.h>
#include "xml/Writer.h"
#include "xml/Utils.h"

using namespace Framework;
using namespace Framework::Xml;

CWriter::CWriter(CStream& stream)
: m_stream(stream)
{

}

CWriter::~CWriter()
{

}

void CWriter::WriteDocument(CStream& stream, CNode* node)
{
	CWriter writer(stream);
	writer.WriteNode(node, 0);
}

void CWriter::WriteNode(CNode* currentNode, unsigned int level)
{
	if(strcmp(currentNode->GetText(), "") == 0)
	{
		if(currentNode->GetChildCount() == 1)
		{
			WriteNode(currentNode->GetFirstChild(), level);
			return;
		}
	}

	if(currentNode->GetChildCount() == 0)
	{
		if(currentNode->IsTag())
		{
			DumpTabs(level);
			DumpString("<");
			DumpString(currentNode->GetText());
			DumpAttributes(currentNode);
			DumpString(" />\r\n");
		}
		return;
	}

	if(currentNode->GetChildCount() == 1)
	{
		if(!currentNode->GetFirstChild()->IsTag())
		{
			DumpTabs(level);

			DumpString("<");
			DumpString(currentNode->GetText());
			DumpAttributes(currentNode);
			DumpString(">");

			DumpString(EscapeText(currentNode->GetInnerText()).c_str());

			DumpString("</");
			DumpString(currentNode->GetText());
			DumpString(">\r\n");

			return;
		}
	}

	DumpTabs(level);
	DumpString("<");
	DumpString(currentNode->GetText());
	DumpAttributes(currentNode);
	DumpString(">\r\n");

	for(const auto& node : currentNode->GetChildren())
	{
		WriteNode(node, level + 1);
	}

	DumpTabs(level);
	DumpString("</");
	DumpString(currentNode->GetText());
	DumpString(">\r\n");
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

void CWriter::DumpAttributes(CNode* node)
{
	for(const auto& attribute : node->GetAttributes())
	{
		DumpString(" ");
		DumpString(attribute.first.c_str());
		DumpString("=\"");
		DumpString(EscapeText(attribute.second).c_str());
		DumpString("\"");
	}
}
