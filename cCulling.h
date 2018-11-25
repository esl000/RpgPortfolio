#pragma once
class cCulling
{
public:
	cCulling();
	~cCulling();

	static bool IsIn(vector<D3DXVECTOR3>& vecPosition, ST_SPHERE* pSphere);
};

