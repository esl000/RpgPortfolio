#pragma once

#include "cUIImageView.h"

//Item - Setting
class cItem : public cUIObject
{
	friend class cItemDatabase;
public:
	enum eItemType
	{
		E_HELMET,
		E_ARMOR1,
		E_ARMOR2,
		E_SWORD,
		E_SHIELD,
		E_NONE
	};

public:
	SYNTHESIZE(string, m_sName, Name);
	SYNTHESIZE(float, m_fDamage, Damage);
	SYNTHESIZE(float, m_fDefence, Defence);
	SYNTHESIZE(float, m_fGold, Gold);
	SYNTHESIZE(int, m_nLevel, Level);
	SYNTHESIZE(cSkinnedMesh*, m_pMesh, Mesh);
	SYNTHESIZE(cSkinnedMesh*, m_pSubMesh, SubMesh);
	SYNTHESIZE(eItemType, m_eItemType, ItemType);
	SYNTHESIZE(cUIImageView*, m_pImageView, ImageView);
	SYNTHESIZE(std::string, m_sFolder, Folder);
	SYNTHESIZE(std::string, m_sFile, File);
	SYNTHESIZE(std::string, m_sSubFile, SubFile);
	SYNTHESIZE(std::string, m_sImageName, ImageName);
	SYNTHESIZE(bool, m_bIsRotation, IsRotation);
public:
	cItem();
	virtual ~cItem();

	virtual void Setup();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
};

