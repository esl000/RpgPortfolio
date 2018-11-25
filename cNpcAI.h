#pragma once

class iUnitAction;
class cNpcCourse;

class cNpcAI : public iUnitAction
{
private:
	cNpcCourse* m_pCourse;
	cSkinnedMesh* m_pOwnerMesh;
	SYNTHESIZE(D3DXVECTOR3, vPosition, position);
public:

	void Start() override;
	void Update() override;

	cNpcAI();
	~cNpcAI();
};

