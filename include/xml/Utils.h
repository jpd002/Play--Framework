#pragma once

#include <string>
#include "Node.h"
#include "Types.h"

namespace Framework
{
	namespace Xml
	{
		bool			GetNodeStringValue(CNode*, const char*, const char**);
		bool			GetNodeIntValue(CNode*, const char*, int32*);
		bool			GetNodeBoolValue(CNode*, const char*, bool*);

		std::string		GetNodeStringValue(CNode*, const char*);
		int32			GetNodeIntValue(CNode*, const char*);

		bool			GetAttributeStringValue(CNode*, const char*, const char**);
		bool			GetAttributeStringValue(CNode*, const char*, std::string*);
		bool			GetAttributeIntValue(CNode*, const char*, int32*);
		bool			GetAttributeInt64Value(CNode*, const char*, int64*);
		bool			GetAttributeFloatValue(CNode*, const char*, float*);
		bool			GetAttributeBoolValue(CNode*, const char*, bool*);

		std::string		GetAttributeStringValue(CNode*, const char*);
		int32			GetAttributeIntValue(CNode*, const char*);
		int64			GetAttributeInt64Value(CNode*, const char*);
		float			GetAttributeFloatValue(CNode*, const char*);

		OwningNodePtr	CreateNodeStringValue(const char*, const char*);
		OwningNodePtr	CreateNodeIntValue(const char*, int);
		OwningNodePtr	CreateNodeBoolValue(const char*, bool);

		AttributeType	CreateAttributeStringValue(const char*, const char*);
		AttributeType	CreateAttributeIntValue(const char*, int32);
		AttributeType	CreateAttributeInt64Value(const char*, int64);
		AttributeType	CreateAttributeFloatValue(const char*, float);
		AttributeType	CreateAttributeBoolValue(const char*, bool);

		std::string		EscapeText(const std::string&);
		std::string		UnescapeText(const std::string&);
	}
}
