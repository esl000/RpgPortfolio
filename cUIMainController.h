#pragma once

#include "cUIObject.h"

////////////////////////////////////////////////////
//[�ڵ��Ģ]�� ���� �Ұ�
//��ƼƼ, ���� ���� ���� ������� �Ŵ����� �־��ּ���. 
//�Ŵ������� �˾Ƽ� �� ������ ������Ʈ ���ݴϴ�.
//��� ���� : m_
//����3 : v
//������ : p
//int : n
//float : f
//�迭 : a
//����ü : st
//string : s
//char[] : sz
//char : c
//stlset : set
//stlvextor : vec
//matrix : mat
//material : mtl
//stlmap : map
//entity : cEntityŬ������
//�Լ����� : �ּ��ʼ�
//1.�ε��� �̹��� �Ķ���
//2.�̴ϸ� ��ġ
//3.����ġ�� ����� ����
////////////////////////////////////////////////////



class cUIImageView;
class cObject;
class cUIButton;
class cUIStatus;
class cUIMiniMap;

class cUIMainController
	: public cUIObject

{
protected:
	LPD3DXSPRITE		m_pSprite;

	cUIImageView*		m_pUIImageView;
	cUIObject*			m_pRootUI;
	cUIButton*			m_pUIButton;
	cUIStatus*			m_pUIStatus;
	cUIMiniMap*			m_pcUIMiniMap;

	bool				m_bInvenTory;
	bool				m_bCheck;
	int					m_nData;
	int					m_iState;
	float				m_fGauge;

public:
	cUIMainController();
	virtual ~cUIMainController();

public:
	virtual void SetUp(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;
};

