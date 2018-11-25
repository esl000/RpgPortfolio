#include "stdafx.h"
#include "cEffectTriangle.h"


cEffectTriangle::cEffectTriangle()
		:m_vecVertex(NULL)
		, m_fColorChangeTime(0.0f)
		, m_fCurrentCount(0.0f)
		, m_fRed(0.0f)
		, m_fGreen(0.0f)
		, m_fBlue(0.0f)
		, m_fAlpha(0.0f)
{
}


cEffectTriangle::~cEffectTriangle()
{
	m_vecVertex.clear();
}

void cEffectTriangle::Setup(vector<ST_PC_VERTEX> vecVertex)
{
	m_vecVertex = vecVertex;	
}

void cEffectTriangle::Update()
{
	m_fCurrentCount += g_pTimeManager->GetElapsedTime();

	if (m_fCurrentCount > m_fColorChangeTime)
	{
		for (int i = 0; i < m_vecVertex.size(); ++i)
		{
			m_vecVertex[i].c = D3DXCOLOR(m_fRed, m_fGreen, m_fBlue, m_fAlpha);
		}
		m_fAlpha -= 0.1f;
		m_fCurrentCount = 0.0f;
	}
}

void cEffectTriangle::Render()
{
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3,
		&m_vecVertex[0], sizeof(ST_PC_VERTEX));
}
