#pragma once

class cEntity;

class iEntityDelegate
{
public:
	virtual void onEntityDelete(cEntity* pEntity) = 0;
};

class cEntity : public cGameObject
{
public:
	enum eEntityType
	{
		E_BUILDING,
		E_OBJECT,
		E_UNIT,
		E_MONSTER,
		E_NPC,
		E_PLAYER
	};

protected:
	SYNTHESIZE_PASS_BY_REF(LPD3DXMESH, m_pObjMesh, ObjMesh);
	SYNTHESIZE(iEntityDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(ST_SPHERE, m_stFrustumSphere, FrustumSphere);
	SYNTHESIZE(eEntityType, m_eEntityType, EntityType);
	SYNTHESIZE(LPD3DXMESH, m_pSphereMesh, SphereMesh);
public:

	cEntity();
	virtual ~cEntity();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void SphereRender(ST_SPHERE stSphere);

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

