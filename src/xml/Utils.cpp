#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include "xml/Utils.h"
#include "string_format.h"

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

bool Xml::GetNodeIntValue(Xml::CNode* pNode, const char* sPath, int32* pValue)
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
	int32 value = 0;
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

bool Xml::GetAttributeIntValue(Xml::CNode* pNode, const char* sName, int32* pValue)
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

bool Xml::GetAttributeInt64Value(Xml::CNode* node, const char* name, int64* value)
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

	(*value) = atoll(text);
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

int32 Xml::GetAttributeIntValue(Xml::CNode* pNode, const char* sName)
{
	int32 nValue = 0;
	if(!GetAttributeIntValue(pNode, sName, &nValue))
	{
		throw std::exception();
	}
	return nValue;
}

int64 Xml::GetAttributeInt64Value(Xml::CNode* node, const char* name)
{
	int64 nValue = 0;
	if(!GetAttributeInt64Value(node, name, &nValue))
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

Xml::OwningNodePtr Xml::CreateNodeStringValue(const char* sName, const char* sValue)
{
	auto node = std::make_unique<Xml::CNode>(sName, true);
	node->InsertNode(std::make_unique<Xml::CNode>(sValue, false));
	return node;
}

Xml::OwningNodePtr Xml::CreateNodeIntValue(const char* sName, int32 nValue)
{
	auto node = std::make_unique<Xml::CNode>(sName, true);
	auto sValue = string_format("%d", nValue);
	node->InsertNode(std::make_unique<Xml::CNode>(std::move(sValue), false));

	return node;
}

Xml::OwningNodePtr Xml::CreateNodeBoolValue(const char* sName, bool nValue)
{
	auto node = std::make_unique<Xml::CNode>(sName, true);
	const char* sValue = nValue ? "true" : "false";
	node->InsertNode(std::make_unique<Xml::CNode>(sValue, false));

	return node;
}

Xml::AttributeType Xml::CreateAttributeStringValue(const char* sName, const char* sValue)
{
	return AttributeType(sName, sValue);
}

Xml::AttributeType Xml::CreateAttributeIntValue(const char* sName, int32 nValue)
{
	auto sValue = string_format("%d", nValue);
	return AttributeType(sName, std::move(sValue));
}

Xml::AttributeType Xml::CreateAttributeInt64Value(const char* sName, int64 nValue)
{
	auto sValue = string_format("%lld", nValue);
	return AttributeType(sName, std::move(sValue));
}

Xml::AttributeType Xml::CreateAttributeFloatValue(const char* sName, float nValue)
{
	auto sValue = string_format("%f", nValue);
	return AttributeType(sName, std::move(sValue));
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
		case '\n':
			result += "&#x0A;";
			break;
		case '\r':
			result += "&#x0D;";
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
	auto ampPos = text.find('&');
	if(ampPos == std::string::npos)
	{
		return text;
	}
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
			else	if(escapeName.find("#x") == 0)
			{
				//TODO: Handle this better (ie.: handle encoding and such)
				char value = static_cast<char>(strtol(escapeName.c_str() + 2, nullptr, 16));
				if(value != 0)
				{
					result += value;
				}
			}
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
