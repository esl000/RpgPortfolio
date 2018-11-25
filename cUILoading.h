#pragma once

#include "cUIObject.h"
#include "cUIButton.h"


class cUIImageView;
class cGameScene;

class cUILoading
	: public cUIObject
{
private:
	cUIImageView*			m_pUILoadingGauge;
	cGameScene*				m_pGameScene;
	DWORD					m_dwThread[2];
	HANDLE					m_hThread[2];
	volatile  bool			m_bVolLoading, m_bVolSetup;
	float					m_fLoading;
	unsigned long			m_ulStackSize;

public:
	cUILoading(void);
	virtual ~cUILoading(void);

public:
	virtual void Setup(void);
	virtual void Update(void);
	virtual void Render(void);
public:
	static void ThreadSetup(LPVOID lpVod);
};

