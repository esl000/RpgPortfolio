#pragma once

class cOctree;

#define g_pIntersectManager cIntersectManager::GetInstance()

class cIntersectManager
{
private:
	float m_fSearchTime;
	float m_fOctreeTime;
	float m_fCurrentTime;
	float m_fCurrentOctTime;
	vector<cEntity*> m_vecNearEntity;
	vector<cOctree*> m_vecOctree;
	SYNTHESIZE(cUnit*, m_pTarget, Target);
	static void SearchEntitys(LPVOID pThis);
	static void SearchOctrees(LPVOID pThis);
public:
	SINGLETONE(cIntersectManager);

	void Setup();
	void Update();
	void Render();
	void Synchronization(cEntity* pEntity);
	bool IntersectEntitys(ST_SPHERE stBoundingSphere);
	bool IntersectEntitys(ST_SPHERE stBoundingSphere, D3DXVECTOR3 vDir);
	bool IntersectInBuilding(IN ST_SPHERE stBoundingSphere, IN D3DXVECTOR3 vTemp, OUT D3DXVECTOR3& vDest);
	bool PickingInBuilding(OUT D3DXVECTOR3& vDest);
};

