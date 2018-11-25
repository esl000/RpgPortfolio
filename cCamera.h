#pragma once


class cCamera : public cGameObject
{
private:
	D3DXMATRIXA16					matView, matProj;
	D3DXVECTOR3					m_vLookAt;
	D3DXVECTOR3					m_vUp;
	D3DXVECTOR3*					m_pTarget;

	POINT						m_ptPrev;
	float						m_fCurrentDistanse;
	float						m_fRotAngleX;
	float						m_fRotAngleY;
	float						m_fDistance;
	cUnit*						m_pPlayer;
	bool							m_isLButtonDown;
	SYNTHESIZE(D3DXVECTOR3, m_vEye, Eye);
public:
	cCamera(void);
	~cCamera(void);

	virtual void Setup() override;
	virtual void Update() override;
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetTarget(D3DXVECTOR3* pTarget);
	void SetPlayer(cUnit* pPlayer);
};

