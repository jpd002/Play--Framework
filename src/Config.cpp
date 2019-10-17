#include <string.h>
#include <stdlib.h>
#include <cassert>
#include "Config.h"
#include "StdStream.h"
#include "xml/Writer.h"
#include "xml/Parser.h"
#include "xml/Utils.h"
#include "xml/FilteringNodeIterator.h"
#include "PathUtils.h"
#include "StdStreamUtils.h"

#define PREFERENCE_ATTRIBUTE_NAME_NAME "Name"
#define PREFERENCE_ATTRIBUTE_NAME_TYPE "Type"
#define PREFERENCE_ATTRIBUTE_NAME_VALUE "Value"

#define PREFERENCE_TYPE_NAME_INTEGER "integer"
#define PREFERENCE_TYPE_NAME_BOOLEAN "boolean"
#define PREFERENCE_TYPE_NAME_STRING "string"
#define PREFERENCE_TYPE_NAME_PATH "path"

using namespace Framework;

CConfig::CConfig(const PathType& path, bool readonly)
: m_path(path)
, m_readonly(readonly)
{
	Load();
}

CConfig::~CConfig()
{
	if(!m_readonly)
	{
		Save();
	}
}

std::string CConfig::MakePreferenceName(const std::string& level0, const std::string& level1, const std::string& level2, const std::string& level3)
{
	std::string result = level0;
	if(level1.length())
	{
		result += "." + level1;
		if(level2.length())
		{
			result += "." + level2;
			if(level3.length())
			{
				result += "." + level3;
			}
		}
	}
	return result;
}

namespace Framework {

template <>
std::shared_ptr<CConfig::CPreference> CConfig::CastPreference<CConfig::CPreference>(const PreferencePtr& preference)
{
	return preference;
}

}

template <typename Type> std::shared_ptr<Type> CConfig::FindPreference(const char* name)
{
	PreferencePtr basePref;

	{
		std::unique_lock<std::mutex> mutexLock(m_mutex);
		auto preferenceIterator(m_preferences.find(name));
		if(preferenceIterator != m_preferences.end())
		{
			basePref = preferenceIterator->second;
		}
	}

	if(!basePref) return std::shared_ptr<Type>();

	auto pref = CastPreference<Type>(basePref);
	return pref;
}

void CConfig::RegisterPreferenceInteger(const char* name, int value)
{
	if(FindPreference<CPreference>(name))
	{
		return;
	}

	auto preference = std::make_shared<CPreferenceInteger>(name, value);
	InsertPreference(preference);
}

void CConfig::RegisterPreferenceBoolean(const char* name, bool value)
{
	if(FindPreference<CPreference>(name))
	{
		return;
	}

	auto preference = std::make_shared<CPreferenceBoolean>(name, value);
	InsertPreference(preference);
}

void CConfig::RegisterPreferenceString(const char* name, const char* value)
{
	if(FindPreference<CPreference>(name))
	{
		return;
	}

	auto preference = std::make_shared<CPreferenceString>(name, value);
	InsertPreference(preference);
}

void CConfig::RegisterPreferencePath(const char* name, const PathType& value)
{
	if(FindPreference<CPreference>(name))
	{
		return;
	}

	auto preference = std::make_shared<CPreferencePath>(name, value);
	InsertPreference(preference);
}

int CConfig::GetPreferenceInteger(const char* name)
{
	auto preference = FindPreference<CPreferenceInteger>(name);
	if(!preference) return 0;
	return preference->GetValue();
}

bool CConfig::GetPreferenceBoolean(const char* name)
{
	auto preference = FindPreference<CPreferenceBoolean>(name);
	if(!preference) return false;
	return preference->GetValue();
}

const char* CConfig::GetPreferenceString(const char* name)
{
	auto preference = FindPreference<CPreferenceString>(name);
	if(!preference) return "";
	return preference->GetValue();
}

CConfig::PathType CConfig::GetPreferencePath(const char* name)
{
	auto preference = FindPreference<CPreferencePath>(name);
	if(!preference) return PathType();
	return preference->GetValue();
}

bool CConfig::SetPreferenceInteger(const char* name, int value)
{
	if(m_readonly) throw std::runtime_error("Setting preference on read-only config is illegal.");
	auto preference = FindPreference<CPreferenceInteger>(name);
	if(!preference) return false;
	preference->SetValue(value);
	return true;
}

bool CConfig::SetPreferenceBoolean(const char* name, bool value)
{
	if(m_readonly) throw std::runtime_error("Setting preference on read-only config is illegal.");
	auto preference = FindPreference<CPreferenceBoolean>(name);
	if(!preference) return false;
	preference->SetValue(value);
	return true;
}

bool CConfig::SetPreferenceString(const char* name, const char* value)
{
	if(m_readonly) throw std::runtime_error("Setting preference on read-only config is illegal.");
	auto preference = FindPreference<CPreferenceString>(name);
	if(!preference) return false;
	preference->SetValue(value);
	return true;
}

bool CConfig::SetPreferencePath(const char* name, const PathType& value)
{
	if(m_readonly) throw std::runtime_error("Setting preference on read-only config is illegal.");
	auto preference = FindPreference<CPreferencePath>(name);
	if(!preference) return false;
	preference->SetValue(value);
	return true;
}

CConfig::PathType CConfig::GetConfigPath() const
{
	return m_path;
}

void CConfig::Load()
{
	std::unique_ptr<Xml::CNode> document;

	try
	{
		Framework::CStdStream configFile(CreateInputStdStream(m_path.native()));
		document = std::unique_ptr<Xml::CNode>(Xml::CParser::ParseDocument(configFile));
	}
	catch(...)
	{
		return;
	}

	//ParseDocument can return null if parsing failed
	if(!document)
	{
		return;
	}

	auto configNode = document->Select("Config");
	if(!configNode)
	{
		return;
	}

	for(Xml::CFilteringNodeIterator itNode(configNode, "Preference"); !itNode.IsEnd(); itNode++)
	{
		auto prefNode = (*itNode);

		auto type = prefNode->GetAttribute(PREFERENCE_ATTRIBUTE_NAME_TYPE);
		auto name = prefNode->GetAttribute(PREFERENCE_ATTRIBUTE_NAME_NAME);

		if(!type) continue;
		if(!name) continue;

		if(!strcmp(type, PREFERENCE_TYPE_NAME_INTEGER))
		{
			int value = 0;
			if(Xml::GetAttributeIntValue(prefNode, PREFERENCE_ATTRIBUTE_NAME_VALUE, &value))
			{
				RegisterPreferenceInteger(name, value);
			}
		}
		else if(!strcmp(type, PREFERENCE_TYPE_NAME_BOOLEAN))
		{
			bool value = false;
			if(Xml::GetAttributeBoolValue(prefNode, PREFERENCE_ATTRIBUTE_NAME_VALUE, &value))
			{
				RegisterPreferenceBoolean(name, value);
			}
		}
		else if(!strcmp(type, PREFERENCE_TYPE_NAME_STRING))
		{
			const char* value = nullptr;
			if(Xml::GetAttributeStringValue(prefNode, PREFERENCE_ATTRIBUTE_NAME_VALUE, &value))
			{
				RegisterPreferenceString(name, value);
			}
		}
		else if(!strcmp(type, PREFERENCE_TYPE_NAME_PATH))
		{
			const char* valueString = nullptr;
			if(Xml::GetAttributeStringValue(prefNode, PREFERENCE_ATTRIBUTE_NAME_VALUE, &valueString))
			{
				auto value = PathUtils::GetPathFromNativeString(valueString);
				RegisterPreferencePath(name, value);
			}
		}
		else
		{
			//Unknown preference type
			assert(false);
		}
	}
}

void CConfig::Save()
{
	if(m_readonly)
	{
		throw std::runtime_error("Config marked as read-only but save has been requested.");
	}

	try
	{
		Framework::CStdStream stream(CreateOutputStdStream(m_path.native()));

		auto configNode = new Xml::CNode("Config", true);

		for(const auto& preferencePair : m_preferences)
		{
			const auto& preference = preferencePair.second;

			auto preferenceNode = new Xml::CNode("Preference", true);
			preference->Serialize(preferenceNode);
			configNode->InsertNode(preferenceNode);
		}

		{
			auto document = std::unique_ptr<Xml::CNode>(new Xml::CNode);
			document->InsertNode(configNode);
			Xml::CWriter::WriteDocument(stream, document.get());
		}
	}
	catch(...)
	{
		return;
	}
}

void CConfig::InsertPreference(const PreferencePtr& preference)
{
	std::unique_lock<std::mutex> mutexLock(m_mutex);
	m_preferences[preference->GetName()] = preference;
}

/////////////////////////////////////////////////////////
//CPreference implementation
/////////////////////////////////////////////////////////

CConfig::CPreference::CPreference(const char* name, PREFERENCE_TYPE nType)
: m_name(name)
, m_type(nType)
{
	
}

const char* CConfig::CPreference::GetName() const
{
	return m_name.c_str();
}

CConfig::PREFERENCE_TYPE CConfig::CPreference::GetType() const
{
	return m_type;
}

const char* CConfig::CPreference::GetTypeString() const
{
	switch(m_type)
	{
	case TYPE_INTEGER:
		return PREFERENCE_TYPE_NAME_INTEGER;
	case TYPE_BOOLEAN:
		return PREFERENCE_TYPE_NAME_BOOLEAN;
	case TYPE_STRING:
		return PREFERENCE_TYPE_NAME_STRING;
	case TYPE_PATH:
		return PREFERENCE_TYPE_NAME_PATH;
	default:
		assert(false);
		return "";
	}
}

void CConfig::CPreference::Serialize(Xml::CNode* pNode) const
{
	pNode->InsertAttribute(Xml::CreateAttributeStringValue(PREFERENCE_ATTRIBUTE_NAME_NAME, m_name.c_str()));
	pNode->InsertAttribute(Xml::CreateAttributeStringValue(PREFERENCE_ATTRIBUTE_NAME_TYPE, GetTypeString()));
}

/////////////////////////////////////////////////////////
//CPreferenceInteger implementation
/////////////////////////////////////////////////////////

CConfig::CPreferenceInteger::CPreferenceInteger(const char* name, int value)
: CPreference(name, TYPE_INTEGER)
, m_value(value)
{
	
}

int CConfig::CPreferenceInteger::GetValue() const
{
	return m_value;
}

void CConfig::CPreferenceInteger::SetValue(int value)
{
	m_value = value;
}

void CConfig::CPreferenceInteger::Serialize(Xml::CNode* pNode) const
{
	CPreference::Serialize(pNode);

	pNode->InsertAttribute(Xml::CreateAttributeIntValue(PREFERENCE_ATTRIBUTE_NAME_VALUE, m_value));
}

/////////////////////////////////////////////////////////
//CPreferenceBoolean implementation
/////////////////////////////////////////////////////////

CConfig::CPreferenceBoolean::CPreferenceBoolean(const char* name, bool value)
: CPreference(name, TYPE_BOOLEAN)
, m_value(value)
{
	
}

bool CConfig::CPreferenceBoolean::GetValue() const
{
	return m_value;
}

void CConfig::CPreferenceBoolean::SetValue(bool value)
{
	m_value = value;
}

void CConfig::CPreferenceBoolean::Serialize(Xml::CNode* pNode) const
{
	CPreference::Serialize(pNode);

	pNode->InsertAttribute(Xml::CreateAttributeBoolValue(PREFERENCE_ATTRIBUTE_NAME_VALUE, m_value));
}

/////////////////////////////////////////////////////////
//CPreferenceString implementation
/////////////////////////////////////////////////////////

CConfig::CPreferenceString::CPreferenceString(const char* name, const char* value)
: CPreference(name, TYPE_STRING)
, m_value(value)
{
	
}

const char* CConfig::CPreferenceString::GetValue() const
{
	return m_value.c_str();
}

void CConfig::CPreferenceString::SetValue(const char* value)
{
	m_value = value;
}

void CConfig::CPreferenceString::Serialize(Xml::CNode* pNode) const
{
	CPreference::Serialize(pNode);

	pNode->InsertAttribute(Xml::CreateAttributeStringValue(PREFERENCE_ATTRIBUTE_NAME_VALUE, m_value.c_str()));
}

/////////////////////////////////////////////////////////
//CPreferencePath implementation
/////////////////////////////////////////////////////////

CConfig::CPreferencePath::CPreferencePath(const char* name, const PathType& value)
: CPreference(name, TYPE_PATH)
, m_value(value)
{

}

CConfig::PathType CConfig::CPreferencePath::GetValue() const
{
	return m_value;
}

void CConfig::CPreferencePath::SetValue(const PathType& value)
{
	m_value = value;
}

void CConfig::CPreferencePath::Serialize(Xml::CNode* node) const
{
	CPreference::Serialize(node);

	auto valueString = PathUtils::GetNativeStringFromPath(m_value);
	node->InsertAttribute(Xml::CreateAttributeStringValue(PREFERENCE_ATTRIBUTE_NAME_VALUE, valueString.c_str()));
}
