#pragma once

class cWarrior : public cUnit
{
public:
	cWarrior();
	virtual ~cWarrior();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

