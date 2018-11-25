#pragma once

class iEffect;

class iEffectDelegate
{
public:
	virtual void OnEffectFinish(iEffect* peffect) = 0;
};

class iEffect : public cGameObject
{
public:
	enum eEffectType
	{
		E_NONE,
		E_DIEEFFECT,
		E_PLAYEREFFECT
	};
protected:
	SYNTHESIZE(eEffectType, m_eEffectType, EffectType);
	SYNTHESIZE(cUnit*, m_pUnit, EffectUnit);
	SYNTHESIZE(iEffectDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(cSkinnedMesh*, m_pMesh, Mesh);
	SYNTHESIZE(ST_SPHERE, m_stFrustumSphere, FrustumSphere);
	SYNTHESIZE(float, m_fMaxTime, MaxTime);
	SYNTHESIZE(float, m_fCurrentTime, CurrentTime);
public:
	iEffect();
	virtual ~iEffect();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

