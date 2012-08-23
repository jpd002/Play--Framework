#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>
#include <boost/thread.hpp>
#include <boost/utility.hpp>
#include <boost/filesystem/path.hpp>
#include <map>
#include "xml/Node.h"

namespace Framework
{
	class CConfig : public boost::noncopyable
	{
	public:
		typedef boost::filesystem::path PathType;

											CConfig(const PathType&);
		virtual								~CConfig();

		static std::string					MakePreferenceName(const std::string&, const std::string& = "", const std::string& = "", const std::string& = "");

		void								RegisterPreferenceInteger(const char*, int);
		void								RegisterPreferenceBoolean(const char*, bool);
		void								RegisterPreferenceString(const char*, const char*);

		int									GetPreferenceInteger(const char*);
		bool								GetPreferenceBoolean(const char*);
		const char*							GetPreferenceString(const char*);

		bool								SetPreferenceInteger(const char*, int);
		bool								SetPreferenceBoolean(const char*, bool);
		bool								SetPreferenceString(const char*, const char*);

		void								Save();
		PathType							GetConfigPath() const;

	private:
		enum PREFERENCE_TYPE
		{
			TYPE_INTEGER,
			TYPE_BOOLEAN,
			TYPE_STRING,
		};

		class CPreference
		{
		public:
											CPreference(const char*, PREFERENCE_TYPE);
			virtual							~CPreference();
			const char*						GetName() const;
			PREFERENCE_TYPE					GetType() const;
			const char*						GetTypeString() const;
			virtual	void					Serialize(Framework::Xml::CNode*) const;

		private:
			std::string						m_sName;
			PREFERENCE_TYPE					m_nType;
		};

		class CPreferenceInteger : public CPreference
		{
		public:
											CPreferenceInteger(const char*, int);
			virtual							~CPreferenceInteger();
			int								GetValue() const;
			void							SetValue(int);
			virtual void					Serialize(Framework::Xml::CNode*) const;

		private:
			int								m_nValue;
		};

		class CPreferenceBoolean : public CPreference
		{
		public:
											CPreferenceBoolean(const char*, bool);
			virtual							~CPreferenceBoolean();
			bool							GetValue() const;
			void							SetValue(bool);
			virtual void					Serialize(Framework::Xml::CNode*) const;

		private:
			bool							m_nValue;
		};

		class CPreferenceString : public CPreference
		{
		public:
											CPreferenceString(const char*, const char*);
			virtual							~CPreferenceString();
			const char*						GetValue() const;
			void							SetValue(const char*);
			virtual void					Serialize(Framework::Xml::CNode*) const;

		private:
			std::string						m_sValue;
		};

		typedef std::map<std::string, CPreference*> PreferenceMapType;

		void								Load();
		template <typename Type> Type*		FindPreference(const char*);
		template <typename Type> Type*		CastPreference(CPreference*);
		void								InsertPreference(CPreference*);

		PreferenceMapType					m_preferences;
		boost::mutex						m_mutex;
		PathType							m_path;
	};
}

#endif
