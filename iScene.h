#pragma once
class iScene : public cObject
{
public:
	iScene();
	virtual ~iScene();

	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
};

