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
			static CNode*				ParseDocument(CStream&);

		private:
										CParser(CStream&, CNode*);
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

			CStream&					m_stream;
			CNode*						m_node;
			std::string					m_text;
			std::string					m_attributeName;
			std::string					m_attributeValue;
			std::list<AttributeType>	m_attributes;
			STATE						m_state;
			bool						m_isTagEnd;
			bool						m_tagSpace;
		};
	
	}

}

#endif
