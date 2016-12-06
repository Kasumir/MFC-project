
// SpongeBobView.h : CSpongeBobView 클래스의 인터페이스
//

#pragma once
#include "Monster.h"
#include "GameObject.h"


class CSpongeBobView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSpongeBobView();
	DECLARE_DYNCREATE(CSpongeBobView)

	Monster monster0, monster1, monster2, monster3, monster4, monster5, monster6, monster7, monster8, monster9,monster10;
	CArray<CPoint, CPoint&> monster_array;
	int s_state; //scene의 상태
	GameObject object;
	CList<CPoint, CPoint&> Tile_list;
	BOOL e_block, e_char, e_mon;
	BOOL i_state;
public:
	CSpongeBobDoc* GetDocument() const;

	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 구현입니다.
public:
	virtual ~CSpongeBobView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSave();
	afx_msg void OnLoad();
	afx_msg void OnBlock();
	afx_msg void OnCharacter();
	afx_msg void OnMonster();
	afx_msg void OnUpdateBlock(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCharacter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMonster(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // SpongeBobView.cpp의 디버그 버전
inline CSpongeBobDoc* CSpongeBobView::GetDocument() const
{
	return reinterpret_cast<CSpongeBobDoc*>(m_pDocument);
}
#endif

