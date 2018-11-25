#include "StdAfx.h"
#include "cCamera.h"


cCamera::cCamera(void)
	: m_vEye(0.f, 0.f, -5.f)
	, m_vLookAt(0.f, 0.f, 0.f)
	, m_vUp(0.f, 1.f, 0.f)
	, m_pTarget(NULL)
	, m_isLButtonDown(false)
	, m_fRotAngleX(0.f)
	, m_fRotAngleY(0.f)
	, m_fDistance(15.f)
	, m_fCurrentDistanse(15.f)
	, m_pPlayer(NULL)
{
}


cCamera::~cCamera(void)
{
}

void cCamera::Setup()
{
#ifdef MAPTOOL
	m_vPosition = *m_pTarget;
#else
#endif

	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 10000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update()
{
	//if (m_pPlayer)
	//{
	//	float fAngle = atan2f(m_pPlayer->GetDirection().x, m_pPlayer->GetDirection().z);
	//	if (fabs(m_fRotAngleY - fAngle) > 0.005f)
	//	{
	//		m_fRotAngleY += 2.f * (fAngle - m_fRotAngleY) * g_pTimeManager->GetElapsedTime();
	//	}
	//	else
	//	{
	//		m_fRotAngleY = fAngle;
	//	}
	//}

	 //카메라 회전 및 큐브의 위치에 따른 뷰 매트릭스 갱신
	D3DXMATRIXA16 matRotX, matRotY;
	D3DXMatrixRotationX(&matRotX, m_fRotAngleX);
	D3DXMatrixRotationY(&matRotY, m_fRotAngleY);

	D3DXMATRIXA16 matCamRot = matRotX * matRotY;

	D3DXVECTOR3 vPrevEye = m_vEye;

	m_vEye = D3DXVECTOR3(0.f, 0.f, -m_fCurrentDistanse);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matCamRot);
	D3DXVECTOR3 vDest;

	if (m_pTarget)
	{
		D3DXVECTOR3 vTarget = (*m_pTarget);
		vTarget.y += 1.5f;
		m_vEye = m_vEye + vTarget;

		D3DXVECTOR3 vEye = m_vEye;
		vEye.y = vPrevEye.y;

		if (g_pTileManager->GetHeight(vDest, vEye))
		{
			if (vDest.y + 1.0f > m_vEye.y)
			{
				m_vEye.y = vDest.y + 1.0f;
			}
		}

		m_vPosition = m_vEye;
		m_vLookAt = vTarget;
	}
	else
	{
		m_vLookAt = D3DXVECTOR3(0.f, 0.f, 0.f);
	}

	if (g_pIntersectManager->IntersectEntitys(ST_SPHERE(m_vEye, 1.f), vDest))
	{
		if (m_fCurrentDistanse > 0)
		{
			m_fCurrentDistanse -= 0.3f;
			if (m_fCurrentDistanse < 0.f)
				m_fCurrentDistanse = 0.f;
		}
	}
	else
	{
		if (m_fCurrentDistanse < m_fDistance)
		{
			float fVirtualDistanse = m_fCurrentDistanse + 0.3f;
			D3DXVECTOR3 vEye = D3DXVECTOR3(0.f, 0.f, -fVirtualDistanse);
			D3DXVec3TransformCoord(&vEye, &vEye, &matCamRot);
			

			if (!g_pIntersectManager->IntersectEntitys(ST_SPHERE(vEye, 1.f), vDest))
			{
				m_fCurrentDistanse += 0.3f;
				m_vEye = vEye;

				D3DXVECTOR3 vTarget = (*m_pTarget);
				vTarget.y += 1.5f;

				m_vEye = m_vEye + vTarget;

				D3DXVECTOR3 vTempEye = m_vEye;
				vTempEye.y = vPrevEye.y;

				if (g_pTileManager->GetHeight(vDest, vTempEye))
				{
					if (vDest.y + 1.0f > m_vEye.y)
					{
						m_vEye.y = vDest.y + 1.0f;
					}
				}

				m_vPosition = m_vEye;
				m_vLookAt = vTarget;
			}
		}
		else
		{
			m_fCurrentDistanse = m_fDistance;
		}
	}


	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
	
}

void cCamera::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			if (!g_pPicking->GetUse(cPicking::E_LEFTCLICK))
				break;
			m_isLButtonDown = true;
			m_ptPrev.x = LOWORD(lParam);
			m_ptPrev.y = HIWORD(lParam);
		}
		break;
	case WM_LBUTTONUP:
		{
			m_isLButtonDown = false;
		}
		break;
	case WM_MOUSEMOVE:
		{
			if (!m_isLButtonDown)
				break;

			POINT ptCurr;
			ptCurr.x = LOWORD(lParam);
			ptCurr.y = HIWORD(lParam);

			int nDeltaX = ptCurr.x - m_ptPrev.x;
			int nDeltaY = ptCurr.y - m_ptPrev.y;

			//float fPrevAnglex = m_fRotAngleX;

			m_fRotAngleY += (nDeltaX * 0.005f);
			m_fRotAngleX += (nDeltaY * 0.005f);
			if (m_fRotAngleX < -D3DX_PI / 2.0f + 0.0001f)
				m_fRotAngleX = -D3DX_PI / 2.0f + 0.0001f;
			if (m_fRotAngleX > D3DX_PI / 2.0f - 0.0001f)
				m_fRotAngleX = D3DX_PI / 2.0f - 0.0001f;

			m_ptPrev = ptCurr;
		}
		break;
	case WM_MOUSEWHEEL:
		{
			if (m_fDistance - (GET_WHEEL_DELTA_WPARAM(wParam) * 0.3f) <= 0.f)
				break;
			if (fabs(m_fDistance - m_fCurrentDistanse) < 0.001f)
			{
				m_fDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) * 0.3f);
				m_fCurrentDistanse = m_fDistance;
			}
			else
			{
				m_fDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) * 0.3f);
			}
		}
		break;
	}
}

void cCamera::SetTarget( D3DXVECTOR3* pTarget )
{
	m_pTarget = pTarget;
}

void cCamera::SetPlayer(cUnit* pPlayer)
{
	m_pPlayer = pPlayer;
}
