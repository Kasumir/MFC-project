
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
#include "SaveDialog.h"
#include "LoadDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSpongeBobView

IMPLEMENT_DYNCREATE(CSpongeBobView, CView)

BEGIN_MESSAGE_MAP(CSpongeBobView, CView)
	// ǥ�� �μ� �����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_SAVE, &CSpongeBobView::OnSave)
	ON_COMMAND(ID_LOAD, &CSpongeBobView::OnLoad)
END_MESSAGE_MAP()

// CSpongeBobView ����/�Ҹ�

CSpongeBobView::CSpongeBobView()
{
	object.CreateCharacter(0, 0);
	monster1.MonsterCreate(500, 100);
	i_state = TRUE;
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

void CSpongeBobView::OnDraw(CDC* pDC)
{
	CSpongeBobDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//---------------------
	CBitmap bitmap, c_bitmap;
	bitmap.LoadBitmap(IDB_BLOCK);
	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);
	CDC dcmem;
	dcmem.CreateCompatibleDC(pDC);
	//---------------------
	CBitmap m1_bitmap, b1_bitmap, wd_bitmap;
	b1_bitmap.LoadBitmap(IDB_BACKGROUND1);
	BITMAP b1_bmpinfo;
	b1_bitmap.GetBitmap(&b1_bmpinfo);

	dcmem.SelectObject(&b1_bitmap);
	pDC->StretchBlt(0, 0, b1_bmpinfo.bmWidth * 4 / 3, b1_bmpinfo.bmHeight * 4 / 3, &dcmem, 0, 0, b1_bmpinfo.bmWidth, b1_bmpinfo.bmHeight, SRCCOPY);//�� �׸�. �� �Ŀ� �ٸ��ű׷�����! �����߿�

	dcmem.SelectObject(&bitmap); // ���Ϻ�Ʈ�ʷε�.

	CRect rect;
	GetWindowRect(&rect);
	for (int i = 0; i <= rect.bottom; i += B_SIZE) {   //���μ�
		pDC->MoveTo(0, i);
		pDC->LineTo(rect.right, i);
	}
	for (int i = 0; i <= rect.right; i += B_SIZE) {    //���μ�
		pDC->MoveTo(i, 0);
		pDC->LineTo(i, rect.bottom);
	}

	POSITION p;
	for (p = Tile_list.GetHeadPosition(); p != NULL;)    //�������
	{
		CPoint pos(Tile_list.GetNext(p));
		pDC->BitBlt(pos.x, pos.y, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
	}

	if (object.c_visible)   //ĳ�����
	{
		object.move();
		object.check(&Tile_list);
		if (object.c_LRstate == STOP)
		{
			if (object.LRcount > 0) {
				object.LRcount = 1;
				c_bitmap.LoadBitmap(IDB_CR1);
			}
			else if (object.LRcount < 0) {
				object.LRcount = -1;
				c_bitmap.LoadBitmap(IDB_CL1);
			}
		}
		else if (object.c_LRstate == RIGHT)
		{
			object.LRcount++;
			c_bitmap.LoadBitmap((object.LRcount % 6) + 319);
		}
		else if (object.c_LRstate == LEFT)
		{
			object.LRcount++;
			c_bitmap.LoadBitmap((object.LRcount % 6) + 311);
		}

		BITMAP c_bmpinfo;
		c_bitmap.GetBitmap(&c_bmpinfo);
		CDC c_dcmem;
		c_dcmem.CreateCompatibleDC(pDC);
		c_dcmem.SelectObject(&c_bitmap);
		//pDC->BitBlt(object.c_pos.x, object.c_pos.y, c_bmpinfo.bmWidth, c_bmpinfo.bmHeight, &c_dcmem, 0, 0, SRCCOPY);
		pDC->TransparentBlt(object.c_pos.x, object.c_pos.y, c_bmpinfo.bmWidth * 2 / 3, c_bmpinfo.bmHeight * 2 / 3, &c_dcmem, 0, 0, c_bmpinfo.bmWidth, c_bmpinfo.bmHeight, RGB(0, 255, 0));
	}


	if (monster1.m_visible == TRUE)
	{
		monster1.MoveState();
		monster1.check(&Tile_list);
		m1_bitmap.LoadBitmap(IDB_MONSTER1);

		BITMAP m1_bmpinfo;
		m1_bitmap.GetBitmap(&m1_bmpinfo);
		CDC m1_dcmem;
		m1_dcmem.CreateCompatibleDC(pDC);
		m1_dcmem.SelectObject(&m1_bitmap);
		pDC->TransparentBlt(monster1.m_pos.x, monster1.m_pos.y, m1_bmpinfo.bmWidth, m1_bmpinfo.bmHeight, &m1_dcmem, 0, 0, m1_bmpinfo.bmWidth, m1_bmpinfo.bmHeight, RGB(0, 255, 0));
	}
	//�����̽� �ٰ� ������ ��, ������� �����մϴ�.
	if (object.c_space == TRUE) {
		object.WaterDrop();
		object.wdcount[0] += 1;
		if (object.wdcount[0] == 8)
			object.wdcount[0] = 0;

	}
	else if (object.wdcount[1] == 0 && object.wdcount[2] == 0 && object.wdcount[3] == 0)
		object.wdcount[0] = 0;

	//������� ����ϴ� �ڵ��Դϴ�.

	if (object.wd_visible == TRUE) {

		wd_bitmap.LoadBitmap(IDB_WaterDrop);
		BITMAP wd_bmpinfo;
		wd_bitmap.GetBitmap(&wd_bmpinfo);
		CDC wd_dcmem;
		CPoint pos;
		wd_dcmem.CreateCompatibleDC(pDC);
		wd_dcmem.SelectObject(&wd_bitmap);
		for (int i = 1; i <= 10; i++) {
			if (object.wdcount[i] != 0) {
				pos = object.Water_drop.GetAt(i);
				pDC->TransparentBlt(pos.x, pos.y, wd_bmpinfo.bmWidth, wd_bmpinfo.bmHeight, &wd_dcmem, 0, 0, wd_bmpinfo.bmWidth, wd_bmpinfo.bmHeight, RGB(0, 255, 0));
			}
		}
		object.WaterDropMove();
	}

	if (i_state)
	{
		Sleep(1000 / 8);     //������
		object.jumpcount++;
		monster1.jumpcount++;
		Invalidate();
	}
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


void CSpongeBobView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPoint pos;
	pos.x = (point.x / B_SIZE) * B_SIZE;
	pos.y = (point.y / B_SIZE) * B_SIZE;
	POSITION p;
	for (p = Tile_list.GetHeadPosition(); p != NULL;) {
		if (pos == Tile_list.GetAt(p)) {
			return;
		}
		Tile_list.GetNext(p);
	}
	Tile_list.AddTail(pos);
}


void CSpongeBobView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPoint pos;
	pos.x = (point.x / B_SIZE) * B_SIZE;
	pos.y = (point.y / B_SIZE) * B_SIZE;
	POSITION p;
	for (p = Tile_list.GetHeadPosition(); p != NULL;) {
		if (pos == Tile_list.GetAt(p)) {
			Tile_list.RemoveAt(p);
			break;
		}
		Tile_list.GetNext(p);
	}
}


void CSpongeBobView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case VK_LEFT:
		object.c_LRstate = LEFT;
		object.c_lastLRstate = LEFT;
		break;
	case VK_RIGHT:
		object.c_LRstate = RIGHT;
		object.c_lastLRstate = RIGHT;
		break;
	case VK_UP:
		if (object.c_UDstate == STOP) {
			object.c_UDstate = UP;
			object.jumpcount = 0;
		}
		break;
	case VK_SPACE:
		object.c_space = TRUE;
		object.wdcount[0] = 0;
		break;
	}
}


void CSpongeBobView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case VK_LEFT:
		object.c_LRstate = STOP;
		object.LRcount = -1;
		break;
	case VK_RIGHT:
		object.LRcount = 1;
		object.c_LRstate = STOP;
		break;
	case VK_SPACE:
		object.c_space = FALSE;
		break;
	}
}

void CSpongeBobView::OnSave()
{
	i_state = FALSE;
	//������ ����
	CString str;
	SaveDialog dlg;
	int result = dlg.DoModal();
	if (result == IDOK) {
		str.Format(_T("%s.txt"), dlg.str);
		CFile file;
		CFileException e;
		if (!file.Open(str, CFile::modeCreate | CFile::modeWrite, &e)) {
			e.ReportError();
			return;
		}
		for (POSITION p = Tile_list.GetHeadPosition(); p != NULL;) {
			int buf[2];
			buf[0] = Tile_list.GetAt(p).x;
			buf[1] = Tile_list.GetNext(p).y;
			file.Write(buf, 2 * sizeof(int));
		}

		//���� ��� ����
		CFile file_list;
		CFileException e1;
		filename tmp;
		CList<filename, filename&> namelist;
		if (!file_list.Open(_T("filename.txt"), CFile::modeReadWrite, &e1)) {  //���ϰ�ü ����
			e1.ReportError();
			return;
		}
		tmp.size = (int)str.GetLength() * 2;
		tmp.name = str;
		file_list.SeekToEnd();
		file_list.Write(&(tmp.size), 4);
		file_list.Write(tmp.name.GetBuffer(tmp.size), tmp.size);
		tmp.name.ReleaseBuffer(tmp.size);
	}

	i_state = TRUE;
	Invalidate();
}


void CSpongeBobView::OnLoad()
{
	i_state = FALSE;
	LoadDialog dlg;
	int pos;
	filename tmp;
	CFile name_list;
	CFileException e1;
	if (!name_list.Open(_T("filename.txt"), CFile::modeRead, &e1)) {//���ϰ�ü����
		e1.ReportError();
		return;
	}
	int len = (int)(name_list.GetLength());
	while(1){                          //filename.txt�� �о����
		if (name_list.GetPosition() >= len)
			break;
		name_list.Read(&tmp.size, sizeof(int));
		name_list.Read(tmp.name.GetBuffer(tmp.size), tmp.size);
		tmp.name.ReleaseBuffer(tmp.size);
		dlg.tmp_list.AddTail(tmp);
	}

	int result = dlg.DoModal();

	if (result == IDOK) {
		CFile file;
		CFileException e;
		if (!file.Open(dlg.str, CFile::modeRead, &e)) {
			e.ReportError();
			i_state = TRUE;
			Invalidate();
			return;
		}
		Tile_list.RemoveAll();
		for (int i = 0; i < file.GetLength() / 8; i++)
		{
			int buf[2];
			file.Read(buf, 2 * sizeof(int));
			CPoint pos = { buf[0], buf[1] };
			Tile_list.AddTail(pos);
		}
	}
	i_state = TRUE;
	Invalidate();
}