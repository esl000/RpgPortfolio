#include "stdafx.h"
#include "cBillBoarding.h"

cBillBoarding::cBillBoarding()
{
}


cBillBoarding::~cBillBoarding()
{
}


void cBillBoarding::GetBillBoardingMatrix(OUT D3DXMATRIXA16* pMat, D3DXVECTOR3 vPos)
{
	D3DXMatrixTranslation(pMat, vPos.x, vPos.y, vPos.z);

	D3DXMATRIXA16 matView, matInvView;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matInvView, 0, &matView);

	pMat->_11 = matInvView._11; pMat->_21 = matInvView._21; pMat->_31 = matInvView._31;
	pMat->_12 = matInvView._12; pMat->_22 = matInvView._22; pMat->_32 = matInvView._32;
	pMat->_13 = matInvView._13; pMat->_23 = matInvView._23; pMat->_33 = matInvView._33;

	return;
}
