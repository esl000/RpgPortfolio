#pragma once

#include "cButton.h"
#include "cMessageBox.h"

class cMessageQuest : public cMessageBox
{
protected:
	enum eButtonType
	{
		E_EXIT = 0,
		E_OK = 1,
		E_NO = 2
	};
public:
	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void onButtonSelect(cButton* pButton);
	cMessageQuest();
	~cMessageQuest();
};

