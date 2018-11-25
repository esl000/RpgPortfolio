#include "stdafx.h"
#include "cUIMainController.h"

#include "cUIObject.h"
#include "cUIImageView.h"
#include "cUIStatus.h"
#include "cUIMiniMap.h"

cUIMainController::cUIMainController()
	: m_pSprite(NULL)
	, m_pRootUI(NULL)
	, m_pUIImageView(NULL)
	, m_pUIButton(NULL)
	, m_pUIStatus(NULL)
	, m_pcUIMiniMap(NULL)
	, m_bInvenTory(false)
	, m_bCheck(false)
	, m_fGauge(0.f)
	, m_nData(0)
	, m_iState(0)
{
}


cUIMainController::~cUIMainController()
{
}
