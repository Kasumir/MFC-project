
// SpongeBobView.h : CSpongeBobView Ŭ������ �������̽�
//

#pragma once


class CSpongeBobView : public CView
{
protected: // serialization������ ��������ϴ�.
	CSpongeBobView();
	DECLARE_DYNCREATE(CSpongeBobView)

// Ư���Դϴ�.
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
};

#ifndef _DEBUG  // SpongeBobView.cpp�� ����� ����
inline CSpongeBobDoc* CSpongeBobView::GetDocument() const
   { return reinterpret_cast<CSpongeBobDoc*>(m_pDocument); }
#endif

