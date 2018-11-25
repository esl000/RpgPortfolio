#include "stdafx.h"
#include "cUnitCustomNpc.h"
#include "cNpcCourse.h"
#include "cUIIQuest.h"
#include "cUnitPlayer.h"
#include "cUINpcWindow.h"


cUnitCustomNpc::cUnitCustomNpc()
	: m_pQuest(NULL)
	, m_sLore("")
	, m_sQuest("")
	, m_sFolder("")
	, m_sFile("")
	, m_sMoveNpc("")
	, m_nQuestIndex(0)
{
	m_eEntityType = E_UNIT;
	m_eUnitType = E_NPC;
}


cUnitCustomNpc::~cUnitCustomNpc()
{
	SAFE_DELETE(m_pMesh);
}

void cUnitCustomNpc::Setup()
{
	
	m_pMesh = new cSkinnedMesh(m_sFolder.c_str(), m_sFile.c_str());
	m_pQuest = g_pQuestDatabase->GetQuest(m_sQuest);
	m_stFrustumSphere = m_pMesh->GetBoundingSphere();

	m_pMesh->SetPosition(m_vPosition);
	m_pMesh->SetDirection(m_vDirection);
	m_stFrustumSphere = m_pMesh->GetBoundingSphere();

	if (m_sMoveNpc == string("move"))
	{
		cNpcCourse* course = new cNpcCourse;
		course->Load();
		m_vecVMoveCourse = course->GetCourse();
		SAFE_DELETE(course);
	}
	//OpenQuest();
}

void cUnitCustomNpc::Update()
{
	if (m_pBuff)
		m_pBuff->Update();
	if (m_pUnitAction)
		m_pUnitAction->Update();

	if (m_pMesh)
	{
		m_pMesh->SetPosition(m_vPosition);
		m_pMesh->SetDirection(m_vDirection);
		m_stFrustumSphere = m_pMesh->GetBoundingSphere();
	}
}

void cUnitCustomNpc::Render()
{
	if (m_pMesh)
		m_pMesh->UpdateAndRender();

	SphereRender(m_stFrustumSphere);
}

void cUnitCustomNpc::OnUnitActionFinish(iUnitAction* pAction)
{
	SAFE_RELEASE(pAction);
	m_pUnitAction = NULL;
}

void cUnitCustomNpc::OpenMessage()
{
	cUINpcWindow* pWindow = new cUINpcWindow;
	pWindow->SetNpc(this);
	pWindow->Setup();
	
	g_pUImanager->RegisterUI(pWindow);
}
