#include "stdafx.h"
#include "cNpcCourse.h"


cNpcCourse::cNpcCourse()
{
}


cNpcCourse::~cNpcCourse()
{
}

void cNpcCourse::Load()
{
	FILE* fp;
	fopen_s(&fp, "npc/npcCourse.txt", "r");

	if (!fp)
		return;
	
	int nCourseSize = 0;

	if (fp)
	{
		fscanf_s(fp, "%d", &nCourseSize);

		for (int i = 0; i < nCourseSize; ++i)
		{
			char szBuf[1024];
		//	char szTemp[1024];
			fgets(szBuf, 1024, fp);

			float x, y, z;

			for (int i = 0; i < 3; ++i)
			{
				if (i == 0)
					x = atof(strtok_s(szBuf, " ", (char**)szBuf));
				if (i == 1)
					y = atof(strtok_s(szBuf, " ", (char**)szBuf));
				if (i == 2)
					z = atof(strtok_s(szBuf, " ", (char**)szBuf));
			}

			D3DXVECTOR3 vPos;
			vPos.x = x;
			vPos.y = y;
			vPos.z = z;

			m_vecVCourse.push_back(vPos);
		}
	}

	if (!fp)
		fclose(fp);
	return;
}

std::vector<D3DXVECTOR3> cNpcCourse::GetCourse()
{
	return m_vecVCourse;
}

