#include "stdafx.h"
#include "cMainGame.h"
#include "cGameScene.h"
#include "cMenuScene.h"
#include "cLoadingScene.h"
#include "cMapToolScene.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
	g_pSceneManager->Destroy();
	g_pSoundManager->release();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}


void cMainGame::Setup()
{
	g_pSoundManager->init();
	AddSound();

	//cGameScene* pGame = new cGameScene;
	//pGame->Setup();
	//g_pSceneManager->AddScene(string("game"), pGame);
	//g_pSceneManager->ChangeScene(string("game"));

	cMenuScene* pMenu = new cMenuScene;
	pMenu->Setup();
	g_pSceneManager->AddScene(string("Menu"), pMenu);
	g_pSceneManager->ChangeScene(string("Menu"));

	//cLoadingScene* pLoad = new cLoadingScene;
	//pLoad->Setup();
	//g_pSceneManager->AddScene(string("loading"), pLoad);
	//g_pSceneManager->ChangeScene(string("loading"));

	//cMapToolScene* pMap = new cMapToolScene;
	//pMap->Setup();
	//g_pSceneManager->AddScene(string("map"), pMap);
	//g_pSceneManager->ChangeScene(string("map"));


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	//SetupVertexFog(D3DCOLOR_XRGB(180, 180, 180), D3DFOG_LINEAR, true, 0.5f);
}

void cMainGame::Update()
{
	if (g_pSceneManager->GetCurrentScene())
		g_pSceneManager->GetCurrentScene()->Update();

	g_pSoundManager->update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	if (g_pSceneManager->GetCurrentScene())
		g_pSceneManager->GetCurrentScene()->Render();

	g_pTimeManager->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (g_pSceneManager->GetCurrentScene())
		g_pSceneManager->GetCurrentScene()->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::AddSound()
{
	//bgm
	g_pSoundManager->addSound("MenuSceneBackGround", "sound/BackGround/MenuSceneBackGround.mp3", true, true);
	g_pSoundManager->addSound("LodingSceneBackGround", "sound/BackGround/LodingSceneBackGround.mp3", true, true);
	g_pSoundManager->addSound("OrgrimarBackGround", "sound/BackGround/OrgrimarBackGround.mp3", true, true);
	g_pSoundManager->addSound("Durota", "sound/BackGround/Durota.mp3", true, true);

	//UI
	g_pSoundManager->addSound("BagClose", "sound/UI/BagClose.ogg", false, false);
	g_pSoundManager->addSound("BagOpen", "sound/UI/BagOpen.ogg", false, false);
	g_pSoundManager->addSound("ButtonClick", "sound/UI/ButtonClick.ogg", false, false);
	g_pSoundManager->addSound("CharacterWindowClose", "sound/UI/CharacterWindowClose.ogg", false, false);
	g_pSoundManager->addSound("CharacterWindowOpen", "sound/UI/CharacterWindowOpen.ogg", false, false);
	g_pSoundManager->addSound("ItemClick", "sound/UI/ItemClick.ogg", false, false);
	g_pSoundManager->addSound("LevelUp", "sound/UI/LevelUp.ogg", false, false);
	g_pSoundManager->addSound("PetCall", "sound/UI/PetCall.ogg", false, false);
	g_pSoundManager->addSound("PetDown", "sound/UI/PetDown.ogg", false, false);
	g_pSoundManager->addSound("QuestComplete", "sound/UI/QuestComplete.ogg", false, false);
	g_pSoundManager->addSound("QuestTake", "sound/UI/QuestTake.ogg", false, false);
	g_pSoundManager->addSound("QuestWindowClose", "sound/UI/QuestWindowClose.ogg", false, false);
	g_pSoundManager->addSound("QuestWindowOpen", "sound/UI/QuestWindowOpen.ogg", false, false);

	//creture
	g_pSoundManager->addSound("Sylvanas", "sound/Creture/Sylvanas.wav", false, false);
	g_pSoundManager->addSound("Thrall", "sound/Creture/Thrall.wav", false, false);
	g_pSoundManager->addSound("Voljin", "sound/Creture/Voljin.wav", false, false);

	//character
	g_pSoundManager->addSound("OrcAttack", "sound/Character/OrcAttack.ogg", false, false);
	g_pSoundManager->addSound("OrcDamage", "sound/Character/OrcDamage.ogg", false, false);
	g_pSoundManager->addSound("OrcTargetHit", "sound/Character/OrcTargetHit.ogg", false, false);
	g_pSoundManager->addSound("OrcWalk", "sound/Character/OrcWalk.ogg", false, false);
	g_pSoundManager->addSound("OrcWeaponSwings", "sound/Character/OrcWeaponSwings.ogg", false, false);

	//skill
	g_pSoundManager->addSound("BladeStorm", "sound/Skill/BladeStorm.ogg", false, false);
	g_pSoundManager->addSound("RendTarget", "sound/Skill/RendTarget.ogg", false, false);
	g_pSoundManager->addSound("ShadowStrike", "sound/Skill/ShadowStrike.ogg", false, false);
	g_pSoundManager->addSound("Strike", "sound/Skill/Strike.ogg", false, false);
	g_pSoundManager->addSound("WhirlWind", "sound/Skill/WhirlWind.ogg", false, false);
	g_pSoundManager->addSound("FallingDamage", "sound/Skill/FallingDamage.ogg", false, false);
	g_pSoundManager->addSound("ThunderClap", "sound/Skill/ThunderClap.ogg", false, false);
	g_pSoundManager->addSound("ShockWave", "sound/Skill/ShockWave.ogg", false, false);

}

void cMainGame::SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density)
{
	float Start = 300.f,    // Linear fog distances
		End = 500.f;

	// Enable fog blending.
	g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// Set the fog color.
	g_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, Color);

	// Set fog parameters.
	if (D3DFOG_LINEAR == Mode)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		g_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&Start));
		g_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&End));
	}
	else
	{
		g_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		g_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)(&Density));
	}

	// Enable range-based fog if desired (only supported for
	//   vertex fog). For this example, it is assumed that UseRange
	//   is set to a nonzero value only if the driver exposes the 
	//   D3DPRASTERCAPS_FOGRANGE capability.
	// Note: This is slightly more performance intensive
	//   than non-range-based fog.
	if (UseRange)
		g_pD3DDevice->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);
}

