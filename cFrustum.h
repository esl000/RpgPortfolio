#pragma once

#define g_pFrustum cFrustum::GetInstance()

class cFrustum
{
private:
	std::vector<D3DXVECTOR3>	m_vecProjVertex;
	std::vector<D3DXPLANE>		m_vecPlane;

public:
	SINGLETONE(cFrustum);

	void Setup();
	void Update();
	bool IsIn(ST_SPHERE* pSphere);

};

