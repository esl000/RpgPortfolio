#include "StdAfx.h"
#include "cHeap.h"
#include "cNode.h"

cHeap::cHeap(void)
{
}


cHeap::~cHeap(void)
{
}

void cHeap::Insert( cNode* pNode )
{
	pNode->m_nHeapIndex = m_vecNode.size();

	m_vecNode.push_back(pNode);

	Update(pNode);
}

cNode* cHeap::Delete()
{
	if(m_vecNode.empty())
		return NULL;

	cNode* pRetNode = m_vecNode[0];

	if(m_vecNode.size() == 1)
	{
		m_vecNode.pop_back();
		return pRetNode;
	}
	
	m_vecNode[0] = m_vecNode.back();
	m_vecNode[0]->m_nHeapIndex = 0;
	m_vecNode.pop_back();

	Update(m_vecNode[0]);

	return pRetNode;
}

void cHeap::Update( cNode* pNode )
{
	UpdateUpper(pNode);
	UpdateLower(pNode);
}

void cHeap::UpdateUpper( cNode* pNode )
{
	if(pNode->m_nHeapIndex == 0)
		return;

	int nParent = (pNode->m_nHeapIndex - 1) / 2;
	if(m_vecNode[nParent]->m_fF > m_vecNode[pNode->m_nHeapIndex]->m_fF)
	{
		Swap(nParent, pNode->m_nHeapIndex);
		UpdateUpper(m_vecNode[nParent]);
	}
}

void cHeap::UpdateLower( cNode* pNode )
{
	int nLeftChild = pNode->m_nHeapIndex * 2 + 1;
	if(nLeftChild >= m_vecNode.size())
		return;

	int nMinChild = nLeftChild;

	int nRightChild = pNode->m_nHeapIndex * 2 + 2;
	if(nRightChild < m_vecNode.size())
	{
		if(m_vecNode[nRightChild]->m_fF < m_vecNode[nMinChild]->m_fF)
			nMinChild = nRightChild;
	}
	
	if(m_vecNode[nMinChild]->m_fF < m_vecNode[pNode->m_nHeapIndex]->m_fF)
	{
		Swap(nMinChild, pNode->m_nHeapIndex);
		UpdateLower(m_vecNode[nMinChild]);
	}
}

void cHeap::Swap( int nIndex1, int nIndex2 )
{
	int nTemp = m_vecNode[nIndex1]->m_nHeapIndex;
	m_vecNode[nIndex1]->m_nHeapIndex = m_vecNode[nIndex2]->m_nHeapIndex;
	m_vecNode[nIndex2]->m_nHeapIndex = nTemp;

	cNode* pTemp = m_vecNode[nIndex1];
	m_vecNode[nIndex1] = m_vecNode[nIndex2];
	m_vecNode[nIndex2] = pTemp;
}
