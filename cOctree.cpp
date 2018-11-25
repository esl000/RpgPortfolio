#include "stdafx.h"
#include "cOctree.h"


cOctree::cOctree()
	: m_pRoot(NULL)
	, m_pMainRoot(NULL)
	, m_pSphere(NULL)
	, m_dwDirection(E_ROOT)
	, m_vCenter(0, 0, 0)
	, m_fRadius(0.f)
	, m_stSphere(D3DXVECTOR3(0, 0, 0), 0.f)
{
}


cOctree::~cOctree()
{
	for each(auto p in m_mapChild)
	{
		SAFE_DELETE(p.second);
	}
}

void cOctree::SetOctree(DWORD dwDirection, D3DXVECTOR3 vCenter, float fRadius, vector<ST_FACE>& vecFace)
{
	if (dwDirection == E_ROOT)
	{
		m_vecDir.push_back(E_UP);
		m_vecDir.push_back(E_RIGHT);
		m_vecDir.push_back(E_TOP);

		m_vecDir.push_back(E_UP);
		m_vecDir.push_back(E_RIGHT);
		m_vecDir.push_back(E_BOTTOM);


		m_vecDir.push_back(E_UP);
		m_vecDir.push_back(E_LEFT);
		m_vecDir.push_back(E_TOP);

		m_vecDir.push_back(E_UP);
		m_vecDir.push_back(E_LEFT);
		m_vecDir.push_back(E_BOTTOM);


		m_vecDir.push_back(E_DOWN);
		m_vecDir.push_back(E_RIGHT);
		m_vecDir.push_back(E_TOP);

		m_vecDir.push_back(E_DOWN);
		m_vecDir.push_back(E_RIGHT);
		m_vecDir.push_back(E_BOTTOM);


		m_vecDir.push_back(E_DOWN);
		m_vecDir.push_back(E_LEFT);
		m_vecDir.push_back(E_TOP);

		m_vecDir.push_back(E_DOWN);
		m_vecDir.push_back(E_LEFT);
		m_vecDir.push_back(E_BOTTOM);
	}

	m_dwDirection = dwDirection;
	m_vCenter = vCenter;
	m_fRadius = fRadius;

	m_stSphere = ST_SPHERE(vCenter, fRadius * sqrt(3));

	if (fRadius < OCTREEMINIMUMRADIUS)
	{
		cout << "final size : " << vecFace.size() << endl;
		m_vecNode = vecFace;
		return;
	}


	map<DWORD, vector<ST_FACE>> mapDirNode;

	vector<ST_FACE> vecOrgIndex;
	for (size_t i = 0; i < vecFace.size(); ++i)
	{
		CheckPos(vecFace[i], vCenter, mapDirNode);
	}

	//vector<DWORD> vecDir;

	//vecDir.push_back(E_UP | E_RIGHT | E_TOP);
	//vecDir.push_back(E_UP | E_RIGHT | E_BOTTOM);
	//vecDir.push_back(E_UP | E_LEFT | E_TOP);
	//vecDir.push_back(E_UP | E_LEFT | E_BOTTOM);

	//vecDir.push_back(E_DOWN | E_RIGHT | E_TOP);
	//vecDir.push_back(E_DOWN | E_RIGHT | E_BOTTOM);
	//vecDir.push_back(E_DOWN | E_LEFT | E_TOP);
	//vecDir.push_back(E_DOWN | E_LEFT | E_BOTTOM);

	//for each(auto dw in vecDir)
	//{
	//	if (mapDirNode.find(dw) == mapDirNode.end())
	//	{
	//		vector<ST_FACE> vecf;
	//		mapDirNode[dw] = vecf;
	//	}
	//}

	for each(auto v in mapDirNode)
	{
		cOctree* pOctree = new cOctree;
		pOctree->m_pMainRoot = m_pMainRoot;
		pOctree->m_dwDirection = v.first;
		D3DXVECTOR3 vChildCenter = vCenter;
		if (v.first & E_UP)
		{
			vChildCenter.y += fRadius / 2.f;
		}
		else if (v.first & E_DOWN)
		{
			vChildCenter.y -= fRadius / 2.f;
		}

		if (v.first & E_RIGHT)
		{
			vChildCenter.x += fRadius / 2.f;
		}
		else if (v.first & E_LEFT)
		{
			vChildCenter.x -= fRadius / 2.f;
		}

		if (v.first & E_TOP)
		{
			vChildCenter.z += fRadius / 2.f;
		}
		else if (v.first & E_BOTTOM)
		{
			vChildCenter.z -= fRadius / 2.f;
		}

		pOctree->m_pRoot = this;
		m_mapChild[v.first] = pOctree;
		pOctree->SetOctree(v.first, vChildCenter, fRadius / 2.f, v.second);
	}
}

vector<ST_FACE> cOctree::GetNode()
{
	return m_vecNode;
}

bool cOctree::isPicked(cRay r, D3DXVECTOR3& vDest)
{
	if (r.IsPicked(&m_stSphere))
	{
		if (m_mapChild.size() == 0)
		{
			//있는 페이스들과 충돌처리 ㄱㄱ
			//if (RootPicked(r, vDest))
			//{
			//	return true;
			//}

			for each(auto v in m_vecNode)
			{
				D3DXVECTOR3 vPos;
				if (r.GetPickedPosition(vPos, v.v1, v.v2, v.v3))
				{
					vDest = vPos;
					return true;
				}
			}

			return false;
		}
		else
		{
			for each(auto v in m_vecNode)
			{
				D3DXVECTOR3 vPos;
				if (r.GetPickedPosition(vPos, v.v1, v.v2, v.v3))
				{
					vDest = vPos;
					return true;
				}
			}

			for each(auto p in m_mapChild)
			{
				if (p.second->isPicked(r, vDest))
					return true;
			}
		}
	}
	return false;
}

void cOctree::GetNearOctree(IN ST_SPHERE stSphere, OUT set<cOctree*>& setOctree)
{
	if (IntersectSphereSphere(stSphere, m_stSphere))
	{
		if (setOctree.find(this) == setOctree.end())
			setOctree.insert(this);

		for each(auto p in m_mapChild)
		{
			p.second->GetNearOctree(stSphere, setOctree);
		}
	}
}

bool cOctree::OnlyPicking(cRay r, D3DXVECTOR3& vDest)
{
	D3DXVECTOR3 vTemp;
	bool isCollision = false;
	if (r.IsPicked(&m_stSphere))
	{
		for each(auto v in m_vecNode)
		{
			D3DXVECTOR3 vPos;
			if (r.GetPickedPosition(vPos, v.v1, v.v2, v.v3))
			{
				if (isCollision && vTemp.y  < vPos.y)
					vTemp = vPos;

				if (!isCollision)
				{
					vTemp = vPos;
					isCollision = true;
				}
			}
		}
	}

	if (isCollision)
	{
		vDest = vTemp;
		return true;
	}

	return false;
}

void cOctree::Render()
{
	//SphereRender(m_stSphere);

	//for each(auto p in m_mapChild)
	//{
	//p.second->SphereRender(p.second->GetSphere());
	//}
}

bool cOctree::RootPicked(cRay r, D3DXVECTOR3& vDest)
{
	if (m_pRoot)
	{
		for each(auto v in m_pRoot->m_vecNode)
		{
			D3DXVECTOR3 vPos;
			if (r.GetPickedPosition(vPos, v.v1, v.v2, v.v3))
			{
				vDest = vPos;
				return true;
			}
		}
		m_pRoot->RootPicked(r, vDest);
	}

	return false;
}



void cOctree::SphereRender(ST_SPHERE stSphere)
{

#ifdef DEBUG_SPHERE
	if (m_pSphere)
		{
			D3DXMATRIXA16 mat;
			D3DXMatrixTranslation(&mat, stSphere.vCenter.x, stSphere.vCenter.y, stSphere.vCenter.z);
			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
			m_pSphere->DrawSubset(0);
			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
		else
		{
			D3DXCreateSphere(g_pD3DDevice, stSphere.fRadius, 8, 8, &m_pSphere, NULL);
			D3DXMATRIXA16 mat;
			D3DXMatrixTranslation(&mat, stSphere.vCenter.x, stSphere.vCenter.y, stSphere.vCenter.z);
			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
			m_pSphere->DrawSubset(0);
			g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
#else

#endif
}

void cOctree::CheckPos(ST_FACE& stFace, D3DXVECTOR3& vCenter, map<DWORD, vector<ST_FACE>>& mapDir)
{
	DWORD dwDir = 0;

	if (stFace.v1.y > vCenter.y &&
		stFace.v2.y > vCenter.y &&
		stFace.v3.y > vCenter.y)
	{
		dwDir |= E_UP;
	}
	else if (stFace.v1.y < vCenter.y &&
		stFace.v2.y < vCenter.y &&
		stFace.v3.y < vCenter.y)
	{
		dwDir |= E_DOWN;
	}
	else
	{
		dwDir |= E_UP;
		dwDir |= E_DOWN;
	}


	if (stFace.v1.x > vCenter.x &&
		stFace.v2.x > vCenter.x &&
		stFace.v3.x > vCenter.x)
	{
		dwDir |= E_RIGHT;
	}
	else if (stFace.v1.x < vCenter.x &&
		stFace.v2.x < vCenter.x &&
		stFace.v3.x < vCenter.x)
	{
		dwDir |= E_LEFT;
	}
	else
	{
		dwDir |= E_RIGHT;
		dwDir |= E_LEFT;
	}


	if (stFace.v1.z > vCenter.z &&
		stFace.v2.z > vCenter.z &&
		stFace.v3.z > vCenter.z)
	{
		dwDir |= E_TOP;
	}
	else if (stFace.v1.z < vCenter.z &&
		stFace.v2.z < vCenter.z &&
		stFace.v3.z < vCenter.z)
	{
		dwDir |= E_BOTTOM;
	}
	else
	{
		dwDir |= E_TOP;
		dwDir |= E_BOTTOM;
	}

	for (int i = 0; i < m_pMainRoot->m_vecDir.size(); i += 3)
	{
		if (dwDir & m_pMainRoot->m_vecDir[i] &&
			dwDir & m_pMainRoot->m_vecDir[i + 1] && 
			dwDir & m_pMainRoot->m_vecDir[i + 2])
			mapDir[m_pMainRoot->m_vecDir[i] | 
					m_pMainRoot->m_vecDir[i + 1] | 
					m_pMainRoot->m_vecDir[i + 2]].push_back(stFace);
	}
}

