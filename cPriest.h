#pragma once
class cPriest : public cUnit
{
public:
	cPriest();
	virtual ~cPriest();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

