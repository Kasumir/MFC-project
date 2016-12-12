
// SpongeBobView.h : CSpongeBobView 클래스의 인터페이스
//

#pragma once
#include "Monster.h"
#include "GameObject.h"
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include "Mmsystem.h"
#include "Digitalv.h"

#define S_MENU 0
#define S_START 1
#define S_EDITOR 2
#define S_END 3
#define S_STOP 4
#define S_OVER 5


class CSpongeBobView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSpongeBobView();
	DECLARE_DYNCREATE(CSpongeBobView)

	Monster monster[10];
	CArray<CPoint, CPoint&> monster_array;
	int s_state; //scene의 상태
	int stageNum;
	int m_deadCount;
	GameObject object;
	CList<CPoint, CPoint&> Tile_list;
	CList<tilestyle, tilestyle> LRTile_list;
	BOOL e_block, e_char, e_mon, e_lrblock;
	BOOL i_state;
	BOOL openStage;
	CRgn start_rgn, editor_rgn, end_rgn;
	CString szSoundPath;
	CString sound_menu;
	CString sound_clear;
	CString sound_gameover;
	

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
	afx_msg void OnLrblock();
	afx_msg void OnUpdateLrblock(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // SpongeBobView.cpp의 디버그 버전
inline CSpongeBobDoc* CSpongeBobView::GetDocument() const
{
	return reinterpret_cast<CSpongeBobDoc*>(m_pDocument);
}
#endif

