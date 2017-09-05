#pragma once

#include <string>
#include "boost_filesystem_def.h"
#include <map>
#include <mutex>
#include "xml/Node.h"

namespace Framework
{
	class CConfig
	{
	public:
		typedef boost::filesystem::path PathType;

											CConfig(const PathType&, bool readonly = false);
											CConfig(const CConfig&) = delete;
		virtual								~CConfig();

		CConfig&							operator =(const CConfig&) = delete;

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
			virtual							~CPreference() = default;
			const char*						GetName() const;
			PREFERENCE_TYPE					GetType() const;
			const char*						GetTypeString() const;
			virtual void					Serialize(Framework::Xml::CNode*) const;

		private:
			std::string						m_name;
			PREFERENCE_TYPE					m_type;
		};

		class CPreferenceInteger : public CPreference
		{
		public:
											CPreferenceInteger(const char*, int);
			virtual							~CPreferenceInteger() = default;
			int								GetValue() const;
			void							SetValue(int);
			void							Serialize(Framework::Xml::CNode*) const override;

		private:
			int								m_value;
		};

		class CPreferenceBoolean : public CPreference
		{
		public:
											CPreferenceBoolean(const char*, bool);
			virtual							~CPreferenceBoolean() = default;
			bool							GetValue() const;
			void							SetValue(bool);
			void							Serialize(Framework::Xml::CNode*) const override;

		private:
			bool							m_value;
		};

		class CPreferenceString : public CPreference
		{
		public:
											CPreferenceString(const char*, const char*);
			virtual							~CPreferenceString() = default;
			const char*						GetValue() const;
			void							SetValue(const char*);
			void							Serialize(Framework::Xml::CNode*) const override;

		private:
			std::string						m_value;
		};

		typedef std::shared_ptr<CPreference> PreferencePtr;
		typedef std::map<std::string, PreferencePtr> PreferenceMapType;

		void								Load();
		void								InsertPreference(const PreferencePtr&);

		template <typename Type> std::shared_ptr<Type>			FindPreference(const char*);
		template <typename Type> static std::shared_ptr<Type>	CastPreference(const PreferencePtr&);

		PreferenceMapType					m_preferences;
		std::mutex							m_mutex;
		PathType							m_path;
		bool								m_readonly;
	};
}
