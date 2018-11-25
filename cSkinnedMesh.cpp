#include "StdAfx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"


cSkinnedMesh::cSkinnedMesh(const char* szFolder, const char* szFilename)
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
	, m_vPosition(0, 0, 0)
	, m_vDirection(0, 0, -1)
	, m_dCurrentAni(0)
	, m_dPeriod(0)
	, m_dPosition(0)
	, m_vOrgSphere(0, 0, 0)
	, m_stSphere()
	, m_fBlendingTime(0.1f)
	, m_fPassedBlendingTime(0.f)
	, m_isBlending(false)
	, m_isTurn(false)
	, m_isStand(true)
	, m_nReverse(0)
	, m_fReverseStartPosition(0)
	, m_fReverseEndPosition(0)
	, m_bIsRotation(false)
	, m_fSleepPosition(0.0f)
{
	cSkinnedMesh* pSkinnedMesh =  g_pSkinnedMeshManager->GetSkinnedMesh(szFolder, szFilename);

	m_pRootFrame = pSkinnedMesh->m_pRootFrame;
	m_dwWorkingPaletteSize = pSkinnedMesh->m_dwWorkingPaletteSize;
	m_pmWorkingPalette = pSkinnedMesh->m_pmWorkingPalette;
	m_pEffect = pSkinnedMesh->m_pEffect;
	m_vOrgSphere = pSkinnedMesh->m_vOrgSphere;
	m_stSphere = pSkinnedMesh->m_stSphere;

	if (pSkinnedMesh->m_pAnimController)
	{
		pSkinnedMesh->m_pAnimController->CloneAnimationController(
			pSkinnedMesh->m_pAnimController->GetMaxNumAnimationOutputs(),
			pSkinnedMesh->m_pAnimController->GetMaxNumAnimationSets(),
			pSkinnedMesh->m_pAnimController->GetMaxNumTracks(),
			pSkinnedMesh->m_pAnimController->GetMaxNumEvents(),
			&m_pAnimController);
	}
}

cSkinnedMesh::cSkinnedMesh()
	: m_pRootFrame(NULL)
	, m_pAnimController(NULL)
	, m_dwWorkingPaletteSize(0)
	, m_pmWorkingPalette(NULL)
	, m_pEffect(NULL)
	, m_dCurrentAni(0)
{
}

cSkinnedMesh::~cSkinnedMesh(void)
{
	SAFE_RELEASE(m_pAnimController);	
}

void cSkinnedMesh::Load(const  char* szDirectory, const char* szFilename)
{
	m_pEffect = LoadEffect("MultiAnimation.hpp");
							
	int nPaletteSize = 0;
	m_pEffect->GetInt("MATRIX_PALETTE_SIZE", &nPaletteSize);

	cAllocateHierarchy ah;
	ah.SetDirectory(szDirectory);
	ah.SetDefaultPaletteSize(nPaletteSize);
	
	std::string sFullPath(szDirectory);
	sFullPath += std::string("/") + std::string(szFilename);

	HRESULT h = D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&ah,
		NULL,
		(LPD3DXFRAME*)&m_pRootFrame,
		&m_pAnimController);

	if (h == D3DERR_INVALIDCALL)
	{
		int a = 0;
	}

	if (h == E_OUTOFMEMORY)
	{
		int a = 0;
	}

	CreateBoundingBox(m_pRootFrame);

	if( m_pmWorkingPalette )
		delete [] m_pmWorkingPalette;

	m_dwWorkingPaletteSize = ah.GetMaxPaletteSize();
	m_pmWorkingPalette = new D3DXMATRIX[ m_dwWorkingPaletteSize];
	if( m_pmWorkingPalette == NULL )
	{
		m_dwWorkingPaletteSize = 0;
	}

	if(m_pRootFrame)
		SetupBoneMatrixPtrs(m_pRootFrame);
}

void cSkinnedMesh::UpdateAndRender(D3DXMATRIXA16* matParent)
{
	AnimationBlend();
	if(m_pAnimController)
	{

		D3DXTRACK_DESC	stDesc;
		LPD3DXANIMATIONSET ani;
		m_pAnimController->GetTrackAnimationSet(0, &ani);
		m_pAnimController->GetTrackDesc(0, &stDesc);

		m_dPeriod = ani->GetPeriod();
		m_dPosition = stDesc.Position;

		if (m_isStand && m_dCurrentAni == 0)
		{
			if (stDesc.Position > ani->GetPeriod() - 0.02f)
				m_pAnimController->SetTrackSpeed(0, -1.f);
			if (stDesc.Position < 0.04f)
				m_pAnimController->SetTrackSpeed(0, 1.f);
		}
		else if (m_isStand && m_dCurrentAni == 10)
		{		
			if (stDesc.Position > 0.20f)
				m_pAnimController->SetTrackSpeed(0, -0.1f);
			if (stDesc.Position < 0.01f)
				m_pAnimController->SetTrackSpeed(0, 0.1f);
		}
		
		if (m_isTurn)
		{
			double dPos, dPeriod;
			dPos = m_dPosition;
			//cout << "Pos : " << dPos << endl;
			dPeriod = m_dPeriod;
			//cout << "Period : " << dPeriod << endl;
			dPos = dPos - dPeriod * (int)(dPos / dPeriod);
			//cout << "fixPos : " << dPos << endl;
			if (dPos / dPeriod > m_fReverseEndPosition - 0.01f)
			{
				m_pAnimController->SetTrackPosition(0, m_fReverseStartPosition);
				++m_nReverse;
				m_nReverse %= 3;
			}
		}

		m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
	}

	if (m_pRootFrame)
	{
		D3DXMATRIXA16 matP, matR, matT, mat;
		float fAngle = atan2f(m_vDirection.x, m_vDirection.z) - D3DX_PI;

		fAngle -= 2 * m_nReverse * D3DX_PI / 3.f;

		D3DXMatrixRotationY(&matR, fAngle);

		D3DXMatrixIdentity(&matP);

		if (matParent)
		{
			matP = *matParent;
		}
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

		mat = matP * matR * matT;

		m_stSphere.vCenter = m_vOrgSphere + m_vPosition;

		Update(m_pRootFrame, &mat);
		Render(m_pRootFrame);
	}	
}

void cSkinnedMesh::Render(ST_BONE* pBone /*= NULL*/)
{
	assert(pBone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	if(pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;

		// get bone combinations
		LPD3DXBONECOMBINATION pBoneCombos = 
			( LPD3DXBONECOMBINATION )( pBoneMesh->pBufBoneCombos->GetBufferPointer() );

		D3DXMATRIXA16 matViewProj, matView, matProj;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		matViewProj = matView * matProj;

		D3DXMATRIXA16 mView, mInvView;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &mView);
		D3DXMatrixInverse(&mInvView, 0, &mView);
		D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&vEye, &vEye, &mInvView);

		// for each palette
		for( DWORD dwAttrib = 0; dwAttrib < pBoneMesh->dwNumAttrGroups; ++ dwAttrib )
		{
			// set each transform into the palette
			for( DWORD dwPalEntry = 0; dwPalEntry < pBoneMesh->dwNumPaletteEntries; ++ dwPalEntry )
			{
				DWORD dwMatrixIndex = pBoneCombos[ dwAttrib ].BoneId[ dwPalEntry ];
				if( dwMatrixIndex != UINT_MAX )
				{
					m_pmWorkingPalette[ dwPalEntry ] = 
						pBoneMesh->pBoneOffsetMatrices[ dwMatrixIndex ] * 
						(*pBoneMesh->ppBoneMatrixPtrs[ dwMatrixIndex ]);
				}
			}

			// set the matrix palette into the effect
			m_pEffect->SetMatrixArray( "amPalette",
				m_pmWorkingPalette,
				pBoneMesh->dwNumPaletteEntries );

			m_pEffect->SetMatrix("g_mViewProj", &matViewProj);
			m_pEffect->SetVector("vLightDiffuse", &D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );
			m_pEffect->SetVector("vWorldLightPos", &D3DXVECTOR4( 500.0f, 500.0f, 500.0f, 1.0f ) );
			m_pEffect->SetVector("vWorldCameraPos", &D3DXVECTOR4( vEye, 1.0f ) );
			m_pEffect->SetVector("vMaterialAmbient", &D3DXVECTOR4( 0.53f, 0.53f, 0.53f, 0.53f ) );
			m_pEffect->SetVector("vMaterialDiffuse", &D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f ) );

			// we're pretty much ignoring the materials we got from the x-file; just set
			// the texture here
			if (pBoneMesh->vecTexture.size() > 0)
			{
				m_pEffect->SetTexture("g_txScene", pBoneMesh->vecTexture[pBoneCombos[dwAttrib].AttribId]);
			}

			// set the current number of bones; this tells the effect which shader to use
			m_pEffect->SetInt( "CurNumBones", pBoneMesh->dwMaxNumFaceInfls - 1 );

			// set the technique we use to draw
			m_pEffect->SetTechnique( "Skinning20" );

			UINT uiPasses, uiPass;

			// run through each pass and draw
			m_pEffect->Begin( & uiPasses, 0 );
			for( uiPass = 0; uiPass < uiPasses; ++ uiPass )
			{
				m_pEffect->BeginPass( uiPass );
				pBoneMesh->pWorkingMesh->DrawSubset( dwAttrib );
				m_pEffect->EndPass();
			}
			m_pEffect->End();
		}
	}

	if (pBone->pEquips)
	{
		D3DXMATRIXA16 mat, matR;
		D3DXMatrixRotationY(&matR, -D3DX_PI / 2.0f);
		if (pBone->pEquips->GetIsRotation())
		{
			mat = matR * pBone->CombinedTransformationMatrix;
		}
		else
		{
			mat = pBone->CombinedTransformationMatrix;
		}
		pBone->pEquips->UpdateAndRender(&mat);
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if(pBone->pFrameSibling)
	{
		Render((ST_BONE*)pBone->pFrameSibling);
	}

	if(pBone->pFrameFirstChild)
	{
		Render((ST_BONE*)pBone->pFrameFirstChild);
	}
}

LPD3DXEFFECT cSkinnedMesh::LoadEffect( char* szFilename )
{
	LPD3DXEFFECT pEffect = NULL;

	D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL,                          NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	g_pD3DDevice->GetDeviceCaps( & caps );
	if( caps.VertexShaderVersion > D3DVS_VERSION( 1, 1 ) )
		pmac = mac;

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	ID3DXBuffer* pBuffer = NULL;
	if(FAILED(D3DXCreateEffectFromFile( g_pD3DDevice,
		szFilename,
		pmac,
		NULL,
		dwShaderFlags,
		NULL,
		&pEffect,
		&pBuffer )))
	{
		// if creation fails, and debug information has been returned, output debug info
		if (pBuffer)
		{
			OutputDebugStringA((char*)pBuffer->GetBufferPointer());
			SAFE_RELEASE(pBuffer);
		}

		return NULL;
	}

	return pEffect;
}

void cSkinnedMesh::Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent )
{
	pCurrent->CombinedTransformationMatrix = pCurrent->TransformationMatrix;
	if(pmatParent)
	{
		pCurrent->CombinedTransformationMatrix =
			pCurrent->CombinedTransformationMatrix * (*pmatParent);
	}

	if(pCurrent->pFrameSibling)
	{
		Update((ST_BONE*)pCurrent->pFrameSibling, pmatParent);
	}

	if(pCurrent->pFrameFirstChild)
	{
		Update((ST_BONE*)pCurrent->pFrameFirstChild, &(pCurrent->CombinedTransformationMatrix));
	}
}

void cSkinnedMesh::SetupBoneMatrixPtrs( ST_BONE* pBone )
{
	assert(pBone);

	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	if(pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if(pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
			// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
			// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
			// 찾아서 월드매트릭스를 걸어줘라.
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				LPCSTR szBoneName = pSkinInfo->GetBoneName(i);
				if(szBoneName == NULL || strlen(szBoneName) == 0)
					continue;
				ST_BONE* pInfluence = (ST_BONE*)D3DXFrameFind(m_pRootFrame, szBoneName);
				pBoneMesh->ppBoneMatrixPtrs[i] = &(pInfluence->CombinedTransformationMatrix);
			}
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if(pBone->pFrameSibling)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameSibling);
	}

	if(pBone->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs((ST_BONE*)pBone->pFrameFirstChild);
	}
}
void cSkinnedMesh::SetAnimationIndex(int nIndex)
{
	m_dCurrentAni = nIndex;
	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	D3DXTRACK_DESC stDesc;
	m_pAnimController->GetTrackDesc(0, &stDesc);
	m_pAnimController->SetTrackDesc(1, &stDesc);

	m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);

	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);

	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);

	m_pAnimController->SetTrackPosition(0, 0.0f);
	m_pAnimController->SetTrackWeight(0, 0.0f);
	m_pAnimController->SetTrackSpeed(0, 1.0f);
	m_pAnimController->SetTrackWeight(1, 1.0f);

	m_fPassedBlendingTime = 0.0f;
	m_isBlending = true;
	//if(!m_pAnimController)
	//	return;

	//if (m_dCurrentAni == nIndex)
	//	return;

	//if (m_dCurrentTrack == 1)
	//	m_dNewTrack = 0;
	//else
	//	m_dNewTrack = 1;

	//m_dCurrentAni = nIndex;

	//LPD3DXANIMATIONSET	pAniSet;
	//m_pAnimController->GetAnimationSet(nIndex % m_pAnimController->GetNumAnimationSets(),
	//	&pAniSet);
	//m_pAnimController->SetTrackAnimationSet(m_dNewTrack, pAniSet);
	//m_pAnimController->SetTrackPosition(m_dNewTrack, 0);
	//m_pAnimController->SetTrackSpeed(m_dNewTrack, 1.f);
	//m_pAnimController->SetTrackWeight(m_dNewTrack, 0);
	//m_pAnimController->SetTrackEnable(m_dNewTrack, true);
	//SAFE_RELEASE(pAniSet);
}

void cSkinnedMesh::CreateBoundingBox(ST_BONE* pBone)
{
	if (!pBone)
		return;
	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pboneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pboneMesh->pOrigMesh)
		{
			D3DXVECTOR3* pFirstPos;
			pboneMesh->pOrigMesh->LockVertexBuffer(0, (LPVOID*)&pFirstPos);
			D3DXComputeBoundingSphere(pFirstPos,
				pboneMesh->pOrigMesh->GetNumVertices(),
				pboneMesh->pOrigMesh->GetNumBytesPerVertex(),
				&m_stSphere.vCenter,
				&m_stSphere.fRadius);
			m_vOrgSphere = m_stSphere.vCenter;
			pboneMesh->pOrigMesh->UnlockVertexBuffer();
			return;
		}
	}

	if (pBone->pFrameSibling)
	{
		CreateBoundingBox((ST_BONE*)pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		CreateBoundingBox((ST_BONE*)pBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::AnimationBlend()
{
	if (m_isBlending)
	{
		m_fPassedBlendingTime += g_pTimeManager->GetElapsedTime();
		if (m_fPassedBlendingTime >= m_fBlendingTime)
		{
			m_isBlending = false;
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackWeight(1, 0.0f);
			m_pAnimController->SetTrackEnable(1, false);
		}
		else
		{
			float fWeight = m_fPassedBlendingTime / m_fBlendingTime;
			m_pAnimController->SetTrackWeight(0, fWeight);
			m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);
		}
	}

}

void cSkinnedMesh::Destroy()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy((LPD3DXFRAME)m_pRootFrame, &ah);
	SAFE_DELETE_ARRAY(m_pmWorkingPalette);
	SAFE_RELEASE(m_pEffect);
}

void cSkinnedMesh::SetRandomTrackPosition()
{
	m_pAnimController->SetTrackPosition(0, (rand() % 100) / 10.0f);
}

void cSkinnedMesh::SetReverse(bool isReverse, float fReverseStartPosition, float fReverseEndPosition)
{
	if (isReverse)
	{
		if (!m_isTurn)
		{
			m_isTurn = true;
			m_nReverse = 0;
			m_fReverseStartPosition = fReverseStartPosition;
			m_fReverseEndPosition = fReverseEndPosition;
			//m_pAnimController->SetTrackSpeed(0, 0.1f);
		}
	}
	else
	{
		m_isTurn = false;
		m_nReverse = 0;
		m_fReverseStartPosition = 0;
		m_fReverseEndPosition = 0;
		//m_pAnimController->SetTrackSpeed(0, 1.f);
	}
}

void cSkinnedMesh::SetSpeed(float fSpeed)
{
	m_pAnimController->SetTrackSpeed(0, fSpeed);
}

ST_SPHERE cSkinnedMesh::GetBoundingSphere()
{
	m_stSphere.vCenter = m_vOrgSphere + m_vPosition;
	return m_stSphere;
}
