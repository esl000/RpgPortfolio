#pragma once

class cNode;

class cHeap
{
private:
	std::vector<cNode*> m_vecNode;

public:
	cHeap(void);
	~cHeap(void);

	void	Insert(cNode* pNode);
	cNode*	Delete();
	void	Update(cNode* pNode);
	void	UpdateUpper(cNode* pNode);
	void	UpdateLower(cNode* pNode);
	void	Swap(int nIndex1, int nIndex2);
};

