
// SpongeBobView.cpp : CSpongeBobView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "SpongeBob.h"
#endif

#include "SpongeBobDoc.h"
#include "SpongeBobView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSpongeBobView

IMPLEMENT_DYNCREATE(CSpongeBobView, CView)

BEGIN_MESSAGE_MAP(CSpongeBobView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSpongeBobView ����/�Ҹ�

CSpongeBobView::CSpongeBobView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CSpongeBobView::~CSpongeBobView()
{
}

BOOL CSpongeBobView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CSpongeBobView �׸���

void CSpongeBobView::OnDraw(CDC* /*pDC*/)
{
	CSpongeBobDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CSpongeBobView �μ�

BOOL CSpongeBobView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CSpongeBobView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CSpongeBobView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CSpongeBobView ����

#ifdef _DEBUG
void CSpongeBobView::AssertValid() const
{
	CView::AssertValid();
}

void CSpongeBobView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpongeBobDoc* CSpongeBobView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpongeBobDoc)));
	return (CSpongeBobDoc*)m_pDocument;
}
#endif //_DEBUG


// CSpongeBobView �޽��� ó����
