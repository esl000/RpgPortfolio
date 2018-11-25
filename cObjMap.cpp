#include "StdAfx.h"
#include "cObjMap.h"


cObjMap::cObjMap(void)
{
}

cObjMap::~cObjMap(void)
{
}

bool cObjMap::GetHeight( IN float x, IN float z, OUT float& y )
{
	D3DXVECTOR3 vRayPos(x, 1000.0f, z);
	D3DXVECTOR3 vRayDir(0.f, -1.f, 0.f);
	for (size_t i = 0; i < m_vecVertex.size(); i += 3)
	{
		float u, v, t;

		if(D3DXIntersectTri(&m_vecVertex[i],
			&m_vecVertex[i + 1],
			&m_vecVertex[i + 2], 
			&vRayPos,
			&vRayDir,
			&u, &v, &t))
		{
			y = 1000.f - t;
			return true;
		}
	}
	return false;
}

void cObjMap::Setup( char* szFullPath, D3DXMATRIXA16* pmat )
{
	std::vector<D3DXVECTOR3> vecV;

	FILE* fp = NULL;
	fopen_s(&fp, szFullPath, "r");
	while(true)
	{
		if(feof(fp))
			break;

		char szBuf[1024] = {0, };
		fgets(szBuf, 1024, fp);

		if(strlen(szBuf) == 0)
			continue;

		if(szBuf[0] == '#')
		{
			continue;
		}
		else if(szBuf[0] == 'm')
		{
		}
		else if(szBuf[0] == 'g')
		{
		}
		else if(szBuf[0] == 'v')
		{
			if(szBuf[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				D3DXVECTOR3 p = D3DXVECTOR3(x, y, z);
				if(pmat)
				{
					D3DXVec3TransformCoord(&p, &p, pmat);
				}
				vecV.push_back(p);
			}
			else if(szBuf[1] == 't')
			{
			}
			else if(szBuf[1] == 'n')
			{
			}
		}
		else if(szBuf[0] == 'u')
		{ 
		}
		else if(szBuf[0] == 'f')
		{ 
			int aIndex[3];
			sscanf_s(szBuf, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&aIndex[0], &aIndex[1], &aIndex[2]);

			for (int i = 0; i < 3; ++i)
			{
				m_vecVertex.push_back(vecV[aIndex[i] - 1]);
			}
		}
	}
	fclose(fp);
}
