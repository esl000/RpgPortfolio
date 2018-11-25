#include "StdAfx.h"
#include "cObject.h"


cObject::cObject(void)
	: m_nRefCount(1)
{
	g_pObjectManager->AddObject(this);
}


cObject::~cObject(void)
{
	assert(m_nRefCount == 0 && "이러지 말자..");
	g_pObjectManager->RemoveObject(this);
}

void cObject::AddRef()
{
	++m_nRefCount;
}

void cObject::Release()
{
	--m_nRefCount;
	if(m_nRefCount == 0)
		delete this;
}

void cObject::AutoRelease()
{
	g_pObjectManager->AddAutoReleasePool(this);
}

