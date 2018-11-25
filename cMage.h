#pragma once
class cMage : public cUnit
{
public:
	cMage();
	virtual ~cMage();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

