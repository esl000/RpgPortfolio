#pragma once

class cTileManager;
class cHeightMap;

#define g_pTileManager cTileManager::GetInstance()

class iLoadDelegate
{
public:
	virtual void OnLoadDelegate(ST_CHUNK_INDEX stIndex) = 0;
};

class cTileManager
{
	friend class cUILoading;
private:

	//0-4-7
	//| | |
	//2-5-8
	//| | |
	//3-6-9

	vector<cHeightMap*> m_vecViewMap;
	//00-05-10-15-20
	//|  |  |  |  |
	//01-06-11-16-21     indexz + = z - 
	//|  |  |  |  |		indexz - = z + 
	//02-07-12-17-22
	//|  |  |  |  |
	//03-08-13-18-23
	//|  |  |  |  |
	//04-09-14-19-24

	vector<cHeightMap*> m_vecLoadMap;
	vector<ST_CHUNK_INDEX> m_vecLoadIndex;

	D3DXVECTOR3 vTarget;
	volatile	bool m_isLoading;
	ST_CHUNK_INDEX m_stCurrentChuck;
	LPD3DXEFFECT		m_pEffect;
	SYNTHESIZE(cGameObject*, m_pTarget, Target);
	SYNTHESIZE(iLoadDelegate*, m_pDelegate, Delegate);
public:
	SINGLETONE(cTileManager);

	void Setup();

	static void Load(LPVOID pThis);
	bool IsMovementRange(D3DXVECTOR3 vPosition, cEntity::eEntityType eType);
	cHeightMap* LoadTile(ST_CHUNK_INDEX stIndex);

	void Update();
	void Render();

	void Destroy();

	bool GetHeight(OUT D3DXVECTOR3& vDest, D3DXVECTOR3 vPos);
	bool GetPickingMapPos(OUT D3DXVECTOR3& vDest);
	bool GetPickingPos(OUT D3DXVECTOR3& vDest);
};

