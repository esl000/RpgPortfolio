#pragma once

class cPyramid;

class cGrid
{
private:
	IDirect3DVertexBuffer9*		m_pVertexBuffer;
	std::vector<ST_PC_VERTEX>		m_vecVertex;
	std::vector<cPyramid*>		m_vecPyramid;

public:
	cGrid(void);
	~cGrid(void);
	void Setup(int nHalf, float fInterval);
	void Render();
};

