#pragma once

struct ST_BONE;

class cSkinnedMesh
{
	friend class cSkinnedMeshManager;

private:
	//하나만 생성
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;

	// 객체마다 생성
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;

	string					m_sFolder;
	string					m_sFIle;

	float					m_fBlendingTime;
	float					m_fPassedBlendingTime;
	bool						m_isBlending;
	
	D3DXVECTOR3				m_vOrgSphere;
	int						m_nReverse;
	bool						m_isTurn;
	float					m_fReverseEndPosition;
	float					m_fReverseStartPosition;

	float					m_fSleepPosition;

	ST_SPHERE m_stSphere;
	SYNTHESIZE(bool, m_isStand, StandSpeedSet);
	SYNTHESIZE_ONLY_GETTER(ST_BONE*, m_pRootFrame, RootFrame);
	SYNTHESIZE_ONLY_GETTER(DWORD, m_dCurrentAni, CurrentAni);
	SYNTHESIZE_ONLY_GETTER(double, m_dPeriod, AnimPeriod);
	SYNTHESIZE_ONLY_GETTER(double, m_dPosition, AnimPosition);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, Direction);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(bool, m_bIsRotation, IsRotation);
public:
	cSkinnedMesh(const char* szFolder, const char* szFilename);
	~cSkinnedMesh(void);
	
	void UpdateAndRender(D3DXMATRIXA16* matParent = NULL);
	void SetAnimationIndex(int nIndex);
	void SetRandomTrackPosition(); // 테스트용
	void SetReverse(bool isReverse, float fReverseStartPosition, float fReverseEndPosition);
	void SetSpeed(float fSpeed);
	ST_SPHERE GetBoundingSphere();
private:
	cSkinnedMesh();
	//void Load(LPVOID pThis);
	void Load(const char* szFolder, const char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void AnimationBlend();
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void CreateBoundingBox(ST_BONE* pBone);
	void Destroy();

};

