#include "stdafx.h"
#include "cCulling.h"


cCulling::cCulling()
{
}


cCulling::~cCulling()
{
}

bool cCulling::IsIn(vector<D3DXVECTOR3>& vecPosition, ST_SPHERE* pSphere)
{
	if (vecPosition.size() == 0)
		return false;
	vector<D3DXPLANE> vecPlane;
	int nCnt = 0;
	D3DXPLANE stPlane;
	for (size_t i = 0; i < vecPosition.size(); i += 3)
	{
		D3DXPlaneFromPoints(&stPlane,
			&vecPosition[i], &vecPosition[i + 1], &vecPosition[i + 2]);
		vecPlane.push_back(stPlane);
	}

	for each(D3DXPLANE p in vecPlane)
	{
		if (D3DXPlaneDotCoord(&p, &pSphere->vCenter) > pSphere->fRadius)
			return false;
	}
	return true;
}
