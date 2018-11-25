#pragma once
class cViewPos : public cUnit
{
public:
	cViewPos();
	~cViewPos();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	D3DXVECTOR3* GetPos();
};

