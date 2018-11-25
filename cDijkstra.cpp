#include "stdafx.h"
#include "cDijkstra.h"


cDijkstra::cDijkstra()
	: m_dSize(0)
{
}


cDijkstra::~cDijkstra()
{
}

cDijkstra	cDijkstra::getDijkstra(DWORD dSize, vector<sEdge> vecEdge)
{
	cDijkstra	dijkstra;
	dijkstra.m_dSize = dSize;
	dijkstra.m_vecEdge = vecEdge;


	dijkstra.m_vecTree.resize(dSize);

	for (size_t i = 0; i < dSize; ++i)
	{
		dijkstra.m_vecTree[i].resize(dSize);
		for (size_t j = 0; j < dSize; ++j)
		{
			if (i == j)
			{
				dijkstra.m_vecTree[i][j].bVisted = true;
				dijkstra.m_vecTree[i][j].fTotalCost = 0;
			}
			else
			{
				dijkstra.m_vecTree[i][j].bVisted = false;
				dijkstra.m_vecTree[i][j].dViaIndex = dSize + 1;
				dijkstra.m_vecTree[i][j].fTotalCost = COSTINFINITY;
			}
		}

		DWORD	dCurrentIndex = i;

		for (size_t j = 0; j < dSize; ++j)
		{

			for (size_t k = 0; k < dijkstra.m_vecTree[i].size(); ++k)
			{
				if (dijkstra.m_vecTree[i][k].bVisted)
					continue;
				float fEdgeCost = COSTINFINITY;

				for (size_t l = 0; l < vecEdge.size(); ++l)
				{
					if ((vecEdge[l].dViaIndex == dCurrentIndex &&
						vecEdge[l].dToIndex == k) ||
						(vecEdge[l].dViaIndex == k &&
						vecEdge[l].dToIndex == dCurrentIndex))
					{
						fEdgeCost = vecEdge[l].fCost;
						break;
					}
				}
				if (fEdgeCost > COSTINFINITY - 0.001f)
					continue;

				if (dijkstra.m_vecTree[i][k].fTotalCost >
					fEdgeCost + dijkstra.m_vecTree[i][dCurrentIndex].fTotalCost)
				{
					dijkstra.m_vecTree[i][k].dViaIndex = dCurrentIndex;
					dijkstra.m_vecTree[i][k].fTotalCost = fEdgeCost + dijkstra.m_vecTree[i][dCurrentIndex].fTotalCost;
				}
			}

			int dLessCostIndex = -1;
			float fLessCost = COSTINFINITY + 1;

			if (j == dSize - 1)
				continue;

			for (size_t k = 0; k < dSize; ++k)
			{
				if (dijkstra.m_vecTree[i][k].bVisted)
					continue;
				if (dijkstra.m_vecTree[i][k].fTotalCost < fLessCost)
				{
					dLessCostIndex = k;
					fLessCost = dijkstra.m_vecTree[i][k].fTotalCost;
				}
			}

			dijkstra.m_vecTree[i][dLessCostIndex].bVisted = true;
			dCurrentIndex = dLessCostIndex;
		}
	}


	return dijkstra;
}

vector<DWORD>		cDijkstra::getFindCourse(DWORD dStartIndex, DWORD dLastIndex)
{
	vector<DWORD>		vecIndex;
	for (DWORD i = dLastIndex;
		i != dStartIndex;
		i = m_vecTree[dStartIndex][i].dViaIndex)
	{
		if (i == m_dSize + 1)
		{
			vecIndex.clear();
			vecIndex.push_back(dStartIndex);
			return vecIndex;
		}
		vecIndex.push_back(i);
	}
	vecIndex.push_back(dStartIndex);

	return vecIndex;
}
