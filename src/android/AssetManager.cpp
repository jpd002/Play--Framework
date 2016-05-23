#include "android/AssetManager.h"

using namespace Framework;
using namespace Framework::Android;

AAssetManager* CAssetManager::GetAssetManager() const
{
	return m_assetManager;
}

void CAssetManager::SetAssetManager(AAssetManager* assetManager)
{
	m_assetManager = assetManager;
}
