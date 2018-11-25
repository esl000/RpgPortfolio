#pragma once

#include "iScene.h"
#include "cMap.h"

class cGrid;
class cCamera;
class cLight;
class iMap;
class cUnitPlayer;
class cUnitMonster;
class cUIInterface;
class cUIIQuest;
class cUIInterface;
class cUIGaugeBar;

class cGameScene : public iScene
	, public iLoadDelegate
{
protected:
	cGrid* m_pGrid;
	cCamera* m_pCamera;
	cLight* m_pLight;
	iMap* m_pMap;
	cUnitPlayer* m_pPlayer;
	cUnitMonster* m_pMonster;
	cUIInterface* m_pInterface;
	cUIGaugeBar* m_pGaugeBar;
	cUnitCustomNpc* m_pNpcSylva;
	cUnitCustomNpc* m_pNpcThrall;
	cUIIQuest* m_pUiQuest;

	bool m_bSetupComplete;
	int UiTestCount;
public:
	cGameScene();
	virtual ~cGameScene();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	virtual void OnLoadDelegate(ST_CHUNK_INDEX stIndex);
};

