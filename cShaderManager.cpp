#include "stdafx.h"
#include "cShaderManager.h"


cShaderManager::cShaderManager()
{
}


cShaderManager::~cShaderManager()
{
}

LPD3DXEFFECT cShaderManager::getEffect(std::string sFullPath)
{
	if (m_mapEffect.find(sFullPath) == m_mapEffect.end())
	{
		m_mapEffect[sFullPath] = LoadEffect(sFullPath.c_str());
	}

	return m_mapEffect[sFullPath];
}

LPD3DXEFFECT cShaderManager::getEffect(char* szFullPath)
{
	return getEffect(string(szFullPath));
}

void cShaderManager::Destroy()
{

}
