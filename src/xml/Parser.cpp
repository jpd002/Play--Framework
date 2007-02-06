#include "xml/Parser.h"
#include "Types.h"

using namespace Framework;
using namespace Framework::Xml;
using namespace std;

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
		case STATE_COMMENT:
			nRet = ProcessChar_Comment(nValue);
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

		if(m_sText.size() != 0)
		{
			m_pNode->InsertNode(new CNode(m_sText.c_str(), false));
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
	bool nHasSameName;

	if((nChar == '!') && (m_sText.size() == 0))
	{
		m_nState = STATE_COMMENT;
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
		if(m_sText[0] != '?')
		{
			//See if the tag name matches the current node's name
			nHasSameName = strcasecmp(m_sText.c_str(), m_pNode->GetText()) == 0;

			if(m_nIsTagEnd && nHasSameName)
			{
				//Walk up the tree
				m_pNode = m_pNode->GetParent();
			}
			else
			{
				//Create a new node
				pChild = new CNode(m_sText.c_str(), true);
				m_pNode->InsertNode(pChild);

				//Copy attributes
				while(m_Attributes.size() != 0)
				{
					pChild->InsertAttribute(*m_Attributes.rbegin());
					m_Attributes.pop_back();
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
		if(m_sAttributeName.size() == 0) return true;
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
		m_Attributes.push_back(AttributeType(m_sAttributeName, m_sAttributeValue));

		m_nState = STATE_ATTRIBUTE_NAME;
		m_sAttributeName = "";
		return true;
	}
	m_sAttributeValue += nChar;
	return true;
}

bool CParser::ProcessChar_Comment(char nChar)
{
	if(nChar == '>')
	{
		if(!string(m_sText.end() - 2, m_sText.end()).compare("--"))
		{
			//Comment end
			m_sText = "";
			m_nState = STATE_TEXT;
			return true;
		}
	}

	m_sText += nChar;
	return true;
}

CNode* CParser::ParseDocument(CStream* pStream)
{
	CNode* pRoot;
	bool nRet;

	pRoot = new CNode();

	CParser Parser(pStream, pRoot);
	nRet = Parser.Parse();

	if(!nRet)
	{
		delete pRoot;
		return NULL;
	}

	return pRoot;
}
