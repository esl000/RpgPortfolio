#pragma once

class cFrame;
class cMtlTex;

class cAseLoad
{
private:
	FILE*							m_fp;
	char							m_szToken[1024];
	cFrame*							m_pRoot;
	std::vector<cMtlTex*>			m_vecMtlTex;

public:
	cAseLoad(void);
	~cAseLoad(void);

	cFrame* Load(char* szFullPath);

private:
	char* GetToken();
	int GetInteger();
	float GetFloat();
	void SkipBlock();
	bool IsEqual(char* s1, char* s2);
	void ProcessMATERIAL_LIST();
	void ProcessMATERIAL(OUT cMtlTex* pMtlTex);
	void ProcessMAP_DIFFUSE(OUT cMtlTex* pMtlTex);
	void ProcessGEOMETRY(OUT cFrame* pFrame);
	void ProcessMESH(OUT cFrame* pFrame);
	void ProcessMESH_VERTEX_LIST(OUT std::vector<D3DXVECTOR3>& vecV);
	void ProcessMESH_FACE_LIST(IN std::vector<D3DXVECTOR3>& vecV, OUT std::vector<ST_PNT_VERTEX>& vecVertex);
	void ProcessMESH_TVERTLIST(OUT std::vector<D3DXVECTOR2>& vecVT);
	void ProcessMESH_TFACELIST(IN std::vector<D3DXVECTOR2>& vecVT, OUT std::vector<ST_PNT_VERTEX>& vecVertex);
	void ProcessMESH_NORMALS(OUT std::vector<ST_PNT_VERTEX>& vecVertex);
	void ProcessNODE_TM(OUT cFrame* pFrame);
	void ProcessTM_ANIMATION(OUT cFrame* pFrame);
	void ProcessCONTROL_POS_TRACK(OUT cFrame* pFrame);
	void ProcessCONTROL_ROT_TRACK(OUT cFrame* pFrame);
};

