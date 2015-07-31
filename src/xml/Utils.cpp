#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include "xml/Utils.h"

using namespace Framework;

bool Xml::GetNodeStringValue(Xml::CNode* pNode, const char* sPath, const char** pValue)
{
	pNode = pNode->Select(sPath);
	if(pNode == NULL)
	{
		return false;
	}
	
	const char* sText = pNode->GetInnerText();
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

bool Xml::GetNodeIntValue(Xml::CNode* pNode, const char* sPath, int* pValue)
{
	const char* sText(nullptr);
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
	const char* sText(nullptr);
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

std::string Xml::GetNodeStringValue(Xml::CNode* pNode, const char* sPath)
{
	const char* sValue(nullptr);
	if(!GetNodeStringValue(pNode, sPath, &sValue))
	{
		throw std::exception();
	}

	return std::string(sValue);
}

int Xml::GetNodeIntValue(Xml::CNode* node, const char* path)
{
	int value = 0;
	if(!GetNodeIntValue(node, path, &value))
	{
		throw std::exception();
	}
	return value;
}

bool Xml::GetAttributeStringValue(Xml::CNode* pNode, const char* sName, const char** pValue)
{
	const char* sText = pNode->GetAttribute(sName);
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

bool Xml::GetAttributeStringValue(Xml::CNode* node, const char* name, std::string* value)
{
	const char* text = node->GetAttribute(name);
	if(text == nullptr)
	{
		return false;
	}

	if(value == nullptr)
	{
		return false;
	}

	(*value) = text;
	return true;
}

bool Xml::GetAttributeIntValue(Xml::CNode* pNode, const char* sName, int* pValue)
{
	const char* sText(nullptr);
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

bool Xml::GetAttributeFloatValue(Xml::CNode* node, const char* name, float* value)
{
	const char* text(nullptr);
	if(!GetAttributeStringValue(node, name, &text))
	{
		return false;
	}

	if(value == nullptr)
	{
		return false;
	}

	(*value) = static_cast<float>(atof(text));
	return true;
}

bool Xml::GetAttributeBoolValue(Xml::CNode* pNode, const char* sName, bool* pValue)
{
	const char* sText(nullptr);
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

std::string Xml::GetAttributeStringValue(Xml::CNode* pNode, const char* sName)
{
	const char* sValue(nullptr);
	if(!GetAttributeStringValue(pNode, sName, &sValue))
	{
		throw std::exception();
	}
	return sValue;
}

int Xml::GetAttributeIntValue(Xml::CNode* pNode, const char* sName)
{
	int nValue = 0;
	if(!GetAttributeIntValue(pNode, sName, &nValue))
	{
		throw std::exception();
	}
	return nValue;
}

float Xml::GetAttributeFloatValue(Xml::CNode* node, const char* name)
{
	float value = 0;
	if(!GetAttributeFloatValue(node, name, &value))
	{
		throw std::exception();
	}
	return value;
}

Xml::CNode* Xml::CreateNodeStringValue(const char* sName, const char* sValue)
{
	Xml::CNode* pNode = new Xml::CNode(sName, true);
	pNode->InsertNode(new Xml::CNode(sValue, false));
	return pNode;
}

Xml::CNode* Xml::CreateNodeIntValue(const char* sName, int nValue)
{
	char sValue[256];

	Xml::CNode* pNode = new Xml::CNode(sName, true);
	sprintf(sValue, "%i", nValue);
	pNode->InsertNode(new Xml::CNode(sValue, false));

	return pNode;
}

Xml::CNode* Xml::CreateNodeBoolValue(const char* sName, bool nValue)
{
	Xml::CNode* pNode = new Xml::CNode(sName, true);
	const char* sValue = nValue ? "true" : "false";
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

std::string Xml::EscapeText(const std::string& text)
{
	std::string result;
	for(auto charIterator(text.begin());
		charIterator != text.end(); charIterator++)
	{
		switch(*charIterator)
		{
		case '&':
			result += "&amp;";
			break;
		case '<':
			result += "&lt;";
			break;
		case '>':
			result += "&gt;";
			break;
		case '\'':
			result += "&apos;";
			break;
		case '\"':
			result += "&quot;";
			break;
		default:
			result += *charIterator;
			break;
		}
	}
	return result;
}

std::string Xml::UnescapeText(const std::string& text)
{
	std::string result;
	for(auto charIterator(text.begin());
		charIterator != text.end(); charIterator++)
	{
		if(*charIterator == '&')
		{
			std::string::size_type currentPos = charIterator - text.begin();
			std::string::size_type endPos = text.find(';', currentPos);
			if(endPos == -1)
			{
				return "";
			}
			std::string escapeName(text.substr(currentPos + 1, endPos - currentPos - 1));
					if(!strcmp(escapeName.c_str(), "amp"))	result += '&';
			else	if(!strcmp(escapeName.c_str(), "lt"))	result += '<';
			else	if(!strcmp(escapeName.c_str(), "gt"))	result += '>';
			else	if(!strcmp(escapeName.c_str(), "apos"))	result += '\'';
			else	if(!strcmp(escapeName.c_str(), "quot"))	result += '\"';
			else
			{
				return "";
			}
			charIterator = text.begin() + endPos;
		}
		else
		{
			result += *charIterator;
		}
	}
	return result;
}
