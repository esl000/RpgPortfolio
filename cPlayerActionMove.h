#pragma once
class cPlayerActionMove : public iUnitAction
{
public:
	cPlayerActionMove();
	virtual ~cPlayerActionMove();

	virtual void Start() override;
	virtual void Update() override;
};

