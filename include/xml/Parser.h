#ifndef _XML_PARSER_H_
#define _XML_PARSER_H_

#include "Node.h"
#include "Stream.h"

namespace Framework
{
	
	namespace Xml
	{
		
		class CParser
		{
		public:
            static CNode*               ParseDocument(const char*);
			static CNode*				ParseDocument(CStream*);

		private:
										CParser(CStream*, CNode*);
										~CParser();

			bool						Parse();
			void						DumpText();
			bool						ProcessChar_Text(char);
			bool						ProcessChar_Tag(char);
			bool						ProcessChar_AttributeName(char);
			bool						ProcessChar_AttributeValue(char);
			bool						ProcessChar_Comment(char);

			enum STATE
			{
				STATE_TEXT,
				STATE_TAG,
				STATE_ATTRIBUTE_NAME,
				STATE_ATTRIBUTE_VALUE,
				STATE_COMMENT,
			};

			CStream*					m_pStream;
			CNode*						m_pNode;
			std::string					m_sText;
			std::string					m_sAttributeName;
			std::string					m_sAttributeValue;
			std::list<AttributeType>	m_Attributes;
			STATE						m_nState;
			bool						m_nIsTagEnd;
			bool						m_nTagSpace;
		};
	
	}

}

#endif
