#pragma once

class cNpcCourse
{
protected:
	std::vector<D3DXVECTOR3> m_vecVCourse;

public:
	std::vector<D3DXVECTOR3> GetCourse();

	cNpcCourse();
	~cNpcCourse();

	void Load();
};

