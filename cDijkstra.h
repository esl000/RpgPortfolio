#pragma once

#define COSTINFINITY 1000000

struct  sEdge
{
	DWORD		dViaIndex;
	DWORD		dToIndex;
	float		fCost;
};

struct sChecker
{
	bool		bVisted;
	DWORD	dViaIndex;
	float	fTotalCost;
};

class cDijkstra
{
private:

	DWORD m_dSize;
	vector<sEdge> m_vecEdge;
	vector<vector<sChecker>> m_vecTree;

public:

	static cDijkstra	getDijkstra(DWORD dSize, vector<sEdge> vecEdge);
	vector<DWORD>		getFindCourse(DWORD dStartIndex, DWORD dLastIndex);
	cDijkstra();
	~cDijkstra();
};

