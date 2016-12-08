
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
#include "SaveDialog.h"
#include "LoadDialog.h"


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
	ON_COMMAND(ID_BLOCK, &CSpongeBobView::OnBlock)
	ON_COMMAND(ID_CHARACTER, &CSpongeBobView::OnCharacter)
	ON_COMMAND(ID_MONSTER, &CSpongeBobView::OnMonster)
	ON_UPDATE_COMMAND_UI(ID_BLOCK, &CSpongeBobView::OnUpdateBlock)
	ON_UPDATE_COMMAND_UI(ID_CHARACTER, &CSpongeBobView::OnUpdateCharacter)
	ON_UPDATE_COMMAND_UI(ID_MONSTER, &CSpongeBobView::OnUpdateMonster)
END_MESSAGE_MAP()

// CSpongeBobView 생성/소멸

CSpongeBobView::CSpongeBobView()
{
	for (int i = 0; i < 10; i++)
		monster[i].MonsterDie();
	monster_array.SetSize(10);
	e_block = e_mon = e_char = FALSE;
	i_state = TRUE;
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
	CBitmap bitmap, c_bitmap; //블록 비트맵 로딩
	CBitmap m_bitmap, b1_bitmap, wd_bitmap;
	bitmap.LoadBitmap(IDB_BLOCK);
	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);
	CDC dcmem;
	dcmem.CreateCompatibleDC(pDC);
	dcmem.SelectObject(&bitmap); 
	//----------------------
	m_bitmap.LoadBitmap(IDB_MONSTER1);  //몬스터 비트맵 로딩
	BITMAP m_bmpinfo;
	m_bitmap.GetBitmap(&m_bmpinfo);
	CDC m_dcmem;
	m_dcmem.CreateCompatibleDC(pDC);
	m_dcmem.SelectObject(&m_bitmap);
	//------------------------
	b1_bitmap.LoadBitmap(IDB_BACKGROUND1);  //배경 비트맵 로딩
	BITMAP b1_bmpinfo;
	b1_bitmap.GetBitmap(&b1_bmpinfo);
	CDC b_dcmem;
	b_dcmem.CreateCompatibleDC(pDC);
	b_dcmem.SelectObject(&b1_bitmap);
	pDC->StretchBlt(0, 0, b1_bmpinfo.bmWidth * 4 / 3, b1_bmpinfo.bmHeight * 4 / 3, &b_dcmem, 0, 0, b1_bmpinfo.bmWidth, b1_bmpinfo.bmHeight, SRCCOPY);//맵 그림. 맵 후에 다른거그려야함! 순서중요
    //----------------------------------------------------------------------
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
	for (POSITION p = Tile_list.GetHeadPosition(); p != NULL;)    //블록출력
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
		pDC->TransparentBlt(object.c_pos.x, object.c_pos.y, c_bmpinfo.bmWidth * 2 / 3, c_bmpinfo.bmHeight * 2 / 3, &c_dcmem, 0, 0, c_bmpinfo.bmWidth, c_bmpinfo.bmHeight, RGB(0, 255, 0));
	}
	for(int i= 0; i<10; i++)
		monster_array[i] = monster[i].m_pos;
	for (int i = 1; i<11; i++)
		if (object.monstercrash(i) == TRUE)
		{
			if (object.monsterindex(i) == 0) {
				monster[0].MonsterDie();
			}else if (object.monsterindex(i) == 1) {
				monster[1].MonsterDie();
			}else if (object.monsterindex(i) == 2) {
				monster[2].MonsterDie();
			}else if (object.monsterindex(i) == 3) {
				monster[3].MonsterDie();
			}else if (object.monsterindex(i) == 4) {
				monster[4].MonsterDie();
			}else if (object.monsterindex(i) == 5) {
				monster[5].MonsterDie();
			}else if (object.monsterindex(i) == 6) {
				monster[6].MonsterDie();
			}else if (object.monsterindex(i) == 7) {
				monster[7].MonsterDie();
			}else if (object.monsterindex(i) == 8) {
				monster[8].MonsterDie();
			}else if (object.monsterindex(i) == 9) {
				monster[9].MonsterDie();
			}object.crash[i] = FALSE;}
	for (int i = 0; i < 10; i++) {
		if (monster[i].m_visible)
		{
			monster[i].MoveState();
			monster[i].check(&Tile_list);
			monster[i].followcharacter(object.c_pos, object.c_LRstate);
			pDC->TransparentBlt(monster[i].m_pos.x, monster[i].m_pos.y, m_bmpinfo.bmWidth, m_bmpinfo.bmHeight, &m_dcmem, 0, 0, m_bmpinfo.bmWidth, m_bmpinfo.bmHeight, RGB(0, 255, 0));
		}
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

	if (i_state)
	{
		Sleep(1000 / 8);     //프레임
		object.jumpcount++;
		//monster1.jumpcount++;
		Invalidate();
	}
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
	if (e_block)
	{
		for (POSITION p = Tile_list.GetHeadPosition(); p != NULL;) {
			if (pos == Tile_list.GetAt(p)) {
				return;
			}
			Tile_list.GetNext(p);
		}
		Tile_list.AddTail(pos);
	}
	else if (e_char)
	{
		object.CreateCharacter(pos.x, pos.y);
	}
	else if (e_mon)
	{
		for (int i = 0; i < 10; i++)
		{
			if (monster[i].die) {
				monster[i].MonsterCreate(pos.x, pos.y);
				break;
			}
		}
	}
}


void CSpongeBobView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CPoint pos;
	if (e_block)
	{
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
	else if (e_char)
	{
		object.DeleteCharacter();
	}
	else if (e_mon)
	{
		;
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
	//새파일 생성
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

		//파일 목록 갱신
		CFile file_list;
		CFileException e1;
		filename tmp;
		CList<filename, filename&> namelist;
		if (!file_list.Open(_T("filename.txt"), CFile::modeReadWrite, &e1)) {  //파일객체 생성
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
	if (!name_list.Open(_T("filename.txt"), CFile::modeRead, &e1)) {//파일객체생성
		e1.ReportError();
		return;
	}
	int len = (int)(name_list.GetLength());
	while(1){                          //filename.txt를 읽어들임
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


void CSpongeBobView::OnBlock()
{
	if (e_block)
		e_char = e_mon = e_block = FALSE;
	else
	{
		e_char = e_mon = FALSE;
		e_block = TRUE;
	}
}


void CSpongeBobView::OnCharacter()
{
	if (e_char)
		e_char = e_mon = e_block = FALSE;
	else
	{
		e_mon = e_block = FALSE;
		e_char = TRUE;
	}
}


void CSpongeBobView::OnMonster()
{
	if (e_mon)
		e_char = e_mon = e_block = FALSE;
	else
	{
		e_char = e_block = FALSE;
		e_mon = TRUE;
	}
}


void CSpongeBobView::OnUpdateBlock(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(e_block);
}


void CSpongeBobView::OnUpdateCharacter(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(e_char);
}


void CSpongeBobView::OnUpdateMonster(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(e_mon);
}
