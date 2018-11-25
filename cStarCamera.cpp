#include "stdafx.h"
#include "cStarCamera.h"


cStarCamera::cStarCamera()
	: eMouseScroll(MOUSE_NONE)
	, m_vCameraPos(40 * CHUNK_SIZE + CHUNK_SIZE / 2, 0, -28 * CHUNK_SIZE + CHUNK_SIZE / 2)
{
	GetClientRect(g_hWnd, &winSize);
	WINDSIZE_X = winSize.right;
	WINDSIZE_Y = winSize.bottom;
}


cStarCamera::~cStarCamera()
{
}

void cStarCamera::Update()
{

	eMouseScroll = MOUSE_NONE;
	if (g_ptMouse.x <= 100)
	{
		int a = 0;
		eMouseScroll = (MOUSESCROLL)(eMouseScroll | MOUSE_LEFT);
	}
	if (g_ptMouse.x >= WINDSIZE_X - 100)
	{
		eMouseScroll = (MOUSESCROLL)(eMouseScroll | MOUSE_RIGHT); 
	}
	if (g_ptMouse.y >= WINDSIZE_Y - 100)
	{
		eMouseScroll = (MOUSESCROLL)(eMouseScroll | MOUSE_BOTTOM);
	}
	if (g_ptMouse.y <= 100)
	{
		eMouseScroll = (MOUSESCROLL)(eMouseScroll | MOUSE_TOP);
	}
	//else
	//{
	//	eMouseScroll = MOUSE_NONE;
	//}

	float cameraSpeed = 5.f;


	if (eMouseScroll & MOUSE_LEFT)
	{
		m_vCameraPos.x = m_vCameraPos.x + cameraSpeed;
	}
	if (eMouseScroll & MOUSE_TOP)
	{
		m_vCameraPos.z = m_vCameraPos.z - cameraSpeed;
	}
	if (eMouseScroll & MOUSE_RIGHT)
	{
		m_vCameraPos.x = m_vCameraPos.x - cameraSpeed;
	}
	if (eMouseScroll & MOUSE_BOTTOM)
	{
		m_vCameraPos.z = m_vCameraPos.z + cameraSpeed;
	}
	//switch (eMouseScroll)
	//{
	//case MOUSE_NONE:
	//	break;
	//case MOUSE_LEFT:
	//	vCameraPos.x = vCameraPos.x + cameraSpeed;
	//	break;
	//case MOUSE_TOP:
	//	vCameraPos.z = vCameraPos.z - cameraSpeed;
	//	break;
	//case MOUSE_RIGHT:
	//	vCameraPos.x = vCameraPos.x - cameraSpeed;
	//	break;
	//case MOUSE_BOTTOM:
	//	vCameraPos.z = vCameraPos.z + cameraSpeed;
	//	break;
	//default:
	//	break;
	//}
}

D3DXVECTOR3* cStarCamera::GetPos()
{
	return &m_vCameraPos;
}
