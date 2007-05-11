#include <stdio.h>
#include <stdexcept>
#include "xml/Utils.h"

using namespace Framework;
using namespace std;

bool Xml::GetNodeStringValue(Xml::CNode* pNode, const char* sPath, const char** pValue)
{
	const char* sText;
	
	pNode = pNode->Select(sPath);
	if(pNode == NULL)
	{
		return false;
	}
	
	sText = pNode->GetInnerText();
	if(sText == NULL)
	{
		return false;
	}

	if(pValue == NULL)
	{
		return false;
	}

	(*pValue) = sText;
	return true;
}

string Xml::GetNodeStringValue(Xml::CNode* pNode, const char* sPath)
{
    const char* sValue;
    if(!GetNodeStringValue(pNode, sPath, &sValue))
    {
        throw exception();
    }

    return string(sValue);
}

bool Xml::GetNodeIntValue(Xml::CNode* pNode, const char* sPath, int* pValue)
{
	const char* sText;

	if(!GetNodeStringValue(pNode, sPath, &sText))
	{
		return false;
	}

	if(pValue == NULL)
	{
		return false;
	}

	(*pValue) = atoi(sText);
	return true;
}

bool Xml::GetNodeBoolValue(Xml::CNode* pNode, const char* sPath, bool* pValue)
{
	const char* sText;

	if(!GetNodeStringValue(pNode, sPath, &sText))
	{
		return false;
	}

	if(pValue == NULL)
	{
		return false;
	}

	if(!strcmp(sText, "true"))
	{
		(*pValue) = true;
	}
	if(!strcmp(sText, "false"))
	{
		(*pValue) = false;
	}

	return true;
}

bool Xml::GetAttributeStringValue(Xml::CNode* pNode, const char* sName, const char** pValue)
{
	const char* sText;
	
	sText = pNode->GetAttribute(sName);
	if(sText == NULL)
	{
		return false;
	}

	if(pValue == NULL)
	{
		return false;
	}

	(*pValue) = sText;
	return true;
}

bool Xml::GetAttributeIntValue(Xml::CNode* pNode, const char* sName, int* pValue)
{
	const char* sText;

	if(!GetAttributeStringValue(pNode, sName, &sText))
	{
		return false;
	}

	if(pValue == NULL)
	{
		return false;
	}

	(*pValue) = atoi(sText);
	return true;
}

int Xml::GetAttributeIntValue(Xml::CNode* pNode, const char* sName)
{
    int nValue;
    if(!GetAttributeIntValue(pNode, sName, &nValue))
    {
        throw exception();
    }
    return nValue;
}

bool Xml::GetAttributeBoolValue(Xml::CNode* pNode, const char* sName, bool* pValue)
{
	const char* sText;

	if(!GetAttributeStringValue(pNode, sName, &sText))
	{
		return false;
	}

	if(pValue == NULL)
	{
		return false;
	}

	if(!strcmp(sText, "true"))
	{
		(*pValue) = true;
	}
	if(!strcmp(sText, "false"))
	{
		(*pValue) = false;
	}

	return true;
}

Xml::CNode* Xml::CreateNodeStringValue(const char* sName, const char* sValue)
{
	Xml::CNode* pNode;

	pNode = new Xml::CNode(sName, true);
	pNode->InsertNode(new Xml::CNode(sValue, false));

	return pNode;
}

Xml::CNode* Xml::CreateNodeIntValue(const char* sName, int nValue)
{
	char sValue[256];
	Xml::CNode* pNode;

	pNode = new Xml::CNode(sName, true);
	sprintf(sValue, "%i", nValue);
	pNode->InsertNode(new Xml::CNode(sValue, false));

	return pNode;
}

Xml::CNode* Xml::CreateNodeBoolValue(const char* sName, bool nValue)
{
	const char* sValue;
	Xml::CNode* pNode;

	pNode = new Xml::CNode(sName, true);
	sValue = nValue ? "true" : "false";
	pNode->InsertNode(new Xml::CNode(sValue, false));

	return pNode;
}

Xml::AttributeType Xml::CreateAttributeStringValue(const char* sName, const char* sValue)
{
	return AttributeType(sName, sValue);
}

Xml::AttributeType Xml::CreateAttributeIntValue(const char* sName, int nValue)
{
	char sValue[256];

	sprintf(sValue, "%i", nValue);

	return AttributeType(sName, sValue);
}

Xml::AttributeType Xml::CreateAttributeBoolValue(const char* sName, bool nValue)
{
	return AttributeType(sName, nValue ? "true" : "false");
}
