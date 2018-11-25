#include "StdAfx.h"
#include "cAseLoad.h"
#include "Asciitok.h"
#include "cMtlTex.h"
#include "cFrame.h"

cAseLoad::cAseLoad(void)
	: m_fp(NULL)
	, m_pRoot(NULL)
{
}


cAseLoad::~cAseLoad(void)
{
}

cFrame* cAseLoad::Load( char* szFullPath )
{
	fopen_s(&m_fp, szFullPath, "r");

	//OutputDebugString(GetToken());
	
	while(char* szToken = GetToken())
	{
		if(IsEqual(szToken, ID_SCENE))
		{
			SkipBlock();
		}
		else if(IsEqual(szToken, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		else if(IsEqual(szToken, ID_GEOMETRY))
		{
			cFrame* pFrame = new cFrame;
			ProcessGEOMETRY(pFrame);
			if(m_pRoot == NULL)
			{
				m_pRoot = pFrame;
			}
			else
			{
				cFrame* pParent = m_pRoot->FindNode(pFrame->GetNodeParent());
				pParent->AddChild(pFrame);
			}
		}
	}

// 	qx = ax * sin(angle/2)
// 	qy = ay * sin(angle/2)
// 	qz = az * sin(angle/2)
// 	qw = cos(angle/2)

	//int nKeyFrame = GetTickCount() % (3200 - 640) + 640;

	//D3DXQUATERNION
	//D3DXMatrixRotationQuaternion()
	//D3DXQuaternionSlerp()
	fclose(m_fp);
	
	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}
	
	m_vecMtlTex.clear();

	m_pRoot->CalcOriginLocalTM(NULL);

	return m_pRoot;
}

char* cAseLoad::GetToken()
{
	int nCnt = 0;
	bool isQuote = false;

	while(true)
	{
		char c = fgetc(m_fp);
		if(feof(m_fp))
			break;

		if(c == '\"')
		{
			if(isQuote)
			{
				break;
			}
			else
			{
				isQuote = true;
				continue;
			}
		}

		if(!isQuote && c < 33)	// White Space
		{
			if(nCnt == 0)
				continue;
			else
				break;
		}

		m_szToken[nCnt++] = c;
	}

	if(nCnt == 0)
		return NULL;

	m_szToken[nCnt] = '\0';

	return m_szToken;
}

int cAseLoad::GetInteger()
{
	return atoi(GetToken());
}

float cAseLoad::GetFloat()
{
	return (float)atof(GetToken());
}

void cAseLoad::SkipBlock()
{
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
	} while (nLevel > 0);
}

bool cAseLoad::IsEqual( char* s1, char* s2 )
{
	return strcmp(s1, s2) == 0;
}

void cAseLoad::ProcessMATERIAL_LIST()
{
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_MATERIAL_COUNT))
		{
			m_vecMtlTex.resize(GetInteger());
		}
		else if(IsEqual(szToken, ID_MATERIAL))
		{
			int nMtlRef = GetInteger();
			m_vecMtlTex[nMtlRef] = new cMtlTex;
			ProcessMATERIAL(m_vecMtlTex[nMtlRef]);
		}
	} while (nLevel > 0);
}

void cAseLoad::ProcessMATERIAL( cMtlTex* pMtlTex )
{
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_AMBIENT))
		{
			float r = GetFloat();
			float g = GetFloat();
			float b = GetFloat();
			pMtlTex->m_stMtl.Ambient = D3DXCOLOR(r, g, b, 1.0f);
		}
		else if(IsEqual(szToken, ID_DIFFUSE))
		{
			float r = GetFloat();
			float g = GetFloat();
			float b = GetFloat();
			pMtlTex->m_stMtl.Diffuse = D3DXCOLOR(r, g, b, 1.0f);
		}
		else if(IsEqual(szToken, ID_SPECULAR))
		{
			float r = GetFloat();
			float g = GetFloat();
			float b = GetFloat();
			pMtlTex->m_stMtl.Specular = D3DXCOLOR(r, g, b, 1.0f);
		}
		else if(IsEqual(szToken, ID_MAP_DIFFUSE))
		{
			ProcessMAP_DIFFUSE(pMtlTex);
		}
	} while (nLevel > 0);
}

void cAseLoad::ProcessMAP_DIFFUSE( cMtlTex* pMtlTex )
{
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_BITMAP))
		{
			pMtlTex->m_pTexture = g_pTextureManager->GetTexture(GetToken());
		}
	} while (nLevel > 0);
}

void cAseLoad::ProcessGEOMETRY( OUT cFrame* pFrame )
{
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_NODE_NAME))
		{
			pFrame->SetNodeName(GetToken());
		}
		else if(IsEqual(szToken, ID_NODE_PARENT))
		{
			pFrame->SetNodeParent(GetToken());
		}
		else if(IsEqual(szToken, ID_NODE_TM))
		{
			ProcessNODE_TM(pFrame);
		}
		else if(IsEqual(szToken, ID_MESH))
		{
			ProcessMESH(pFrame);
		}
		else if(IsEqual(szToken, ID_MATERIAL_REF))
		{
			pFrame->SetMtlTex(m_vecMtlTex[GetInteger()]);
		}
		else if(IsEqual(szToken, ID_TM_ANIMATION))
		{
			ProcessTM_ANIMATION(pFrame);
		}
		
	} while (nLevel > 0);
}

void cAseLoad::ProcessMESH( OUT cFrame* pFrame )
{
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR2>	vecVT;
	std::vector<ST_PNT_VERTEX>	vecVertex;

	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_MESH_NUMVERTEX))
		{
			vecV.resize(GetInteger());
		}
		else if(IsEqual(szToken, ID_MESH_NUMFACES))
		{
			vecVertex.resize(GetInteger() * 3);
		}
		else if(IsEqual(szToken, ID_MESH_VERTEX_LIST))
		{
			ProcessMESH_VERTEX_LIST(vecV);
		}
		else if(IsEqual(szToken, ID_MESH_FACE_LIST))
		{
			ProcessMESH_FACE_LIST(vecV, vecVertex);
		}
		else if(IsEqual(szToken, ID_MESH_NUMTVERTEX))
		{
			vecVT.resize(GetInteger());
		}
		else if(IsEqual(szToken, ID_MESH_TVERTLIST))
		{
			ProcessMESH_TVERTLIST(vecVT);
		}
		else if(IsEqual(szToken, ID_MESH_NUMTVFACES))
		{
			GetToken();
		}
		else if(IsEqual(szToken, ID_MESH_TFACELIST))
		{
			ProcessMESH_TFACELIST(vecVT, vecVertex);
		}
		else if(IsEqual(szToken, ID_MESH_NORMALS))
		{
			ProcessMESH_NORMALS(vecVertex);
		}
	} while (nLevel > 0);

	pFrame->BuildMesh(vecVertex);
}

void cAseLoad::ProcessMESH_VERTEX_LIST( OUT std::vector<D3DXVECTOR3>& vecV )
{
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_MESH_VERTEX))
		{
			int nIndex = GetInteger();
			float x = GetFloat();
			float z = GetFloat();
			float y = GetFloat();
			vecV[nIndex] = D3DXVECTOR3(x, y, z);
		}
	} while (nLevel > 0);
}

void cAseLoad::ProcessMESH_FACE_LIST( IN std::vector<D3DXVECTOR3>& vecV, OUT std::vector<ST_PNT_VERTEX>& vecVertex )
{
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_MESH_FACE))
		{
			int nFaceIndex = GetInteger();
			GetToken(); // A:
			int A = GetInteger();
			GetToken(); // B:
			int C = GetInteger();
			GetToken(); // C:
			int B = GetInteger();
			vecVertex[nFaceIndex * 3 + 0].p = vecV[A];
			vecVertex[nFaceIndex * 3 + 1].p = vecV[B];
			vecVertex[nFaceIndex * 3 + 2].p = vecV[C];
		}
	} while (nLevel > 0);
}

void cAseLoad::ProcessMESH_TVERTLIST( OUT std::vector<D3DXVECTOR2>& vecVT )
{
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_MESH_TVERT))
		{
			int nIndex = GetInteger();
			float u = GetFloat();
			float v = 1.0f - GetFloat();
			vecVT[nIndex] = D3DXVECTOR2(u, v);
		}
	} while (nLevel > 0);
}

void cAseLoad::ProcessMESH_TFACELIST( IN std::vector<D3DXVECTOR2>& vecVT, OUT std::vector<ST_PNT_VERTEX>& vecVertex )
{
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_MESH_TFACE))
		{
			int nFaceIndex = GetInteger();
			int A = GetInteger();
			int C = GetInteger();
			int B = GetInteger();
			vecVertex[nFaceIndex * 3 + 0].t = vecVT[A];
			vecVertex[nFaceIndex * 3 + 1].t = vecVT[B];
			vecVertex[nFaceIndex * 3 + 2].t = vecVT[C];
		}
	} while (nLevel > 0);
}

void cAseLoad::ProcessMESH_NORMALS( OUT std::vector<ST_PNT_VERTEX>& vecVertex )
{
	int aModIndex[] = {0, 2, 1};
	int nModCount = 0;
	int nFaceIndex = 0;
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_MESH_FACENORMAL))
		{
			nFaceIndex = GetInteger();
			nModCount = 0;
		}
		else if(IsEqual(szToken, ID_MESH_VERTEXNORMAL))
		{
			GetToken();
			float x = GetFloat();
			float z = GetFloat();
			float y = GetFloat();
			vecVertex[nFaceIndex * 3 + aModIndex[nModCount]].n = D3DXVECTOR3(x, y, z);
			++nModCount;
		}
	} while (nLevel > 0);
}

void cAseLoad::ProcessNODE_TM( OUT cFrame* pFrame )
{
	D3DXMATRIXA16 mat;
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_TM_ROW0))
		{
			mat._11 = GetFloat();
			mat._13 = GetFloat();
			mat._12 = GetFloat();
			mat._14 = 0.0f;
		}
		else if(IsEqual(szToken, ID_TM_ROW1))
		{
			mat._31 = GetFloat();
			mat._33 = GetFloat();
			mat._32 = GetFloat();
			mat._34 = 0.0f;
		}
		else if(IsEqual(szToken, ID_TM_ROW2))
		{
			mat._21 = GetFloat();
			mat._23 = GetFloat();
			mat._22 = GetFloat();
			mat._24 = 0.0f;
		}
		else if(IsEqual(szToken, ID_TM_ROW3))
		{
			mat._41 = GetFloat();
			mat._43 = GetFloat();
			mat._42 = GetFloat();
			mat._44 = 1.0f;
		}
	} while (nLevel > 0);

	pFrame->SetWorldMatrix(mat);
}

void cAseLoad::ProcessTM_ANIMATION( OUT cFrame* pFrame )
{
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_POS_TRACK))
		{
			ProcessCONTROL_POS_TRACK(pFrame);
		}
		else if(IsEqual(szToken, ID_ROT_TRACK))
		{
			ProcessCONTROL_ROT_TRACK(pFrame);
		}
	} while (nLevel > 0);
}

void cAseLoad::ProcessCONTROL_POS_TRACK( OUT cFrame* pFrame )
{
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_POS_SAMPLE))
		{
			ST_POS_SAMPLE ps;
			ps.nKey = GetInteger();
			ps.v.x = GetFloat();
			ps.v.z = GetFloat();
			ps.v.y = GetFloat();
			pFrame->m_vecPosTrack.push_back(ps);
		}
	} while (nLevel > 0);
}

void cAseLoad::ProcessCONTROL_ROT_TRACK( OUT cFrame* pFrame )
{
	int nLevel = 0;
	do 
	{
		char* szToken = GetToken();
		if(IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if(IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken, ID_ROT_SAMPLE))
		{
			ST_ROT_SAMPLE rs;
			
			rs.nKey = GetInteger();
			
			rs.q.x = GetFloat();
			rs.q.z = GetFloat();
			rs.q.y = GetFloat();
			rs.q.w = GetFloat();

			//Axis Angle To Quaternion
			rs.q.x *= sinf(rs.q.w / 2.0f);
			rs.q.y *= sinf(rs.q.w / 2.0f);
			rs.q.z *= sinf(rs.q.w / 2.0f);
			rs.q.w = cos(rs.q.w / 2.0f);

			// ´©Àû
			if(!pFrame->m_vecRotTrack.empty())
			{
				rs.q = pFrame->m_vecRotTrack.back().q * rs.q;
			}

			pFrame->m_vecRotTrack.push_back(rs);
		}
	} while (nLevel > 0);
}
