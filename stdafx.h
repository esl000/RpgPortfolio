// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include <iostream>
using namespace std;
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


extern HWND g_hWnd;
extern POINT g_ptMouse;
extern CRITICAL_SECTION cs_tile;
extern CRITICAL_SECTION cs_intersect;
extern CRITICAL_SECTION cs;

#include <vector>
#include <string>
#include <map>
#include <set>
#include <list>
#include <assert.h>
#include <math.h>

#define DEBUG_SPHERE 
//#define MAPTOOL 

#define CHUNK_SIZE 512

#define WINSIZEX 1424
#define WINSIZEY 725

//FVF
// D3D 정점 FVF플래그 작성 순서 및 플래그
// 
// 1. Position 정점의 좌표 x,y,z(float)             :  D3DFVF_XYZ
// 2. RHW (float)                                   :  D3DFVF_XYZRHW
// (D3DFVF_XYZ 또는 D3DFVF_NORMAL과 같이 사용불가)
// 3. Blending Weight Data 결합 가중치 (float)      : D3DFVF_XYZB1 ~ D3DFVF_XYZB5
// 4. Vertex Normal 정점의 법선 벡터 x,y,z(float)   : D3DFVF_NORMAL
// 5. Vertex Point Size 정점의 점 크기 (float)      : D3DFVF_PSIZE
// 6. Diffuse Color (DWORD)                         : D3DFVF_DIFFUSE
// 7. Specular Color (DWORD)                        : D3DFVF_SPECULAR
// 8. Texture Coordinate Set 1 (float)              : D3DFVF_TEX0 - D3DFVF_TEX8 

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;
	enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE};
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;
	enum {FVF = D3DFVF_XYZ | D3DFVF_TEX1};
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

struct ST_RHWC_VERTEX
{
	D3DXVECTOR4 p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct ST_POS_SAMPLE
{
	int				nKey;
	D3DXVECTOR3		v;
};

struct ST_ROT_SAMPLE
{
	int				nKey;
	D3DXQUATERNION	q;
};

struct ST_SPHERE
{
	D3DXVECTOR3 vCenter;
	float		fRadius;
	ST_SPHERE() : vCenter(D3DXVECTOR3(0, 0, 0)), fRadius(0.0f) {}
	ST_SPHERE(D3DXVECTOR3 _vCenter, float _fRadius) : vCenter(_vCenter), fRadius(_fRadius) {}
};

struct ST_FACE
{
	D3DXVECTOR3 v1, v2, v3;
	ST_FACE() : v1(0, 0, 0), v2(0, 0, 0), v3(0, 0, 0) {}
	ST_FACE(D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 p3) : v1(p1), v2(p2), v3(p3) {}
};

struct ST_BOUNDINGBOX
{
	vector<ST_FACE> vecPosition;
};

struct ST_SIZEF
{
	float fWidth;
	float fHeight;
	ST_SIZEF() : fWidth(0.0f), fHeight(0.0f) {}
	ST_SIZEF(float _fWidth, float _fHeight) : fWidth(_fWidth), fHeight(_fHeight) {}
};

struct ST_CHUNK
{
	int x;
	int z;
	ST_CHUNK() : x(0), z(0) {}
	ST_CHUNK(int _fX, int _fZ) : x(_fX), z(_fZ) {}
};

struct ST_CHUNK_INDEX
{
	int x;
	int z;
	ST_CHUNK_INDEX() : x(0), z(0) {}
	ST_CHUNK_INDEX(int _nX, int _nZ) : x(_nX), z(_nZ) {}
};


struct ST_MESSAGE
{
	DWORD	dwIndex;
	DWORD	dwFlag;
	string		sData;
};


///////////////////////////////////////
//UI(Information)
#define ITEM_X 4
#define ITEM_Y 5
#define ITEMX 2
#define ITEMY 8
#define INTERFACE_X 12
#define SKILLINVEN 9

enum SKILL
{
	E_SKILL0,
	E_SKILL1,
	E_SKILL2,
	E_SKILL3,
	E_SKILL4,
	E_SKILL5
};
//
//
//class cUIImageView;
//class cInvenTest
//{
//public:
//	SKILL				skillType;
//	ITEM			    itemType;
//	RECT				rc;
//	cUIImageView*		pImageView;
//	string				sitemName;
//};
///////////////////////////////////////



#define SINGLETONE(class_name) private:\
	class_name(void);\
	~class_name(void);\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}


#define SAFE_RELEASE(p) {if(p) {p->Release(); p = NULL;} }
#define SAFE_DELETE(p) {if(p) {delete p; p = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] p; p = NULL;}}
#define SAFE_ADD_REF(p) {if(p) {p->AddRef();}}

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_ONLY_GETTER(varType, varName, FunName)\
protected: varType varName;\
public: inline varType Get##FunName(void) { return varName; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var){ varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) { return varName; }\
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
	SAFE_ADD_REF(var);\
	SAFE_RELEASE(varName);\
	varName = var;\
		}\
	}

#define IN  
#define OUT

inline bool IsFocusSight(D3DXVECTOR3 vPos, D3DXVECTOR3 vDest, D3DXVECTOR3 vSight)
{
	D3DXVECTOR3 vDir = vDest - vPos;
	//cout << D3DXVec3Dot(&vSight, &vDir) << endl;
	if (D3DXVec3Dot(&vSight, &vDir) > 0)
	{
		return true;
	}
	else return false;
}

inline ST_CHUNK GetChunk(D3DXVECTOR3 vPos)
{
	int x, z;
	if (vPos.x >= 0)
		x = CHUNK_SIZE * ((int)vPos.x / CHUNK_SIZE);
	else
		x = CHUNK_SIZE * (((int)vPos.x / CHUNK_SIZE) - 1);

	if (vPos.z >= 0)
		z = CHUNK_SIZE * ((int)vPos.z / CHUNK_SIZE);
	else
		z = CHUNK_SIZE * (((int)vPos.z / CHUNK_SIZE) - 1);
	return ST_CHUNK(x, z);
}


inline ST_CHUNK_INDEX GetChunkIndex(D3DXVECTOR3 vPos)
{
	ST_CHUNK stChunk = GetChunk(vPos);
	return ST_CHUNK_INDEX(stChunk.x / CHUNK_SIZE, -stChunk.z / CHUNK_SIZE);
}

inline bool IntersectSphereSphere(ST_SPHERE stSphere1, ST_SPHERE stSphere2)
{
	if (D3DXVec3Length(&(stSphere1.vCenter - stSphere2.vCenter)) < stSphere1.fRadius + stSphere2.fRadius)
		return true;
	else
		return false;
}

inline bool IntersectBoxSphere(vector<ST_FACE>& vecFace, ST_SPHERE stSphere)
{
	for (int i = 0; i < vecFace.size(); ++i)
	{
		D3DXVECTOR3 vDir;
		float u, v, y;
		D3DXVec3Cross(&vDir, &(vecFace[i].v3 - vecFace[i].v1), &(vecFace[i].v2 - vecFace[i].v1));
		if (D3DXIntersectTri(&vecFace[i].v1,
			&vecFace[i].v2,
			&vecFace[i].v3,
			&stSphere.vCenter,
			&vDir,
			&u, &v, &y))
		{
			if (y < stSphere.fRadius)
			{
				return true;
			}
		}
	}
	return false;
}



inline bool operator==(ST_CHUNK var1, ST_CHUNK var2)
{
	if (var1.x == var2.x && var1.z == var2.z)
		return true;
	else
		return false;
}

inline bool operator!=(ST_CHUNK var1, ST_CHUNK var2)
{
	return !(var1 == var2);
}

inline bool operator==(ST_CHUNK_INDEX var1, ST_CHUNK_INDEX var2)
{
	if (var1.x == var2.x && var1.z == var2.z)
		return true;
	else
		return false;
}

inline bool operator!=(ST_CHUNK_INDEX var1, ST_CHUNK_INDEX var2)
{
	return !(var1 == var2);
}







//-------------------------기본 클래스 인터페이스
#include "cObject.h"
#include "cGameObject.h"
#include "cSkinnedMesh.h"
#include "cUIObject.h"
#include "cEntity.h"
#include "cUnit.h"
#include "cFrustum.h"
#include "iEffect.h"
#include "cSkill.h"
#include "cRay.h"
//--------------------------------------------

//----------------------------------데이터 베이스
#include "cNpcDataBase.h"
#include "cQuestDatabase.h"
#include "cMonsterDatabase.h"
#include "cBuildingDatabase.h"
#include "cObjectDatabase.h"
#include "cNpcCourse.h"
#include "cItemDatabase.h"
//--------------------------------------------


//-----------------------------------기본 매니져
#include "cObjectManager.h"
#include "cDeviceManager.h"
#include "cTimeManager.h"
#include "cDeviceManager.h"
#include "cTextureManager.h"
#include "cSkinnedMeshManager.h"
#include "cFontManager.h"
#include "cSceneManager.h"
#include "cEntityManager.h"
#include "cUnitManager.h"
#include "cEffectManager.h"
#include "cSkillManager.h"
#include "cIntersectManager.h"
#include "cTileManager.h"
#include "cObjManager.h"
#include "cUImanager.h"
#include "cPicking.h"
#include "cMessageManager.h"
#include "cShaderManager.h"
//---------------------------------------------

//---------------------------------------양쌤코드
#include "soundManager.h"
//---------------------------------------------

//---------------------------------------??????
#include "Asciitok.h"
//---------------------------------------------

inline LPD3DXEFFECT LoadEffect(const char* szFilename)
{
	LPD3DXEFFECT pEffect = NULL;

	DWORD dwShaderFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

#ifdef DEBUG_VS
	dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
	dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

	ID3DXBuffer* pBuffer = NULL;
	if (FAILED(D3DXCreateEffectFromFile(g_pD3DDevice,
		szFilename,
		NULL,
		NULL,
		dwShaderFlags,
		NULL,
		&pEffect,
		&pBuffer)))
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