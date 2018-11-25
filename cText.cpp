#include "stdafx.h"
#include "cText.h"
#include "cBillBoarding.h"
//#include <atlconv.h>


cText::cText()
	: m_nLength(0)
{
}


cText::~cText()
{
}

void cText::Setup(std::wstring sStr)
{
	//WCHAR szWchar[1024];
	//char* szChar;
	//szChar = (LPSTR)(LPCSTR)sStr.c_str();
	//szWchar = new WCHAR[strlen(szChar) + 1];
	//swprintf_s(szWchar, sStr.length(), L"%s", (LPSTR)(LPCSTR)sStr.c_str());

	//SAFE_DELETE_ARRAY(szChar);


	m_nLength = sStr.length();

	// Get a handle to a device context
	HDC hdc = CreateCompatibleDC(NULL);

	// Describe the font we want.

	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));

	lf.lfHeight = 2;    // in logical units
	lf.lfWidth = 1;    // in logical units
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = 500;   // boldness, range 0(light) - 1000(bold)
	lf.lfItalic = FALSE;
	lf.lfUnderline = FALSE;
	lf.lfStrikeOut = FALSE;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = 0;
	lf.lfPitchAndFamily = 0;

	strcpy(lf.lfFaceName, "±¼¸²Ã¼"); // font style

	// Create the font and select it with the device context.
	HFONT hFont = CreateFontIndirect(&lf);
	HFONT hFontOld = (HFONT)SelectObject(hdc, hFont);

	LPD3DXMESH pMesh;
	// Create the text mesh based on the selected font in the HDC.
	D3DXCreateTextW(g_pD3DDevice,
		hdc,
		sStr.c_str(),
		0.001f,
		0.001f,
		&pMesh,
		NULL,
		NULL);

	pMesh->CloneMeshFVF(pMesh->GetOptions(),
		ST_PC_VERTEX::FVF,
		g_pD3DDevice,
		&m_pText);

	ST_PN_VERTEX* pV1;
	ST_PC_VERTEX* pV2;

	pMesh->LockVertexBuffer(0, (LPVOID*)&pV1);
	m_pText->LockVertexBuffer(0, (LPVOID*)&pV2);

	for (int i = 0; i < pMesh->GetNumVertices(); ++i)
	{
		pV2[i].p = pV1[i].p;
		pV2[i].c = D3DCOLOR_XRGB(0, 255, 0);
	}

	m_pText->UnlockVertexBuffer();
	pMesh->UnlockVertexBuffer();

	SAFE_RELEASE(pMesh);

	//(szWchar);

	// Restore the old font and free the acquired HDC.    
	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);
}

void cText::Update()
{
	D3DXVECTOR3 vPos = m_vPosition;
	vPos.y += 2.5;
	cBillBoarding::GetBillBoardingMatrix(&m_matBillBoard, vPos);
	
	D3DXMATRIXA16 matT;
	float x = -0.4f * m_nLength / 2;
	D3DXMatrixTranslation(&matT, x, 0, 0);
	m_matBillBoard = matT * m_matBillBoard;
}

void cText::Render()
{
	D3DXMATRIXA16 matS, matWorld;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);

	matWorld = matS * m_matBillBoard;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pText->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}
