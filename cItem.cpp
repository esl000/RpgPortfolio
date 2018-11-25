#include "stdafx.h"
#include "cItem.h"




cItem::cItem()
	: m_sName("")
	, m_fDamage(0.f)
	, m_fDefence(0.f)
	, m_fGold(0.f)
	, m_nLevel(0)
	, m_pMesh(NULL)
	, m_pSubMesh(NULL)
	, m_eItemType(E_NONE)
	, m_pImageView(NULL)
	, m_bIsRotation(false)
{
}


cItem::~cItem()
{
	SAFE_DELETE(m_pMesh);
	SAFE_RELEASE(m_pImageView);
}

void cItem::Setup()
{
	m_pMesh = new cSkinnedMesh(m_sFolder.c_str(), m_sFile.c_str());
	if (m_bIsRotation)
		m_pMesh->SetIsRotation(true);
	else
		m_pMesh->SetIsRotation(false);

	if (m_eItemType == E_ARMOR1)
	{
		m_pSubMesh = new cSkinnedMesh(m_sFolder.c_str(), m_sSubFile.c_str());
		if (m_bIsRotation)
			m_pSubMesh->SetIsRotation(true);
		else
			m_pSubMesh->SetIsRotation(false);
	}

	m_pImageView = new cUIImageView;
	m_pImageView->SetTexture(m_sImageName);
	m_pImageView->SetScale(D3DXVECTOR3(0.65f, 0.65f, 1.f));
}

void cItem::Update()
{
	if (m_pImageView)
		m_pImageView->Update();
}

void cItem::Render(LPD3DXSPRITE pSprite)
{
	if (m_pImageView)
		m_pImageView->Render(pSprite);
}
