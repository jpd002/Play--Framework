#pragma once

#include "Singleton.h"
#include <android/asset_manager_jni.h>

namespace Framework
{
	namespace Android
	{
		class CAssetManager : public CSingleton<CAssetManager>
		{
		public:
			AAssetManager*    GetAssetManager() const;
			void              SetAssetManager(AAssetManager*);
			
		private:
			AAssetManager*    m_assetManager = nullptr;
		};
	}
}
