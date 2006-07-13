#ifndef _XML_UTILS_H_
#define _XML_UTILS_H_

#include "Node.h"

namespace Framework
{
	namespace Xml
	{
		bool			GetNodeStringValue(CNode*, const char*, const char**);
		bool			GetNodeIntValue(CNode*, const char*, int*);
		bool			GetNodeBoolValue(CNode*, const char*, bool*);

		bool			GetAttributeStringValue(CNode*, const char*, const char**);
		bool			GetAttributeIntValue(CNode*, const char*, int*);
		bool			GetAttributeBoolValue(CNode*, const char*, bool*);

		Xml::CNode*		CreateNodeStringValue(const char*, const char*);
		Xml::CNode*		CreateNodeIntValue(const char*, int);
		Xml::CNode*		CreateNodeBoolValue(const char*, bool);

		CStrPair*		CreateAttributeStringValue(const char*, const char*);
		CStrPair*		CreateAttributeIntValue(const char*, int);
		CStrPair*		CreateAttributeBoolValue(const char*, bool);
	}
}

#endif
