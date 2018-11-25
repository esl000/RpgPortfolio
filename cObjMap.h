#pragma once

#include "iMap.h"

class cObjMap : public iMap
{
private:
	std::vector<D3DXVECTOR3> m_vecVertex;

public:
	cObjMap(void);
	~cObjMap(void);

	void Setup(char* szFullPath, D3DXMATRIXA16* pmat = NULL);

	// iMap override
	virtual void Render() override {}
	virtual bool GetHeight(IN float x, IN float z, OUT float& y) override;
};

