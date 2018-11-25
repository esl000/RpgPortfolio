#pragma once

#include "cUIObject.h"
#include "cUIButton.h"

class cUIObject;
class cUIImageView;
class cUIButton;

class cUIMainView 
	: public cUIObject
	, public iUIButtonDelegate
{
public:
	cUIMainView(void);
	virtual ~cUIMainView(void);

public:
	virtual void Setup(void);
	virtual void Update(void);
	virtual void Render(void);
	virtual void OnClick(cUIButton* pButton);
};

