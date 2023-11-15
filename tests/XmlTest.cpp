#include "XmlTest.h"
#include <string>
#include "PtrStream.h"
#include "xml/Parser.h"
#include "TestDefs.h"

static const char* g_escapeCharXml = "<root>Bacon &amp; Eggs</root>";

void XmlTest_Execute()
{
	{
		Framework::CPtrStream input(g_escapeCharXml, strlen(g_escapeCharXml));
		auto node = Framework::Xml::CParser::ParseDocument(input);
		auto rootNode = node->Select("root");
		TEST_VERIFY(!strcmp(rootNode->GetInnerText(), "Bacon & Eggs"));
	}
}
