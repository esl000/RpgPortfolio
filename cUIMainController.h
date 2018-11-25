#pragma once

#include "cUIObject.h"

////////////////////////////////////////////////////
//[코드규칙]꼭 엄수 할것
//엔티티, 유닛 등은 꼭꼭 만든다음 매니저에 넣어주세요. 
//매니저에서 알아서 다 렌더랑 업데이트 해줍니다.
//멤버 변수 : m_
//벡터3 : v
//포인터 : p
//int : n
//float : f
//배열 : a
//구조체 : st
//string : s
//char[] : sz
//char : c
//stlset : set
//stlvextor : vec
//matrix : mat
//material : mtl
//stlmap : map
//entity : cEntity클래스명
//함수생성 : 주석필수
//1.로딩바 이미지 파랑색
//2.미니맵 위치
//3.경험치바 보라색 변경
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

