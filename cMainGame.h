#pragma once

class cMainGame
{
private:

public:
	 void Setup();
	 void Update();
	 void Render();
	 void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	 void AddSound();

	 void SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density);

	cMainGame();
	~cMainGame();
};

