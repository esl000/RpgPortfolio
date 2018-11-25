#pragma once

#include "iUnitAction.h"
#include "cBuff.h"

class cUnit;
class cUIImageView;

class iUnitDelegate
{
public:
	virtual void onUnitDelete(cUnit* pUnit) = 0;
};

class cUnit : public cEntity
{
public:
	enum eUnitType
	{
		E_MONSTER,
		E_NPC,
		E_CHARACTER,
	};

	enum eGravityState
	{
		E_NONE,
		E_JUMPSTART,
		E_JUMP,
		E_FALL,
		E_FALLEND
	};

protected:
	float	m_fGravityPower;
	float	m_fGravitySpeed;

	SYNTHESIZE(string, m_sMonsterName, monsterName);
	SYNTHESIZE(bool, m_isAnimChange, AnimChange);
	SYNTHESIZE(DWORD, m_dwJumpAnim, JumpAnim);
	SYNTHESIZE(DWORD, m_dwFallAnim, FallAnim);
	SYNTHESIZE(DWORD, m_dwFallEndAnim, FallEndAnim);
	SYNTHESIZE_ONLY_GETTER(eGravityState, m_eGravityState, GravityState);
	SYNTHESIZE_ADD_REF(iUnitAction*, m_pUnitAction, UnitAction);
	SYNTHESIZE(iUnitDelegate*, m_pUnitDelegate, UnitDelegate);
	SYNTHESIZE(cSkinnedMesh*, m_pMesh, Mesh);
	SYNTHESIZE(cUnit*, m_pTarget, Target);
	SYNTHESIZE(cUnit*, m_pKiller, Killer);
	SYNTHESIZE(float, m_fMaxHp, MaxHp);
	SYNTHESIZE(float, m_fMaxMp, MaxMp);
	SYNTHESIZE(float, m_fMaxExp, MaxExp);
	SYNTHESIZE(float, m_fCurrentHp, CurrentHp);
	SYNTHESIZE(float, m_fCurrentMp, CurrentMp);
	SYNTHESIZE(float, m_fCurrentExp, CurrentExp);
	SYNTHESIZE(float, m_fAttackRange, AttackRange);
	SYNTHESIZE(float, m_fCurrentDamage, CurrentDamage);
	SYNTHESIZE(float, m_fOrigDamage, OrigDamage);
	SYNTHESIZE(float, m_fCurrentSpeed, CurrentSpeed);
	SYNTHESIZE(float, m_fCurrentMoney, CurrentMoney);
	SYNTHESIZE(float, m_fOrigSpeed, OriginSpeed);
	SYNTHESIZE(float, m_fCurrentDefence, CurrentDefence);
	SYNTHESIZE(float, m_fOrigDefence, OrigDefence);
	SYNTHESIZE_PASS_BY_REF(std::string, m_sName, Name);
	SYNTHESIZE(DWORD, m_dwLevel, Level);
	SYNTHESIZE(cBuff*, m_pBuff, Buff);
	SYNTHESIZE_PASS_BY_REF(eUnitType, m_eUnitType, UnitType);

public:
	cUnit();
	virtual ~cUnit();

	virtual void Setup() = 0;
	virtual void Update();
	virtual void Render() = 0;
	virtual void Damage(float fDamage);
	virtual void Jump();
	virtual void Gravity();
	virtual void Die();


	void SetCurrentAtt(float fAtt);
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

