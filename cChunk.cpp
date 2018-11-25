#include "stdafx.h"
#include "cChunk.h"


cChunk::cChunk()
	: m_pMesh(NULL)
	, m_pTexture(NULL)
{
}


cChunk::~cChunk()
{
	SAFE_RELEASE(m_pMesh);
}

void cChunk::Setup(vector<ST_PNT_VERTEX>& vecVertex, DWORD dwSize)
{
	//EnterCriticalSection(&cs);
	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pMesh);
	//LeaveCriticalSection(&cs);
	ST_PNT_VERTEX* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		pI[i] = i;
	}
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, sizeof(DWORD) * vecVertex.size() / 3);
	m_pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdjBuffer(vecVertex.size());
	m_pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

	m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuffer[0],
		0, 0, 0);
}

void cChunk::Render()
{
	if (m_pMesh)
	{
		g_pD3DDevice->SetTexture(0, m_pTexture);
		m_pMesh->DrawSubset(0);
	}
}
