
// SpongeBobView.h : CSpongeBobView Ŭ������ �������̽�
//

#pragma once
#include "Monster.h"
#include "GameObject.h"

#define S_MENU 0
#define S_START 1
#define S_EDITOR 2
#define S_END 3


class CSpongeBobView : public CView
{
protected: // serialization������ ��������ϴ�.
	CSpongeBobView();
	DECLARE_DYNCREATE(CSpongeBobView)

	int s_state; //scene�� ����
	CRgn start_rgn, editor_rgn, end_rgn;
	Monster monster1, monster2, monster3, monster4, monster5, monster6;
	CArray<CPoint, CPoint&> monster_array;
	GameObject object;
	CList<CPoint, CPoint&> Tile_list;

public:
	CSpongeBobDoc* GetDocument() const;

	// �۾��Դϴ�.
public:

	// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// �����Դϴ�.
public:
	virtual ~CSpongeBobView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSave();
	afx_msg void OnLoad();
};

#ifndef _DEBUG  // SpongeBobView.cpp�� ����� ����
inline CSpongeBobDoc* CSpongeBobView::GetDocument() const
{
	return reinterpret_cast<CSpongeBobDoc*>(m_pDocument);
}
#endif

