#pragma once
#include "cGameObject.h"
class cSkyBox :
	public cGameObject
{
protected:
	cSkinnedMesh* m_pMesh;
	SYNTHESIZE(cUnitPlayer*, m_pPlayer, Player);
public:
	cSkyBox();
	~cSkyBox();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

