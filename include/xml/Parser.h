#ifndef _XML_PARSER_H_
#define _XML_PARSER_H_

#include "Node.h"
#include "Stream.h"
#include "Str.h"
#include "StrPair.h"

namespace Framework
{
	
	namespace Xml
	{
		
		class CParser
		{
		public:
			static CNode*	ParseDocument(CStream*);

		private:
							CParser(CStream*, CNode*);
							~CParser();

			bool			Parse();
			void			DumpText();
			bool			ProcessChar_Text(char);
			bool			ProcessChar_Tag(char);
			bool			ProcessChar_AttributeName(char);
			bool			ProcessChar_AttributeValue(char);

			enum STATE
			{
				STATE_TEXT,
				STATE_TAG,
				STATE_ATTRIBUTE_NAME,
				STATE_ATTRIBUTE_VALUE,
			};

			CStream*		m_pStream;
			CNode*			m_pNode;
			CStrA			m_sText;
			CStrA			m_sAttributeName;
			CStrA			m_sAttributeValue;
			CList<CStrPair>	m_Attribute;
			STATE			m_nState;
			bool			m_nIsTagEnd;
			bool			m_nTagSpace;
		};
	
	}

}

#endif
