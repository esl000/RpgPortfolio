#include "StdAfx.h"
#include "cFrame.h"

cFrame::cFrame(void)
	: m_pMtlTex(NULL)
	, m_pMesh(NULL)
{
	D3DXMatrixIdentity(&m_matLocal);
	D3DXMatrixIdentity(&m_matWorld);
}


cFrame::~cFrame(void)
{
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pMesh);
}

void cFrame::Render()
{
	if(m_pMtlTex)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetTexture(0, m_pMtlTex->m_pTexture);
		g_pD3DDevice->SetMaterial(&m_pMtlTex->m_stMtl);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		m_pMesh->DrawSubset(0);
	}
	
	for each(auto c in m_vecChild)
	{
		c->Render();
	}
}

void cFrame::Update(D3DXMATRIXA16* pmatParent, int nTick)
{
	D3DXMATRIXA16 matT, matR;
	
	CalcLocalMatrixT(matT, nTick);
	CalcLocalMatrixR(matR, nTick);
	
	m_matLocal = matR * matT;

	m_matWorld = m_matLocal;
	if(pmatParent)
	{
		m_matWorld *= (*pmatParent);
	}

	
	for each(auto c in m_vecChild)
	{
		c->Update(&m_matWorld, nTick);
	}
}

void cFrame::BuildMesh( std::vector<ST_PNT_VERTEX>& vecVertex )
{
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, 0, &m_matWorld);

	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInvWorld);
		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInvWorld);
	}

	D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pMesh);

	ST_PNT_VERTEX* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	WORD* pI = NULL;
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

cFrame* cFrame::FindNode( std::string sNodeName )
{
	if(sNodeName == m_sNodeName)
		return this;

	for each(auto c in m_vecChild)
	{
		cFrame* pFrame = c->FindNode(sNodeName);
		if(pFrame != NULL)
			return pFrame;
	}
	return NULL;
}

void cFrame::AddChild( cFrame* pChild )
{
	m_vecChild.push_back(pChild);
}

void cFrame::Destroy()
{
	for each(auto c in m_vecChild)
	{
		c->Destroy();
	}
	this->Release();
}

void cFrame::CalcOriginLocalTM( D3DXMATRIXA16* pmatParent )
{
	if(pmatParent)
	{
		D3DXMATRIXA16 matInvParent;
		D3DXMatrixInverse(&matInvParent, 0, pmatParent);

		m_matLocal = m_matWorld * matInvParent;
	}
	else
	{
		m_matLocal = m_matWorld;
	}

	for each(auto c in m_vecChild)
	{
		c->CalcOriginLocalTM(&m_matWorld);
	}
}

void cFrame::CalcLocalMatrixT( OUT D3DXMATRIXA16& matT, IN int nTick )
{
	if (m_vecPosTrack.empty())
	{
		D3DXMatrixIdentity(&matT);
		matT._41 = m_matLocal._41;
		matT._42 = m_matLocal._42;
		matT._43 = m_matLocal._43;
		return;
	}

	if(nTick <= m_vecPosTrack.front().nKey)
	{
		D3DXMatrixIdentity(&matT);
		matT._41 = m_vecPosTrack.front().v.x;
		matT._42 = m_vecPosTrack.front().v.y;
		matT._43 = m_vecPosTrack.front().v.z;
		return;
	}

	if(nTick >= m_vecPosTrack.back().nKey)
	{
		D3DXMatrixIdentity(&matT);
		matT._41 = m_vecPosTrack.back().v.x;
		matT._42 = m_vecPosTrack.back().v.y;
		matT._43 = m_vecPosTrack.back().v.z;
		return;
	}

	int nPrev = 0;
	int nNext = 0;

	for (size_t i = 0; i <m_vecPosTrack.size(); ++i)
	{
		if(nTick < m_vecPosTrack[i].nKey)
		{
			nNext = i;
			break;
		}
	}
	nPrev = nNext - 1;

	float t = (nTick - m_vecPosTrack[nPrev].nKey)
		/ (float)(m_vecPosTrack[nNext].nKey - m_vecPosTrack[nPrev].nKey);

	D3DXVECTOR3 v;
	D3DXVec3Lerp(&v, &m_vecPosTrack[nPrev].v, &m_vecPosTrack[nNext].v, t);
	
	D3DXMatrixIdentity(&matT);
	matT._41 = v.x;
	matT._42 = v.y;
	matT._43 = v.z;
}

void cFrame::CalcLocalMatrixR( OUT D3DXMATRIXA16& matR, IN int nTick )
{
	if (m_vecRotTrack.empty())
	{
		matR = m_matLocal;
		matR._41 = 0.0f;
		matR._42 = 0.0f;
		matR._43 = 0.0f;
		return;
	}

	if(nTick <= m_vecRotTrack.front().nKey)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.front().q);
		return;
	}

	if(nTick >= m_vecRotTrack.back().nKey)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.back().q);
		return;
	}

	int nPrev = 0;
	int nNext = 0;

	for (size_t i = 0; i <m_vecRotTrack.size(); ++i)
	{
		if(nTick < m_vecRotTrack[i].nKey)
		{
			nNext = i;
			break;
		}
	}
	nPrev = nNext - 1;

	float t = (nTick - m_vecRotTrack[nPrev].nKey)
		/ (float)(m_vecRotTrack[nNext].nKey - m_vecRotTrack[nPrev].nKey);

	D3DXQUATERNION q;
	D3DXQuaternionSlerp(&q, &m_vecRotTrack[nPrev].q, &m_vecRotTrack[nNext].q, t);
	D3DXMatrixRotationQuaternion(&matR, &q);
}

