#ifndef _XML_UTILS_H_
#define _XML_UTILS_H_

#include <string>
#include "Node.h"

namespace Framework
{
	namespace Xml
	{
		bool			GetNodeStringValue(CNode*, const char*, const char**);
		bool			GetNodeIntValue(CNode*, const char*, int*);
		bool			GetNodeBoolValue(CNode*, const char*, bool*);

		std::string		GetNodeStringValue(CNode*, const char*);
		int				GetNodeIntValue(CNode*, const char*);

		bool			GetAttributeStringValue(CNode*, const char*, const char**);
		bool			GetAttributeStringValue(CNode*, const char*, std::string*);
		bool			GetAttributeIntValue(CNode*, const char*, int*);
		bool			GetAttributeFloatValue(CNode*, const char*, float*);
		bool			GetAttributeBoolValue(CNode*, const char*, bool*);

		std::string		GetAttributeStringValue(CNode*, const char*);
		int				GetAttributeIntValue(CNode*, const char*);
		float			GetAttributeFloatValue(CNode*, const char*);

		Xml::CNode*		CreateNodeStringValue(const char*, const char*);
		Xml::CNode*		CreateNodeIntValue(const char*, int);
		Xml::CNode*		CreateNodeBoolValue(const char*, bool);

		AttributeType	CreateAttributeStringValue(const char*, const char*);
		AttributeType	CreateAttributeIntValue(const char*, int);
		AttributeType	CreateAttributeBoolValue(const char*, bool);

		std::string		EscapeText(const std::string&);
		std::string		UnescapeText(const std::string&);
	}
}

#endif
