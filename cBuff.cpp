#include "stdafx.h"
#include "cBuff.h"
#include "cUnit.h"


cBuff::cBuff()
	: m_pOwner(NULL)
	, m_pDelegate(NULL)
	, m_fPassedTime(0.f)
{
}


cBuff::~cBuff()
{
}
