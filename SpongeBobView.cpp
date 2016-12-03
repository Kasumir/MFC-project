
// SpongeBobView.cpp : CSpongeBobView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SpongeBob.h"
#endif

#include "SpongeBobDoc.h"
#include "SpongeBobView.h"
#include "Monster.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSpongeBobView

IMPLEMENT_DYNCREATE(CSpongeBobView, CView)

BEGIN_MESSAGE_MAP(CSpongeBobView, CView)
	// 표준 인쇄 명령입니다.
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

// CSpongeBobView 생성/소멸

CSpongeBobView::CSpongeBobView()
{
	object.CreateCharacter(0, 0);
	monster1.MonsterCreate(500, 100);
	monster2.MonsterCreate(500, 100);
	monster3.MonsterCreate(500, 100);
	monster4.MonsterCreate(500, 100);
	monster5.MonsterCreate(500, 100);
	monster_array.SetSize(5);
}

CSpongeBobView::~CSpongeBobView()
{
}

BOOL CSpongeBobView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSpongeBobView 그리기

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
	CBitmap m1_bitmap, b1_bitmap, wd_bitmap, m2_bitmap, m3_bitmap, m4_bitmap, m5_bitmap, m6_bitmap;
	b1_bitmap.LoadBitmap(IDB_BACKGROUND1);
	BITMAP b1_bmpinfo;
	b1_bitmap.GetBitmap(&b1_bmpinfo);

	dcmem.SelectObject(&b1_bitmap);
	pDC->StretchBlt(0, 0, b1_bmpinfo.bmWidth * 4 / 3, b1_bmpinfo.bmHeight * 4 / 3, &dcmem, 0, 0, b1_bmpinfo.bmWidth, b1_bmpinfo.bmHeight, SRCCOPY);//맵 그림. 맵 후에 다른거그려야함! 순서중요

	dcmem.SelectObject(&bitmap); // 블록비트맵로딩.

	CRect rect;
	GetWindowRect(&rect);
	for (int i = 0; i <= rect.bottom; i += B_SIZE) {   //가로선
		pDC->MoveTo(0, i);
		pDC->LineTo(rect.right, i);
	}
	for (int i = 0; i <= rect.right; i += B_SIZE) {    //세로선
		pDC->MoveTo(i, 0);
		pDC->LineTo(i, rect.bottom);
	}

	POSITION p;
	for (p = Tile_list.GetHeadPosition(); p != NULL;)    //블록출력
	{
		CPoint pos(Tile_list.GetNext(p));
		pDC->BitBlt(pos.x, pos.y, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
	}

	if (object.c_visible)   //캐릭출력
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
	
	monster_array[0] = monster1.m_pos;
	monster_array[1] = monster2.m_pos;
	monster_array[2] = monster3.m_pos;
	monster_array[3] = monster4.m_pos;
	monster_array[4] = monster5.m_pos;
	
	for (int i = 0; i < 5; i++)
		if (object.monsterindex() == i)
			if (object.monstercrash() == TRUE)
			{
				if (i == 0)
					monster1.MonsterDie();
				else if (i == 1)
					monster2.MonsterDie();
				else if (i == 2)
					monster3.MonsterDie();
				else if (i == 3)
					monster4.MonsterDie();
				else if (i == 4)
					monster5.MonsterDie();		
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
	if (monster2.m_visible == TRUE)
	{
		monster2.MoveState();
		monster2.check(&Tile_list);
		m2_bitmap.LoadBitmap(IDB_MONSTER1);

		BITMAP m2_bmpinfo;
		m2_bitmap.GetBitmap(&m2_bmpinfo);
		CDC m2_dcmem;
		m2_dcmem.CreateCompatibleDC(pDC);
		m2_dcmem.SelectObject(&m2_bitmap);
		pDC->TransparentBlt(monster2.m_pos.x, monster2.m_pos.y, m2_bmpinfo.bmWidth, m2_bmpinfo.bmHeight, &m2_dcmem, 0, 0, m2_bmpinfo.bmWidth, m2_bmpinfo.bmHeight, RGB(0, 255, 0));
	}
	if (monster3.m_visible == TRUE)
	{
		monster3.MoveState();
		monster3.check(&Tile_list);
		m3_bitmap.LoadBitmap(IDB_MONSTER1);

		BITMAP m3_bmpinfo;
		m3_bitmap.GetBitmap(&m3_bmpinfo);
		CDC m3_dcmem;
		m3_dcmem.CreateCompatibleDC(pDC);
		m3_dcmem.SelectObject(&m3_bitmap);
		pDC->TransparentBlt(monster3.m_pos.x, monster3.m_pos.y, m3_bmpinfo.bmWidth, m3_bmpinfo.bmHeight, &m3_dcmem, 0, 0, m3_bmpinfo.bmWidth, m3_bmpinfo.bmHeight, RGB(0, 255, 0));
	}
	if (monster4.m_visible == TRUE)
	{
		monster4.MoveState();
		monster4.check(&Tile_list);
		m4_bitmap.LoadBitmap(IDB_MONSTER1);

		BITMAP m4_bmpinfo;
		m4_bitmap.GetBitmap(&m4_bmpinfo);
		CDC m4_dcmem;
		m4_dcmem.CreateCompatibleDC(pDC);
		m4_dcmem.SelectObject(&m4_bitmap);
		pDC->TransparentBlt(monster4.m_pos.x, monster4.m_pos.y, m4_bmpinfo.bmWidth, m4_bmpinfo.bmHeight, &m4_dcmem, 0, 0, m4_bmpinfo.bmWidth, m4_bmpinfo.bmHeight, RGB(0, 255, 0));
	}
	if (monster5.m_visible == TRUE)
	{
		monster5.MoveState();
		monster5.check(&Tile_list);
		m5_bitmap.LoadBitmap(IDB_MONSTER1);

		BITMAP m5_bmpinfo;
		m5_bitmap.GetBitmap(&m5_bmpinfo);
		CDC m5_dcmem;
		m5_dcmem.CreateCompatibleDC(pDC);
		m5_dcmem.SelectObject(&m5_bitmap);
		pDC->TransparentBlt(monster5.m_pos.x, monster5.m_pos.y, m5_bmpinfo.bmWidth, m5_bmpinfo.bmHeight, &m5_dcmem, 0, 0, m5_bmpinfo.bmWidth, m5_bmpinfo.bmHeight, RGB(0, 255, 0));
	}


	//스페이스 바가 눌렸을 때, 물방울을 생성합니다.
	if (object.c_space == TRUE) {
		object.WaterDrop();
		object.wdcount[0] += 1;
		if (object.wdcount[0] == 8)
			object.wdcount[0] = 0;

	}
	else if (object.wdcount[1] == 0 && object.wdcount[2] == 0 && object.wdcount[3] == 0)
		object.wdcount[0] = 0;

	//물방울을 출력하는 코드입니다.

	if (object.wd_visible == TRUE) {
		object.crash = FALSE;
		object.WD_Cehck(&Tile_list, &monster_array);

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

	Sleep(1000 / 8);     //프레임
	object.jumpcount++;
	monster1.jumpcount++;
	Invalidate();
}


// CSpongeBobView 인쇄

BOOL CSpongeBobView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSpongeBobView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSpongeBobView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CSpongeBobView 진단

#ifdef _DEBUG
void CSpongeBobView::AssertValid() const
{
	CView::AssertValid();
}

void CSpongeBobView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpongeBobDoc* CSpongeBobView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpongeBobDoc)));
	return (CSpongeBobDoc*)m_pDocument;
}
#endif //_DEBUG


// CSpongeBobView 메시지 처리기


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
	CDialog dlg(IDD_SAVEDIALOG);
	int result = dlg.DoModal();
	
	CFile file;
	CFileException e;
	if (!file.Open(_T("mytext.txt"), CFile::modeCreate | CFile::modeWrite, &e)) {
		e.ReportError();
		return;
	}
	POSITION p;
	for (p = Tile_list.GetHeadPosition(); p != NULL;) {
		int buf[2];
		buf[0] = Tile_list.GetAt(p).x;
		buf[1] = Tile_list.GetNext(p).y;
		file.Write(buf, 2 * sizeof(int));
	}
}


void CSpongeBobView::OnLoad()
{
	CFile file;
	CFileException e;
	if (!file.Open(_T("mytext.txt"), CFile::modeRead, &e)) {
		e.ReportError();
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
