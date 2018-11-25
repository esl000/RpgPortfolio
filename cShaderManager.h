#pragma once

#define g_pShaderManager cShaderManager::GetInstance()

class cShaderManager
{
private:
	map<string, LPD3DXEFFECT> m_mapEffect;
public:
	SINGLETONE(cShaderManager);

	LPD3DXEFFECT getEffect(std::string sFullPath);
	LPD3DXEFFECT getEffect(char* szFullPath);

	void Destroy();
};

