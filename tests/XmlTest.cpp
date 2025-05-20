#include "XmlTest.h"
#include <string>
#include <cstring>
#include <cstdint>
#include "PtrStream.h"
#include "xml/Parser.h"
#include "xml/Utils.h"
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
	{
		static const int32 intValue = INT32_MAX;
		auto node = std::make_unique<Framework::Xml::CNode>("AttribTest", true);
		node->InsertAttribute(Framework::Xml::CreateAttributeIntValue("TestInt", intValue));
		TEST_VERIFY(Framework::Xml::GetAttributeIntValue(node.get(), "TestInt") == intValue);
	}
	{
		static const int64 int64Value = INT64_MAX;
		auto node = std::make_unique<Framework::Xml::CNode>("AttribTest", true);
		node->InsertAttribute(Framework::Xml::CreateAttributeInt64Value("TestInt64", int64Value));
		TEST_VERIFY(Framework::Xml::GetAttributeInt64Value(node.get(), "TestInt64") == int64Value);
	}
}
