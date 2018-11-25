#include "stdafx.h"
#include "cNpcAI.h"

cNpcAI::cNpcAI()
{
}


cNpcAI::~cNpcAI()
{
}

void cNpcAI::Start()
{
	if (m_pOwner)
		m_pOwnerMesh = m_pOwner->GetMesh();

}

void cNpcAI::Update()
{


}
