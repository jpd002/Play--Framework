#include "xml/Parser.h"
#include "xml/Utils.h"
#include "Types.h"
#include "stricmp.h"
#include "IosIStream.h"
#include <sstream>

using namespace Framework;
using namespace Framework::Xml;

CParser::CParser(CStream& stream, CNode* root)
: m_stream(stream)
, m_node(root)
, m_state(STATE_TEXT)
, m_isTagEnd(false)
, m_tagSpace(false)
{

}

CParser::~CParser()
{

}

bool CParser::Parse()
{
	char nValue = 0;
	m_stream.Read(&nValue, 1);

	while(!m_stream.IsEOF())
	{
		bool nRet = false;
		switch(m_state)
		{
		case STATE_TEXT:
			nRet = ProcessChar_Text(nValue);
			break;
		case STATE_TAG:
			nRet = ProcessChar_Tag(nValue);
			break;
		case STATE_ATTRIBUTE_NAME:
			nRet = ProcessChar_AttributeName(nValue);
			break;
		case STATE_ATTRIBUTE_VALUE:
			nRet = ProcessChar_AttributeValue(nValue);
			break;
		case STATE_COMMENT:
			nRet = ProcessChar_Comment(nValue);
			break;
		}
		if(nRet == false)
		{
			return false;
		}
		m_stream.Read(&nValue, 1);
	}
	return true;
}

bool CParser::ProcessChar_Text(char nChar)
{
	if(nChar == '<')
	{
		//Tag is starting

		if(m_text.size() != 0)
		{
			m_node->InsertNode(new CNode(UnescapeText(m_text).c_str(), false));
			m_text = "";
		}

		m_state = STATE_TAG;
		m_isTagEnd = false;
		m_tagSpace = false;
		return true;
	}
	m_text += nChar;
	return true;
}

bool CParser::ProcessChar_Tag(char nChar)
{
	if((nChar == '!') && (m_text.size() == 0))
	{
		m_state = STATE_COMMENT;
		return true;
	}
	if(nChar == '<')
	{
		//???
		return false;
	}
	if(nChar == '/')
	{
		//This is an end tag
		m_isTagEnd = true;
		return true;
	}
	if(nChar == ' ' || nChar == '\t' || nChar == '\r' || nChar == '\n')
	{
		//Attributes follow
		m_state = STATE_ATTRIBUTE_NAME;
		m_attributeName = "";
		return true;
	}
	if(nChar == '>')
	{
		if(m_text[0] != '?')
		{
			//See if the tag name matches the current node's name
			bool nHasSameName = stricmp(m_text.c_str(), m_node->GetText()) == 0;

			if(m_isTagEnd && nHasSameName)
			{
				//Walk up the tree
				m_node = m_node->GetParent();
			}
			else
			{
				//Create a new node
				CNode* pChild = new CNode(m_text.c_str(), true);
				m_node->InsertNode(pChild);

				//Copy attributes
				while(m_attributes.size() != 0)
				{
					pChild->InsertAttribute(*m_attributes.rbegin());
					m_attributes.pop_back();
				}

				//Go down if it's not an singleton
				if(!m_isTagEnd)
				{
					m_node = pChild;
				}
			}
		}

		m_text = "";
		m_state = STATE_TEXT;
		return true;
	}

	m_text += nChar;
	return true;
}

bool CParser::ProcessChar_AttributeName(char nChar)
{
	if(nChar == '=')
	{
		return true;
	}
	if(nChar == ' ' || nChar == '\t' || nChar == '\r' || nChar == '\n')
	{
		if(m_attributeName.size() == 0) return true;
		return false;
	}
	if(nChar == '>' || nChar == '/')
	{
		m_state = STATE_TAG;
		return ProcessChar_Tag(nChar);
	}
	if(nChar == '"')
	{
		m_state = STATE_ATTRIBUTE_VALUE;
		m_attributeValue = "";
		return true;
	}
	m_attributeName += nChar;
	return true;
}

bool CParser::ProcessChar_AttributeValue(char nChar)
{
	if(nChar == '"')
	{
		m_attributes.push_back(AttributeType(m_attributeName, UnescapeText(m_attributeValue)));

		m_state = STATE_ATTRIBUTE_NAME;
		m_attributeName = "";
		return true;
	}
	m_attributeValue += nChar;
	return true;
}

bool CParser::ProcessChar_Comment(char nChar)
{
	if(nChar == '>')
	{
		if(!std::string(m_text.end() - 2, m_text.end()).compare("--"))
		{
			//Comment end
			m_text = "";
			m_state = STATE_TEXT;
			return true;
		}
	}

	m_text += nChar;
	return true;
}

CNode* CParser::ParseDocument(CStream& stream)
{
	CNode* root = new CNode();

	CParser Parser(stream, root);
	bool nRet = Parser.Parse();

	if(!nRet)
	{
		delete root;
		return NULL;
	}

	return root;
}
