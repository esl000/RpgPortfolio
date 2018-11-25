#include "stdafx.h"
#include "cResourceManager.h"


cResourceManager::cResourceManager()
{
}


cResourceManager::~cResourceManager()
{
}

void cResourceManager::GetResourse(OUT ST_BONE** pRootBone,
	OUT LPD3DXANIMATIONCONTROLLER* pAnimController,
	char* szFolder, char* szFile)
{
	GetResourse(pRootBone, pAnimController,
		string(szFolder), string(szFile));
}

void cResourceManager::GetResourse(OUT ST_BONE** pRootBone,
	OUT LPD3DXANIMATIONCONTROLLER* pAnimController,
	string sFolder, string sFile)
{
	std::string sFullPath;
	sFullPath = sFolder + std::string("/") + sFile;

	if (m_mapFrame.find(sFullPath) != m_mapFrame.end())
	{
		(*pRootBone) = m_mapFrame[sFullPath];
		(*pAnimController) = CloneAnimController(m_mapAniController[sFullPath]);
	}
	else
	{
		Load(pRootBone, pAnimController,
			sFolder, sFile);
	}
}

void cResourceManager::Destroy()
{
	cAllocateHierarchy ah;

	for each(auto p in m_mapFrame)
	{
		D3DXFrameDestroy(p.second, &ah);
	}

	for each(auto p in m_mapAniController)
	{
		SAFE_RELEASE(p.second);
	}
}

void cResourceManager::Load(OUT ST_BONE** pRootBone,
	OUT LPD3DXANIMATIONCONTROLLER* pAnimController, 
	string sFolder, string sFile)
{
	std::string sFullPath;
	sFullPath = sFolder + std::string("/") + sFile;

	cAllocateHierarchy ah;
	ah.SetFolder(sFolder);

	ST_BONE* pRoot;
	LPD3DXANIMATIONCONTROLLER pAnim;

	D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&ah,
		NULL,
		(LPD3DXFRAME*)&pRoot,
		&pAnim);

	SetWorldMatrix(pRoot, pRoot);

	m_mapFrame[sFullPath] = pRoot;
	m_mapAniController[sFullPath] = pAnim;

	(*pRootBone) = pRoot;
	(*pAnimController) = CloneAnimController(pAnim);
}

void cResourceManager::SetWorldMatrix(ST_BONE* pRootBone, ST_BONE* pBone)
{
	ST_BONE_MESH* pMeshContainer = (ST_BONE_MESH*)pBone->pMeshContainer;
	if (pMeshContainer)
	{
		for (DWORD i = 0; i < pMeshContainer->pSkinInfo->GetNumBones(); ++i)
		{
			ST_BONE* pCurrentFrame = (ST_BONE*)D3DXFrameFind(pRootBone, pMeshContainer->pSkinInfo->GetBoneName(i));
			pMeshContainer->ppBoneMatrixPtrs[i] = &pCurrentFrame->CombinedTransformationMatrix;
		}
	}

	if (pBone->pFrameFirstChild)
	{
		SetWorldMatrix(pRootBone, (ST_BONE*)pBone->pFrameFirstChild);
	}

	if (pBone->pFrameSibling)
	{
		SetWorldMatrix(pRootBone, (ST_BONE*)pBone->pFrameSibling);
	}
}

LPD3DXANIMATIONCONTROLLER cResourceManager::CloneAnimController(LPD3DXANIMATIONCONTROLLER pAnim)
{
	LPD3DXANIMATIONCONTROLLER pOut;

	pAnim->CloneAnimationController(
		pAnim->GetMaxNumAnimationOutputs(),
		pAnim->GetMaxNumAnimationSets(),
		pAnim->GetMaxNumTracks(),
		pAnim->GetMaxNumEvents(),
		&pOut);

	return pOut;
}
