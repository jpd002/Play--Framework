#include "xml/Parser.h"
#include "Types.h"

using namespace Framework;
using namespace Framework::Xml;

CParser::CParser(CStream* pStream, CNode* pRoot)
{
	m_pStream = pStream;
	m_pNode = pRoot;
	m_sText = "";
	m_nState = STATE_TEXT;
	m_nIsTagEnd = false;
	m_nTagSpace = false;
}

CParser::~CParser()
{
	while(m_Attribute.Count() != 0)
	{
		delete m_Attribute.Pull();
	}
}

bool CParser::Parse()
{
	char nValue;
	bool nRet;
	m_pStream->Read(&nValue, 1);
	while(!m_pStream->IsEOF())
	{
		switch(m_nState)
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
		}
		if(nRet == false)
		{
			return false;
		}
		m_pStream->Read(&nValue, 1);
	}
	return true;
}

bool CParser::ProcessChar_Text(char nChar)
{
	if(nChar == '<')
	{
		//Tag is starting

		if(strlen(m_sText) != 0)
		{
			m_pNode->InsertNode(new CNode(m_sText, false));
			m_sText = "";
		}

		m_nState = STATE_TAG;
		m_nIsTagEnd = false;
		m_nTagSpace = false;
		return true;
	}
	m_sText += nChar;
	return true;
}

bool CParser::ProcessChar_Tag(char nChar)
{
	CNode* pChild;
	CStrPair* pAttribute;
	bool nHasSameName;

	if(nChar == '<')
	{
		//???
		return false;
	}
	if(nChar == '/')
	{
		//This is an end tag
		m_nIsTagEnd = true;
		return true;
	}
	if(nChar == ' ')
	{
		//Attributes follow
		m_nState = STATE_ATTRIBUTE_NAME;
		m_sAttributeName = "";
		return true;
	}
	if(nChar == '>')
	{
		if(((const char*)m_sText)[0] != '?')
		{
			//See if the tag name matches the current node's name
			nHasSameName = _stricmp(m_sText, m_pNode->GetText()) == 0;

			if(m_nIsTagEnd && nHasSameName)
			{
				//Walk up the tree
				m_pNode = m_pNode->GetParent();
			}
			else
			{
				//Create a new node
				pChild = new CNode(m_sText, true);
				m_pNode->InsertNode(pChild);

				//Copy attributes
				while(m_Attribute.Count() != 0)
				{
					pAttribute = m_Attribute.Pull();
					pChild->InsertAttribute(pAttribute);
				}

				//Go down if it's not an singleton
				if(!m_nIsTagEnd)
				{
					m_pNode = pChild;
				}
			}
		}

		m_sText = "";
		m_nState = STATE_TEXT;
		return true;
	}
	m_sText += nChar;
	return true;
}

bool CParser::ProcessChar_AttributeName(char nChar)
{
	if(nChar == '=')
	{
		return true;
	}
	if(nChar == ' ')
	{
		if(strlen(m_sAttributeName) == 0) return true;
		return false;
	}
	if(nChar == '>' || nChar == '/')
	{
		m_nState = STATE_TAG;
		return ProcessChar_Tag(nChar);
	}
	if(nChar == '"')
	{
		m_nState = STATE_ATTRIBUTE_VALUE;
		m_sAttributeValue = "";
		return true;
	}
	m_sAttributeName += nChar;
	return true;
}

bool CParser::ProcessChar_AttributeValue(char nChar)
{
	if(nChar == '"')
	{
		m_Attribute.Insert(new CStrPair(m_sAttributeName, m_sAttributeValue));

		m_nState = STATE_ATTRIBUTE_NAME;
		m_sAttributeName = "";
		return true;
	}
	m_sAttributeValue += nChar;
	return true;
}

CNode* CParser::ParseDocument(CStream* pStream)
{
	CParser* pParser;
	CNode* pRoot;
	bool nRet;

	pRoot = new CNode();

	pParser = new CParser(pStream, pRoot);
	nRet = pParser->Parse();

	delete pParser;

	if(!nRet)
	{
		delete pRoot;
		return NULL;
	}

	return pRoot;
}
