#pragma once

#include "cAllocateHierarchy.h"

#define g_pResourceManager cResourceManager::GetInstance()

class cResourceManager
{
private:
	map<string, ST_BONE*> m_mapFrame;
	map<string, LPD3DXANIMATIONCONTROLLER> m_mapAniController;

private:

	void Load(OUT ST_BONE** pRootBone,
		OUT LPD3DXANIMATIONCONTROLLER* pAnimController, 
		string sFolder, string sFile);

	void SetWorldMatrix(ST_BONE* pRootBone, ST_BONE* pBone);

	LPD3DXANIMATIONCONTROLLER CloneAnimController(LPD3DXANIMATIONCONTROLLER pAnim);

public:
	SINGLETONE(cResourceManager);

	void GetResourse(OUT ST_BONE** pRootBone,
		OUT LPD3DXANIMATIONCONTROLLER* pAnimController,
		char* szFolder, char* szFile);

	void GetResourse(OUT ST_BONE** pRootBone,
		OUT LPD3DXANIMATIONCONTROLLER* pAnimController, 
		string sFolder, string sFile);

	void Destroy();
};

