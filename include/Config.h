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
		void								RegisterPreferencePath(const char*, const PathType&);

		int									GetPreferenceInteger(const char*);
		bool								GetPreferenceBoolean(const char*);
		const char*							GetPreferenceString(const char*);
		PathType							GetPreferencePath(const char*);

		bool								SetPreferenceInteger(const char*, int);
		bool								SetPreferenceBoolean(const char*, bool);
		bool								SetPreferenceString(const char*, const char*);
		bool								SetPreferencePath(const char*, const PathType&);

		void								Save();
		PathType							GetConfigPath() const;

	private:
		enum PREFERENCE_TYPE
		{
			TYPE_INTEGER,
			TYPE_BOOLEAN,
			TYPE_STRING,
			TYPE_PATH,
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
			enum
			{
				PREFERENCE_TYPE_ID = TYPE_INTEGER
			};

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
			enum
			{
				PREFERENCE_TYPE_ID = TYPE_BOOLEAN
			};

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
			enum
			{
				PREFERENCE_TYPE_ID = TYPE_STRING
			};

											CPreferenceString(const char*, const char*);
			virtual							~CPreferenceString() = default;
			const char*						GetValue() const;
			void							SetValue(const char*);
			void							Serialize(Framework::Xml::CNode*) const override;

		private:
			std::string						m_value;
		};

		class CPreferencePath : public CPreference
		{
		public:
			enum
			{
				PREFERENCE_TYPE_ID = TYPE_PATH
			};

											CPreferencePath(const char*, const PathType&);
			virtual							~CPreferencePath() = default;
			PathType						GetValue() const;
			void							SetValue(const PathType&);
			void							Serialize(Framework::Xml::CNode*) const override;

		private:
			PathType						m_value;
		};

		typedef std::shared_ptr<CPreference> PreferencePtr;
		typedef std::map<std::string, PreferencePtr> PreferenceMapType;

		void								Load();
		void								InsertPreference(const PreferencePtr&);

		template <typename Type> std::shared_ptr<Type>			FindPreference(const char*);

		template <typename Type>
		static std::shared_ptr<Type> CastPreference(const PreferencePtr& preference)
		{
			if(preference->GetType() != Type::PREFERENCE_TYPE_ID)
			{
				return std::shared_ptr<Type>();
			}
			return std::static_pointer_cast<Type>(preference);
		}

		PreferenceMapType					m_preferences;
		std::mutex							m_mutex;
		PathType							m_path;
		bool								m_readonly;
	};
}
