#pragma once


class cStarCamera 
{
private:

	enum MOUSESCROLL
	{
		MOUSE_NONE = 0,
		MOUSE_LEFT = 1 << 0,
		MOUSE_TOP = 1 << 1,
		MOUSE_RIGHT = 1 << 2,
		MOUSE_BOTTOM = 1 << 3
	};

	RECT							winSize;
	int							WINDSIZE_Y;
	int							WINDSIZE_X;
	MOUSESCROLL					eMouseScroll;
	D3DXVECTOR3					m_vCameraPos;
	//SYNTHESIZE(cGameObject*, m_pOwner, Owner);


public:

	void Update();

	D3DXVECTOR3* GetPos();

	cStarCamera();
	~cStarCamera();
};

