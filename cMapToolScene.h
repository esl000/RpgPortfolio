#pragma once
#include "iScene.h"
#include "cCamera.h"
#include "cLight.h"
#include "cGrid.h"
#include "cViewPos.h"

class cMapToolScene : public iScene
	, public iLoadDelegate
{
private:
	vector<cEntity*> m_vecEntity;
	cEntity* m_pCurrentEntity;
	int m_nIndex;
	cEntity::eEntityType m_eCurrentType;
	cLight* m_pLight;
	cCamera* m_pCamera;
	cGrid* m_pGrid;
	cViewPos* m_pViewPos;

public:
	cMapToolScene();
	virtual ~cMapToolScene();

	
	void Load();
	void Save();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	virtual void OnLoadDelegate(ST_CHUNK_INDEX stIndex);
};

