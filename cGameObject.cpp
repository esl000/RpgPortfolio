#include "StdAfx.h"
#include "cGameObject.h"


cGameObject::cGameObject(void)
	: m_vPosition(0, 0, 0)
	, m_vDirection(0, 0, 0)
	, m_pAction(NULL)
{
}


cGameObject::~cGameObject(void)
{
	SAFE_RELEASE(m_pAction);
}

void cGameObject::Setup()
{

}

void cGameObject::Update()
{
	if (m_pAction)
	{
		m_pAction->Update();
	}
}

void cGameObject::Render()
{

}
